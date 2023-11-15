#ifndef POPUP_H_
#define POPUP_H_

#include <unistd.h>   // for sleep 1
#include <iostream> 
#include <fstream>
#include <string>
#include <wchar.h>    // wchar type judge (alphabet, space ...)

#include "utils.h"

// using std::min;

#define POPUPWIDTH 118   // main win-2
#define POPUPHEIGHT 31   // main win-2
#define POPUPSTART_Y 2
#define POPUPSTART_X 2

// write to screen
void show(WINDOW* win, const char* file, int& rowcount, int& startrow);

// create subwin (form) inherited from menu_win
void showcase(WINDOW* menu_win, string filename){
    // derwin: the content in parent win will be kept; newwin: overwrite the 'parent' win
    WINDOW* win_pop = newwin(POPUPHEIGHT, POPUPWIDTH, POPUPSTART_Y, POPUPSTART_X);
    assert(win_pop != NULL);
    // box(win_pop, 0, 0);
    
    refresh();
    wrefresh(win_pop);

    int ch; 
    int rowcount = 0; int startrow = 0;
    bool stop = false;
    string desc = "/repo1/metung/shuttle/desc/" + filename; // absolute path for using as symbolic tool
    // string desc = string(getrealpath(".")) + "/desc/" + filename;

    // show(win_pop, getrealpath(desc.c_str()), rowcount, startrow); // init content & compute rowcount
    show(win_pop, desc.c_str(), rowcount, startrow); // init content & compute rowcount
    while(1){
        ch = wgetch(menu_win);
        switch(ch){
            case 9:  // tab
                stop = true;
                break;
            case KEY_DOWN:
                if(startrow!=0 && rowcount-startrow<=POPUPHEIGHT){ // disable keydown when no content behind
                    break;
                }
                if(rowcount > POPUPHEIGHT){ // to be checked
                    startrow++; 
                    // wclear(win_pop); // the window is waiting for next refresh to redraw from scratch -> cause win flickering
                    werase(win_pop); // just clear the existed content -> smoothing between redraws 
                    show(win_pop, getrealpath(desc.c_str()), rowcount, startrow);
                }
                break;
            case KEY_UP:
                if(startrow > 0){
                    startrow--;
                    // wclear(win_pop); // clear -> cause win flickering
                    werase(win_pop);
                    show(win_pop, getrealpath(desc.c_str()), rowcount, startrow);
                }
                break;
            default: // other keys
                break;
        }
        if(stop){
            break;
        }
    }

    delwin(win_pop);
    // endwin();
}


void show(WINDOW* win, const char* file, int& rowcount, int& startrow){
    FILE* fp;
    wchar_t c;
    fp = fopen(file, "r") ; // opening an existing file
    if(fp == NULL){ // show nothing
        return;
    }
    int row = 0; int col = 0; // win start pos
    int currow = 0;          // cursor row num
    // print wchar by wchar
    while(1){
        // mvwprintw(win, row, col, "%s", file); break; // for test file path
        c = getwc(fp); // get wchar from file stream
        if(c == EOF){  // end of file
            break;
        }
        // deal with special tui-elements wchar_t
        if(c == L'─'){
            if(currow >= startrow){
                mvwaddch(win, row, col, ACS_HLINE);
                col++;
            }
        }
        else if(c == L'┌'){
            if(currow >= startrow){
                mvwaddch(win, row, col, ACS_ULCORNER);
                col++;
            }
        }
        else if(c == L'└'){
            if(currow >= startrow){
                mvwaddch(win, row, col, ACS_LLCORNER);
                col++;
            }
        }
        else if(c == L'┘'){
            if(currow >= startrow){
                mvwaddch(win, row, col, ACS_LRCORNER);
                col++;
            }
        }
        else if(c == L'┐'){
            if(currow >= startrow){
                mvwaddch(win, row, col, ACS_URCORNER);
                col++;
            }
        }
        else if(c == L'│'){
            if(currow >= startrow){
                mvwaddch(win, row, col, ACS_VLINE);
                col++;
            }
        }
        else if(c == L'├'){
            if(currow >= startrow){
                mvwaddch(win, row, col, ACS_LTEE);
                col++;
            }
        }
        else if(c == L'├'){
            if(currow >= startrow){
                mvwaddch(win, row, col, ACS_LTEE);
                col++;
            }
        }
        else if(c == L'┤'){
            if(currow >= startrow){
                mvwaddch(win, row, col, ACS_RTEE);
                col++;
            }
        }
        else if(c == L'┴'){
            if(currow >= startrow){
                mvwaddch(win, row, col, ACS_BTEE);
                col++;
            }
        }
        else if(c == L'┬'){
            if(currow >= startrow){
                mvwaddch(win, row, col, ACS_TTEE);
                col++;
            }
        }
        else if(c == L'┼'){
            if(currow >= startrow){
                mvwaddch(win, row, col, ACS_PLUS);
                col++;
            }
        }
        else if(c == '\n'){ // newline
            currow++;
            if(currow >= startrow){ // if need to display the line after \n
                if(currow==startrow && startrow!=0){ // if ...
                    col=0;
                }
                else if(currow==startrow && startrow==0){
                    row++; col=0;
                    mvwprintw(win, row, col, "%c", c);
                }
                else{
                    row++; col=0;
                    mvwprintw(win, row, col, "%c", c);
                }
            }
        }
        else{ // any chars
            if(currow >= startrow){
                mvwprintw(win, row, col, "%c", c); // 0,0 -> 0,1
                col++; // move
            }
        }
    }
    if(startrow == 0){ // record row of entire file when startrow=0
        rowcount = row;
    }
    wrefresh(win);
    fclose(fp); // close
}

#endif

