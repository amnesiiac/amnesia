#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include "base.h"

MenuItem* Method::get_downloader_ptr(){
    MenuItem* downloader_ptr = new MenuItem;
    downloader_ptr->name = "downloader";
    downloader_ptr->submenu = {
        {"downloader +", {{"curl +", {{""}}}}},
    };
    return downloader_ptr;
}

#endif
