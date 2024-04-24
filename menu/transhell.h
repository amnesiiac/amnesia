#ifndef TRANSHELL_H
#define TRANSHELL_H

#include "base.h"

MenuItem* Method::get_transhell_ptr(){
    MenuItem* transhell_ptr = new MenuItem;
    transhell_ptr->name = "transhell";
    transhell_ptr->submenu = {
        {"transhell#docker run --rm -it transhell -shell#"}
    };
    return transhell_ptr;
}

#endif
