#ifndef CRONTAB_H
#define CRONTAB_H

#include "base.h"

MenuItem* Method::get_crontab_ptr(){
    MenuItem* crontab_ptr = new MenuItem;
    crontab_ptr->name = "crontab";
    crontab_ptr->submenu = {
        {"crontab +", {
            {"show manual#man crontab#"},
            {"show crontab configs#cat /etc/crontab#"},
            {"list crontab jobs for current user#crontab -l#"},
            {"edit/create crontab config for current user#crontab -e#"},
            {"edit/create/replace crontab config for cur user in certain place#crontab ${path/file}#"},
            {"remove all crontab jobs#crontab -r#"},
            {"remove certain crontab job#crontab -r ${jobid}#"},
            {"remove certain crontab job with prompt#crontab -ri#"}},
        },
    };
    return crontab_ptr;
}

#endif
