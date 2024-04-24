#ifndef MAC_H
#define MAC_H

#include "base.h"

MenuItem* Method::get_mac_ptr(){
    MenuItem* mac_ptr = new MenuItem;
    mac_ptr->name = "mac";
    mac_ptr->submenu = {
        {"mac +", {{"system integrity protection(SIP) +", {{"check SIP status#csrutil status#test"},
                                                           {"enable SIP#csrutil enable#"},
                                                           {"disable SIP#csrutil disable#"}}},
                   {"desktop icon +", {{"show icon#defaults delete com.apple.finder CreateDesktop; killall Finder#"},
                                       {"hide icon#defaults write com.apple.finder CreateDesktop -bool FALSE; killall Finder#"}}},
                   {"software install permission +", {{"disable install from all source#sudo spctl --master-disable#"},
                                                      {"enable install from all source#sudo spctl --master-enable#"}}},
                   {"show mac battery capacity#ioreg -rn AppleSmartBattery | grep -i capacity#"},
                   {"build mac app by applescript#osacompile -o ${appname.app} ${applescript.scpt}#"},
                   {"shortcut +", {{"app windows switch over sequentially#command + ~#"},
                                   {"lock the screen#ctrl + command + q#"}}}}
        }
    };
    return mac_ptr;
}

#endif
