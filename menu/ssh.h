#ifndef SSH_H
#define SSH_H

#include "base.h"

MenuItem* Method::get_ssh_ptr(){
    MenuItem* ssh_ptr = new MenuItem;
    ssh_ptr->name = "ssh";
    ssh_ptr->submenu = {
        {"ssh +", {
            {"*ssh config#see desc/sshconfig for details#sshconfig"},
            {"scp +", {
                {"test ssh connection to github site without create new tty#ssh -T git@github.com#"},
                {"download file from server to local#scp user@ip:${serverdir/file} ${localdir}#"},
                {"upload file from local to server#scp ${localdir/file} user@ip:${serverdir}#"},
                {"download dir from server to local under local dir#scp -r user@ip:${serverdir} ${localdir}#"},
                {"upload dir from local to server under serverdir#scp -r ${localdir} user@ip:${serverdir}#"}}}},
        },
    };
    return ssh_ptr;
}

#endif
