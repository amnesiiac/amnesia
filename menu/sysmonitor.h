#ifndef SYSMONITOR_H
#define SYSMONITOR_H

#include "base.h"

MenuItem* Method::get_sysmonitor_ptr(){
    MenuItem* sysmonitor_ptr = new MenuItem;
    sysmonitor_ptr->name = "sysmonitor";
    sysmonitor_ptr->submenu = {
        {"system activity monitoring +", {
            {"auditctl +", {{"list all existed audit rules#sudo auditctl -l#"},
                            {"add audit rules for monitoring file write, attribute changing#sudo auditctl -w /repo/reborn/logg/init-aarch64.log -p wa#"},
                            {"delete all audit rules#sudo auditctl -D#"},
                            {"delete certain audit rules##"},
                            {"check all audit log#sudo vim /var/log/audit/audit.log#"}}},
            {"inotify +", {{"install the inotify tools on centos linux#yum install inotify-tools#"},
                           {"inotifywait +", {{"show manual#man inotifywait#"},
                                              {"capture the first event happened on dir#inotifywait ${dir}#"},
                                              {"monitor events on certain dir continuously#inotifywait -m ${dir}#"}}}}}},
        },
    };
    return sysmonitor_ptr;
}

#endif
