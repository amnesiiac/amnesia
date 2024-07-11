#include <cstring>
#include <stdio.h>
#include <ncurses.h>
#include <iostream>
#include <locale.h>   // setlocal

// #include "menuitem.h"
#include "menu.h"
#include "form.h"     // subwin enable quick selection according to user input
#include "popup.h"    // new popup win that show related file content in man dir
#include "leven.h"    // levenshtein distance
#include "jaro.h"     // jaro-winkler distance: better performance when matching special chars (enabled)

// std
using std::vector;
using std::string;
using std::map;
using std::max;
using std::cout;
using std::endl;

#define WINWIDTH 120
#define WINHEIGHT 34
#define WINSTART_X 1        // win border startup x offset from terminal border
#define WINSTART_Y 0        // win border startup y offset from terminal border
#define MENU_X 2            // menu start x offset from win border
#define MENU_Y 2            // menu start y offset from win border
#define MENU_INTERVAL 2     // interval between prev/next layer of menus
#define MAX_MENUSTRLEN 36   // max len of menu string (trunc the left)

// execute shell cmd: echo "cmd" | pbcopy
char* execute_command(const char* command){
    char buffer[128];
    char* result = static_cast<char*>(malloc(1)); result[0] = '\0';
    FILE* pipe = popen(command, "r");
    if(pipe == nullptr){
        return result;
    }
    while(fgets(buffer, sizeof(buffer), pipe) != nullptr){
        result = static_cast<char*>(realloc(result, strlen(result) + strlen(buffer) + 1));
        strcat(result, buffer);
    }
    pclose(pipe);
    return result;
}

// return the menu item name
inline string get_head(string str){
    int pos = str.find_first_of('#');
    if(pos != string::npos){
        str.erase(pos);
    }
    return str;
}

// return the menu item cmd
inline string get_cmd(string str){
    int pos1 = str.find_first_of('#');
    int pos2 = str.find_last_of('#') - pos1 - 1;
    if(pos1!=string::npos && pos2!=string::npos){
        str.erase(0, pos1+1);
        str.erase(pos2);
        return str;
    }
    return "";
}

// return the filename(man, examples...) if existed
inline string get_file(string str){
    int pos = str.find_last_of('#');
    if(pos != string::npos){
        str.erase(0, pos+1);
        return str;
    }
    return "";
}

inline string trunc_menu_header(string headstr){
    if(headstr.length() > MAX_MENUSTRLEN){
        return headstr.substr(0, MAX_MENUSTRLEN);
    }
    else{
        return headstr;
    }
}

// dump "layer -> menus" info to result (only available when memu layer changes)
void getlayout(map<int, vector<string>> &res, MenuItem* ptr, int layer, int limit,
               vector<int> &highlight){
    if(ptr!=nullptr){
        if(res.find(layer)!=res.end()){
            res[layer].push_back(ptr->name);
        }
        else{
            res[layer] = {ptr->name};
        }
        layer++; // 1 layer deeper
        int menu_no = -1;
        for(auto it : ptr->submenu){
            menu_no++;
            // go to submenu, condition
            if(it.submenu.size()!=0 && layer<limit && menu_no==highlight[layer]){
                getlayout(res, &it, layer, limit, highlight);
            }
            else{ // no submenu
                if(res.find(layer)!=res.end()){ // already recorded
                    res[layer].push_back(it.name);
                }
                else{
                    res[layer] = {it.name};
                }
            }
        }
        return;
    }
    else{
        return;
    }
}

// print text according to (x,y)
void print_menu(WINDOW* menu_win, int x, int y, int active_layer, vector<int> &highlight,
                map<int, vector<string>> &res){
    box(menu_win, 0, 0);
    string headstr, trunc_headstr;
    string null(WINWIDTH-3, ' ');
    for(int i = 0; i < res[active_layer].size(); ++i){                                                 // for each item in menu_win
        headstr = get_head(res[active_layer][i]);
        trunc_headstr = headstr.length()>MAX_MENUSTRLEN? headstr.substr(0, MAX_MENUSTRLEN) : headstr;
        trunc_headstr = trunc_menu_header(headstr);
        // trunc_headstr = headstr.length()>MAX_MENUSTRLEN? headstr.substr(0, MAX_MENUSTRLEN) : headstr;
        if(highlight[active_layer] == i){                                                              // active item -> highlight
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", trunc_headstr.c_str());
            wattroff(menu_win, A_REVERSE);
            mvwprintw(menu_win, 1, 2, "%s", null.c_str());                                             // clear space
            mvwprintw(menu_win, 1, 2, ">>> %s", headstr.c_str());                                      // print full menu string
        }
        else{                                                                                          // no active item
            mvwprintw(menu_win, y, x, "%s", (char*)trunc_headstr.c_str());
        }
        ++y;
    }
    wrefresh(menu_win);
}

// get max menu name width for each layer
int get_menu_width(vector<string> &menu){
    int len=-1;
    for(string item : menu){
        len = max(len, (int)trunc_menu_header(get_head(item)).length());
    }
    return len;
}

int main(){
    // libc use locale from system default
    setlocale(LC_ALL, "");

    // menu data intake
    MenuItem* ptr = initdata();

    // init state
    int startlayer=0;
    map<int, vector<string>> res;   // layer -> vector<int> menu names
    int active_layer = 1;           // active layer
    vector<int> active_menu(10, 0); // maximum 10 layer
    int active_layer_menu_num;      // num of items of each layer
    int x=MENU_X, y=MENU_Y;         // menu win pos
    int c;                          // user input char
    bool choice=false;              // user enter choice
    int old_win_pos=x;              // record last operating win x pos
    string head;                    // chosen head name
    string cmd;                     // chosen cmd
    string ret;                     // form return string
    // int levenDis = 0;               // levenshtein distance
    double jaroDis = 0;             // jaro-winkler distance
    // int minDis = 1000;              // min l dis
    double minDis = 1000;
    int minDisIdx = 0;              // menu item index has min l dis

    // init ncurse
    initscr();
    clear();
    noecho();
    cbreak();

    // init ncurse menu win
    WINDOW* menu_win;
    menu_win = newwin(WINHEIGHT, WINWIDTH, WINSTART_Y, WINSTART_X);
    keypad(menu_win, TRUE);
    // mvprintw(0, 0, "Arrow keys to go up/down. Press enter to select.");
    refresh(); // refresh all

    // init layer 1 menu
    getlayout(res, ptr, startlayer, active_layer, active_menu);
    print_menu(menu_win, x, y, active_layer, active_menu, res);

    // tui while loop
    while(1){
        c = wgetch(menu_win);
        switch(c){
            case KEY_UP: // active layer not change, menu highlight item rotated
                active_layer_menu_num = res[active_layer].size(); // compute current layer menu num
                if(active_menu[active_layer] == 0){ // rollback
                    active_menu[active_layer] = active_layer_menu_num-1;
                }
                else{
                    --active_menu[active_layer];
                }
                print_menu(menu_win, x, y, active_layer, active_menu, res);
                break;
            case KEY_DOWN: // active layer not change, menu highlight item rotated
                active_layer_menu_num = res[active_layer].size();
                if(active_menu[active_layer] == active_layer_menu_num-1){
                    active_menu[active_layer] = 0;
                }
                else{
                    ++active_menu[active_layer];
                }
                print_menu(menu_win, x, y, active_layer, active_menu, res);
                break;
            case KEY_RIGHT: // try active layer+1, has submenu->print, no submenu->restore&print
                ++active_layer; active_menu[active_layer]=0; // refresh highlight
                res.clear();
                getlayout(res, ptr, startlayer, active_layer, active_menu); // refresh res
                if(res[active_layer].size()!=0){ // check if current highlight has submenu
                    x=old_win_pos+get_menu_width(res[active_layer-1])+MENU_INTERVAL; old_win_pos=x;
                }
                else{ // do nothing show the same (restore the condition)
                    active_layer--; // restore layer
                    res.clear(); getlayout(res, ptr, startlayer, active_layer, active_menu);
                }
                print_menu(menu_win, x, y, active_layer, active_menu, res);
                break;
            case KEY_LEFT: // go one layer shallower, into pre level active
                if(active_layer<=1){ // no previous menu
                    print_menu(menu_win, x, y, active_layer, active_menu, res);
                }
                else{
                    werase(menu_win); // clear the window
                    old_win_pos=2; // init win pos
                    for(int layer=1; layer<active_layer; layer++){ // print each layer menu left->right
                        res.clear();
                        getlayout(res, ptr, startlayer, layer, active_menu); // refresh res
                        if(res[layer].size()!=0){ // check if current highlight has submenu
                            x=layer==1? old_win_pos:old_win_pos+get_menu_width(res[layer-1])+MENU_INTERVAL;
                            old_win_pos=x;
                        }
                        print_menu(menu_win, x, y, layer, active_menu, res);
                    }
                    // reset active layer
                    active_layer--;
                    res.clear();
                    getlayout(res, ptr, startlayer, active_layer, active_menu); // refresh res
                }
                break;
            case 10: // press enter -> execute the corresponding shell command
                head = get_head(res[active_layer][active_menu[active_layer]]);
                cmd = get_cmd(res[active_layer][active_menu[active_layer]]);
                print_menu(menu_win, x, y, active_layer, active_menu, res);
                choice = true; // reset choice to break the while loop
                break;
            case 47: // press '/' -> print a form on top of window, ask for user input, and use regex to highlight the best match item
                // using form return a string
                ret = formloop(menu_win);
                // find the best match by levendis
                for(int i=0; i<res[active_layer].size(); ++i){ // for each item in menu_win
                    // levenDis = levenshteinDist(get_head(res[active_layer][i]), ret);
                    // minDisIdx = levenDis<minDis? i : minDisIdx;
                    // minDis = std::min(levenDis, minDis);
                    jaroDis = 1 - jaroWinklerDistance(get_head(res[active_layer][i]), ret);
                    minDisIdx = jaroDis<minDis? i : minDisIdx;
                    minDis = std::min(jaroDis, minDis);
                }
                // refresh cur hi 
                if(minDisIdx != active_menu[active_layer]){
                    active_menu[active_layer] = minDisIdx;
                    // levenDis = 0; minDis = 1000; minDisIdx = 0; // reset
                    jaroDis = 0; minDis = 1000; minDisIdx = 0; // reset
                }
                // update layout info and print
                print_menu(menu_win, x, y, active_layer, active_menu, res);
                break;
            case 9: // tab -> print text on popup window
                showcase(menu_win, get_file(res[active_layer][active_menu[active_layer]]));
                print_menu(menu_win, x, y, active_layer, active_menu, res);
                // choice = true;
                break;
            default: // other keys -> refresh the menu_win
                print_menu(menu_win, x, y, active_layer, active_menu, res);
                refresh();
                break;
        }
        if(choice){ // user choice to get out of infinite loop
            break;
        }
    }
    // renovate cmd to pbcopy
    string echo = "echo ";
    string quote = "\'"; // forbid shell expansion
    string tr = " | tr -d \'\\n\'";
    string pbcopy = " | pbcopy";
    string cache_cmd = cmd;
    cmd = echo + quote + cmd + quote + tr + pbcopy;

    // shell cmd execute
    char* output = execute_command(cmd.c_str());
    free(output);

    // clean all & close win
    clrtoeol();
    refresh();
    endwin();

    // output shell prompt
    cout << head << ":\n>>> "<< cache_cmd << endl;
    return 0;
}


