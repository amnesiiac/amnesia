#ifndef TERM_H
#define TERM_H

#include "base.h"

MenuItem* Method::get_term_ptr(){
    MenuItem* term_ptr = new MenuItem;
    term_ptr->name = "term";
    term_ptr->submenu = {
        {"terminal + ", {{"job +", {{"show jobs of current shell job list#jobs#"}}},
                         {"disown +", {{"remove the job %1 from terminal job list#disown %1#"}}}}},
    };
    return term_ptr;
}

#endif
