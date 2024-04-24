#include "base.h"
#include "mac.h"
#include "transhell.h"
#include "blog.h"
#include "latex.h"
#include "gnu.h"

// create MenuBuilder singleton instance
// invoke its public method to return the menu_ptr as below

MenuItem* initdata(){
    MenuItem *menu_ptr = new MenuItem;
    menu_ptr->name = "Main Menu";

    MenuItem* mac_ptr = get_mac_ptr();
    menu_ptr->submenu.insert(menu_ptr->submenu.end(), mac_ptr->submenu.begin(), mac_ptr->submenu.end());

    MenuItem* transhell_ptr = get_transhell_ptr();
    menu_ptr->submenu.insert(menu_ptr->submenu.end(), transhell_ptr->submenu.begin(), transhell_ptr->submenu.end());

    MenuItem* blog_ptr = get_blog_ptr();
    menu_ptr->submenu.insert(menu_ptr->submenu.end(), blog_ptr->submenu.begin(), blog_ptr->submenu.end());

    MenuItem* latex_ptr = get_latex_ptr();
    menu_ptr->submenu.insert(menu_ptr->submenu.end(), latex_ptr->submenu.begin(), latex_ptr->submenu.end());

    MenuItem* gnu_ptr = get_gnu_ptr();
    menu_ptr->submenu.insert(menu_ptr->submenu.end(), gnu_ptr->submenu.begin(), gnu_ptr->submenu.end());

    return menu_ptr;
}
