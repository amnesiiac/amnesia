#ifndef PROCESS_H
#define PROCESS_H

#include "base.h"

MenuItem* Method::get_process_ptr(){
    MenuItem* process_ptr = new MenuItem;
    process_ptr->name = "process";
    process_ptr->submenu = {
        {"process +", {
            {"ps +", {{"show parent proc of current proc#ps j ${cur_pid}#"},
                      {"show full cmdline for a proc#ps -ef | grep ${pid} | awk '{ for(i=${col}; i<=NF; i++) printf \"%s \", $i; print \"\" }'#"}}},
            {"pstree +"},
            {"cpu affinity +", {{"get certain proc's cpu affinity#taskset#"}}},
            {"procfs +", {{"show the cmdline that start the process#cat /proc/${pid}/cmdline#"},
                        {"show the status of a process (todo: explanation needed)#cat /proc/${pid}/status#"}}},
            {"kill proc +", {
                {"kill +"},
                {"pkill +", {
                    {"kill all processes with name exactly match the pattern#pkill -f ${pattern}#"}}}}}},
        },
    };
    return process_ptr;
}

#endif
