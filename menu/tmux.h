#ifndef TMUX_H
#define TMUX_H

#include "base.h"

MenuItem* Method::get_tmux_ptr(){
    MenuItem* tmux_ptr = new MenuItem;
    tmux_ptr->name = "tmux";
    tmux_ptr->submenu = {
        {"tmux +", {
            {"settings +", {{"install"},
                            {"config"}}},
            {"session +", {{"create new session#tmux new -s ${session}#"},
                           {"list sessions(terminal)#tmux ls#"},
                           {"list sessions(tmux)#ctrl+b,s#"},
                           {"access sessions(terminal)#tmux a -t ${session}#"},
                           {"detach from current session#ctrl+b,d#"},
                           {"kill session(terminal/tmux)#tmux kill-session -t ${session}#"},
                           {"rename session(terminal/tmux)#tmux rename -t ${oldname} ${newname}#"},
                           {"rename current session(tmux)#ctrl+b,$#"}}},
            {"window +", {{"create window#ctrl+b,c#"},
                          {"previous window#ctrl+b,p#"},
                          {"next window#ctrl+b,n#"},
                          {"switch to window n#ctrl+b,${win_num}#"},
                          {"list windows#ctrl+b w#"},
                          {"close current window#ctrl+b,&#"}}},
            {"pane +", {{"split win to left/right pane#ctrl+b,%#"},
                        {"split win to top/bottom pane#ctrl+b,\\#"},
                        {"select pane by arrow keys#ctrl+b,${arrows}#"},
                        {"maximize/restore current pane#ctrl+b,z#"},
                        {"close current pane#ctrl+b,x#"}}}},
        },
    };
    return tmux_ptr;
}

#endif
