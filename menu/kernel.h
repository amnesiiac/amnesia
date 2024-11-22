#ifndef KERNEL_H
#define KERNEL_H

#include "base.h"

MenuItem* Method::get_kernel_ptr(){
    MenuItem* kernel_ptr = new MenuItem;
    kernel_ptr->name = "kernel";
    kernel_ptr->submenu = {
        {"kernel +", {
            {"grep config option inside zipped kernel config (if kernel is configured to have config.gz)#zcat /proc/config.gz | grep -i ${pattern_to_search}#"},
            {"ring buffer +", {{"dmesg +", {{"show manual (print / control kernel ring buffer)#man dmesg#"},
                                            {"show help page#dmesg --help#"},
                                            {"show kernel ring buffer log in certain log level (debug, info, notice...)#dmesg -l ${log level}#"},
                                            {"check kvm related msg (sometime lsmod show kvm ready, but kvm still not available)#dmesg | grep -i kvm#"}}}}},
        }},
    };
    return kernel_ptr;
}

#endif
