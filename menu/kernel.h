#ifndef KERNEL_H
#define KERNEL_H

#include "base.h"

MenuItem* Method::get_kernel_ptr(){
    MenuItem* kernel_ptr = new MenuItem;
    kernel_ptr->name = "kernel";
    kernel_ptr->submenu = {
        {"kernel +", {
            {"grep config option inside zipped kernel config (if kernel is configured to have config.gz)#zcat /proc/config.gz | grep -i ${pattern_to_search}#"}},
        },
    };
    return kernel_ptr;
}

#endif
