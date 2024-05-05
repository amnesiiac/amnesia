#ifndef TOOL_H
#define TOOL_H

#include "base.h"

MenuItem* Method::get_tool_ptr(){
    MenuItem* tool_ptr = new MenuItem;
    tool_ptr->name = "tool";
    tool_ptr->submenu = {
        {"tools +", {
            {"asciinema +", {
                {"record cast file startup (use ctrl+d to stop#asciinema rec ${record.cast}#"},
                {"play cast file (use ctrl+c to stop)#asciinema play ${record.cast}#"},
                {"generate a new faster played record using the existed record (asciinema play -h)#asciinema rec -c 'asciinema play -s 4 ${current.cast}' ${faster.cast}#"}}}},
        },
    };
    return tool_ptr;
}

#endif
