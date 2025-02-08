#ifndef MENU_H
#define MENU_H

#include "base.h"
#include "mac.h"
#include "transhell.h"
#include "blog.h"
#include "latex.h"
#include "gnu.h"
#include "revision.h"
#include "network.h"
#include "downloader.h"
#include "docker.h"
#include "filesys.h"
#include "dev.h"
#include "sysmonitor.h"
#include "search.h"
#include "user.h"
#include "vim.h"
#include "tmux.h"
#include "code.h"
#include "cicd.h"
#include "crontab.h"
#include "os.h"
#include "kernel.h"
#include "time_.h"
#include "tool.h"
#include "term.h"
#include "encryption.h"
#include "performance.h"
#include "process.h"


MenuItem* initdata(){
    std::map<std::string, MenuItem* (Method::*)()> method_map;

    method_map["mac"] = &Method::get_mac_ptr;
    method_map["blog"] = &Method::get_blog_ptr;
    method_map["code"] = &Method::get_code_ptr;
    method_map["cicd"] = &Method::get_cicd_ptr;
    method_map["crontab"] = &Method::get_crontab_ptr;
    method_map["transhell"] = &Method::get_transhell_ptr;
    method_map["latex"] = &Method::get_latex_ptr;
    method_map["gnu"] = &Method::get_gnu_ptr;
    method_map["revision"] = &Method::get_revision_ptr;
    method_map["network"] = &Method::get_network_ptr;
    method_map["downloader"] = &Method::get_downloader_ptr;
    method_map["docker"] = &Method::get_docker_ptr;
    method_map["dev"] = &Method::get_dev_ptr;
    method_map["filesys"] = &Method::get_filesys_ptr;
    method_map["sysmonitor"] = &Method::get_sysmonitor_ptr;
    method_map["search"] = &Method::get_search_ptr;
    method_map["user"] = &Method::get_user_ptr;
    method_map["vim"] = &Method::get_vim_ptr;
    method_map["tmux"] = &Method::get_tmux_ptr;
    method_map["os"] = &Method::get_os_ptr;
    method_map["kernel"] = &Method::get_kernel_ptr;
    method_map["time"] = &Method::get_time_ptr;
    method_map["tool"] = &Method::get_tool_ptr;
    method_map["term"] = &Method::get_term_ptr;
    method_map["encryption"] = &Method::get_encryption_ptr;
    method_map["performance"] = &Method::get_performance_ptr;
    method_map["process"] = &Method::get_process_ptr;

    Method mlib;
    std::vector<MenuItem*> menus;
    for(auto it=method_map.begin(); it!=method_map.end(); ++it){
        menus.push_back((mlib.*(it->second))());
    }

    MenuItem* menu_ptr = MenuBuilder::buildmenu(menus);
    return menu_ptr;
}

#endif
