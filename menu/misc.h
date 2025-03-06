#ifndef MISC_H
#define MISC_H

#include "base.h"

MenuItem* Method::get_misc_ptr(){
    MenuItem* misc_ptr = new MenuItem;
    misc_ptr->name = "misc";
    misc_ptr->submenu = {{"misc +", {{"history +", {{"show cmd history, execute certain cmd directly#history && !${line_no}#"},
                                                    {"show cmd history, print the cmd, scroll up for rectify & execution#history && !${line_no}:p && ^#"}}}}},
    };
    return misc_ptr;
}

#endif
