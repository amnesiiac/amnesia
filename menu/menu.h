#ifndef MENU_H
#define MENU_H

#include "base.h"
#include "mac.h"
#include "transhell.h"
#include "blog.h"
#include "latex.h"
#include "gnu.h"


MenuItem* initdata(){
    std::map<std::string, MenuItem* (Method::*)()> method_map;

    method_map["mac"] = &Method::get_mac_ptr;
    method_map["transhell"] = &Method::get_transhell_ptr;
    method_map["latex"] = &Method::get_latex_ptr;
    method_map["gnu"] = &Method::get_gnu_ptr;
    method_map["blog"] = &Method::get_blog_ptr;

    Method mlib;
    std::vector<MenuItem*> menus;
    for(auto it=method_map.begin(); it!=method_map.end(); ++it){
        menus.push_back((mlib.*(it->second))());
    }

    MenuItem* menu_ptr = MenuBuilder::buildmenu(menus);
    return menu_ptr;
}

#endif
