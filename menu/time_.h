#ifndef TIME_H
#define TIME_H

#include "base.h"

MenuItem* Method::get_time_ptr(){
    MenuItem* time_ptr = new MenuItem;
    time_ptr->name = "time";
    time_ptr->submenu = {
        {"time +", {
            {"show date info of current machine or NTP server configured time#date#"},
            {"time since kernel bootup (container shared with host, vm own exclusively)#uptime#"},
            {"show current timezone info (not NTP time)#zdump -c \"$(date +'%Y-%m-%d %H:%M:%S')\" /etc/localtime#"}},
        },
    };
    return time_ptr;
}

#endif
