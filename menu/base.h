#ifndef BASE_H     // avoid dulicate include
#define BASE_H

#include <vector>
#include <string>
#include <map>

struct MenuItem{
    std::string name;
    std::vector<MenuItem> submenu;
};

// make this menu builder as singleton instance using lcoal static solution, which can only create one global distance
class MenuBuilder{
private:
    MenuBuilder(){};
    ~ MenuBuilder(){};
    MenuBuilder& operator=(const MenuBuilder&);
    MenuBuilder(const MenuBuilder&);
public:
    static MenuItem* buildmenu(std::vector<MenuItem>&);
};

MenuItem* MenuBuilder::buildmenu(std::vector<MenuItem*>& menus){
    static MenuItem* local_menu_ptr;
    local_menu_ptr->name = "Main Menu";
    local_menu_ptr->submenu = {};
    for(MenuItem* menu_ptr: menus){
        local_menu_ptr->submenu.insert(local_menu_ptr->submenu.end(), menu_ptr->submenu.begin(), menu_ptr->submenu.end());
    }
    return local_menu_ptr;
}

#endif // BASE_H
