#ifndef USER_H
#define USER_H

#include "base.h"

MenuItem* Method::get_user_ptr(){
    MenuItem* user_ptr = new MenuItem;
    user_ptr->name = "user";
    user_ptr->submenu = {
        {"su/sudo/id/user/groups +", {
            {"su +"},
            {"doas +", {{"*add user with doas privilege in alpine#see desc pages for details#su_sudo"}}},
            {"sudo +", {{"run cmd as another user with $HOME set as /home/anotheruser before cmd run#sudo -u ${another user} -H ${cmd}#su_sudo"}}},
            {"user +", {{"show certain user info#id ${username}#"},
                        {"add a user#sudo useradd ${username}#"},
                        {"add passwd for a user#sudo passwd ${username}#"},
                        {"change passwd for a user (no need for previous passwd, root)#passwd ${username}#"},
                        {"change passwd for current user (previous passwd needed, user)#passwd#"}}},
            {"print usernames currently logged in (one name per ssh connection)#users#"},
            {"groups +", {{"add certain user to group#sudo usermod -aG ${groupname} ${username}#"},
                          {"show the groups of a user#groups ${username}#"},
                          {"show the groups of current user#groups $(whoami)#"}}}}},
    };
    return user_ptr;
}

#endif
