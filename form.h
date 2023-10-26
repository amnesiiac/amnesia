#ifndef FORM_H_
#define FORM_H_

#include <ncurses.h>
#include <form.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// c++ string
#include <string>
using std::string;

#include "utils.h"


// static WINDOW *win_body, *win_form;

#define FORMWIDTH 80
#define FORMHEIGHT 1
#define FORMSTART_X 2  // for alignment with main window items
#define FORMSTART_Y 1


static void driver(WINDOW* win, FORM* form, FIELD* fields[3], int ch, string& res){
    int i;
    switch(ch){
        case 10: // enter
            // sync current field buffer with the value displayed
            form_driver(form, REQ_NEXT_FIELD); // refresh cur field buffer
            form_driver(form, REQ_PREV_FIELD); // go back
            refresh();
            res = string(trim_whitespaces(field_buffer(fields[1], 0)));
            break;
        // case KEY_DOWN: // next
        //     form_driver(form, REQ_NEXT_FIELD);
        //     form_driver(form, REQ_END_LINE);
        //     break;
        // case KEY_UP: // prev
        //     form_driver(form, REQ_PREV_FIELD);
        //     form_driver(form, REQ_END_LINE);
        //     break;
        // case KEY_LEFT:
        //     form_driver(form, REQ_PREV_CHAR);
        //     break;
        // case KEY_RIGHT:
        //     form_driver(form, REQ_NEXT_CHAR);
        //     break;
        // case KEY_BACKSPACE:                   // del char before cursor: not working
        //     form_driver(form, REQ_DEL_PREV);
        //     break;
        case 127:
            form_driver(form, REQ_DEL_PREV);
            break;
        // case KEY_DC:                          // del char under cursor
        //     form_driver(form, REQ_DEL_CHAR);
        //     break;
        default:
            form_driver(form, ch);
            break;
    }
    wrefresh(win);
}

// --- create subwin (form) inherited from menu_win --- //
string formloop(WINDOW* menu_win){
    // win of form -> menu_win 
    WINDOW* win_form = derwin(menu_win, FORMHEIGHT, FORMWIDTH, FORMSTART_Y, FORMSTART_X);
    assert(win_form != NULL);
    // box(win_form, 0, 0);
    
    // fields
    FIELD* fields[3];
    fields[0] = new_field(1, 10, 0, 0, 0, 0);   // field_height, field_width, pos_y, pos_x
    fields[1] = new_field(1, 40, 0, 8, 0, 0);
    fields[2] = NULL;
    assert(fields[0] != NULL && fields[1] != NULL);
    // set buffer names
    set_field_buffer(fields[0], 0, "SEARCH:");
    set_field_buffer(fields[1], 0, "");
    // set field options
    set_field_opts(fields[0], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(fields[1], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);

    // form
    FORM* form = new_form(fields);
    assert(form != NULL);
    set_form_win(form, win_form);
    // set_form_sub(form, derwin(win_form, FORMHEIGHT, FORMWIDTH, FORMSTART_Y, FORMSTART_X)); // bugs
    set_form_sub(form, win_form);
    post_form(form);

    // refresh();
    wrefresh(win_form);

    // main loop
    int ch;
    string res;
    while((ch=getch()) != 27){ // ESC
        driver(win_form, form, fields, ch, res);
        if(ch == 10){ // the second enter will break while
            break;
        }
    }

    // cleanup (todo: make it a hook when tui abnormal exit)
    unpost_form(form);
    free_form(form);
    free_field(fields[0]);
    free_field(fields[1]);
    free_field(fields[2]);
    delwin(win_form);
    // endwin(); // win_form is subwin of menu_win, if endwin, will exit all

    return res;
}

#endif

