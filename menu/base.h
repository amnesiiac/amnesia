#ifndef BASE_H
#define BASE_H

#include <vector>
#include <string>
#include <map>

struct MenuItem{
    std::string name;
    std::vector<MenuItem> submenu;
};

class Method;

class MenuBuilder{  // singleton
private:
    MenuBuilder(){};
    ~MenuBuilder(){};
    MenuBuilder(const MenuBuilder&);
    const MenuBuilder& operator=(const MenuBuilder&);
public:
    static MenuItem* buildmenu(const std::vector<MenuItem*>&);  // independant among all instance
};

MenuItem* MenuBuilder::buildmenu(const std::vector<MenuItem*>& menus){
	static MenuItem menu;
    static MenuItem* local_menu_ptr = &menu;  // global unique
    local_menu_ptr->name = "Main Menu";
    local_menu_ptr->submenu = {};
    for(const MenuItem* menu_ptr: menus){
        local_menu_ptr->submenu.insert(
            local_menu_ptr->submenu.end(),
            menu_ptr->submenu.begin(),
            menu_ptr->submenu.end()
        );
    }
    return local_menu_ptr;
};

#endif // BASE_H
