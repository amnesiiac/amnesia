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
                {"generate a new faster played record using the existed record (asciinema play -h)#asciinema rec -c 'asciinema play -s 4 ${current.cast}' ${faster.cast}#"}}},
            {"vnc +", {{"vnc config path#ls -l ~/.vnc/#"},
                       {"vncpasswd +", {{"show manual#man vncpasswd#"},
                                        {"interatively setup login passwd for vnc#vncpasswd#"}}},
                       {"vncserver +", {{"show manual#man vncserver#"},
                                        {"startup vnc server by a given id (id: 1,2,3...)#vncserver :${id}#"},
                                        {"list all vnc server live#vncserver -list#"},
                                        {"kill a certain vnc server#vncserver -kill :${uuid}#"},
                                        {"*config the xstartup script & behavior#cd ~/.vnc/ && vim xstartup#vnc"}}}}}},
        },
    };
    return tool_ptr;
}

#endif
