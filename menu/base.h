#ifndef BASE_H
#define BASE_H

#include <vector>
#include <string>
#include <map>

struct MenuItem{
    std::string name;
    std::vector<MenuItem> submenu;
};

class Method{
public:
    MenuItem* get_mac_ptr();
    MenuItem* get_blog_ptr();
    MenuItem* get_code_ptr();
    MenuItem* get_cicd_ptr();
    MenuItem* get_crontab_ptr();
    MenuItem* get_transhell_ptr();
    MenuItem* get_latex_ptr();
    MenuItem* get_gnu_ptr();
    MenuItem* get_revision_ptr();
    MenuItem* get_network_ptr();
    MenuItem* get_downloader_ptr();
    MenuItem* get_docker_ptr();
    MenuItem* get_filesys_ptr();
    MenuItem* get_dev_ptr();
    MenuItem* get_sysmonitor_ptr();
    MenuItem* get_search_ptr();
    MenuItem* get_user_ptr();
    MenuItem* get_vim_ptr();
    MenuItem* get_tmux_ptr();
    MenuItem* get_os_ptr();
    MenuItem* get_kernel_ptr();
    MenuItem* get_time_ptr();
    MenuItem* get_tool_ptr();
    MenuItem* get_term_ptr();
    MenuItem* get_encryption_ptr();
    MenuItem* get_performance_ptr();
    MenuItem* get_process_ptr();
};

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
