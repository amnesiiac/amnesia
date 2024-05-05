#ifndef HARDWARE_H
#define HARDWARE_H

#include "base.h"

MenuItem* Method::get_hardware_ptr(){
    MenuItem* hardware_ptr = new MenuItem;
    hardware_ptr->name = "hardware";
    hardware_ptr->submenu = {
        {"hardware & devices +", {
            {"lshw +", {{"show hardware info in summary#lshw -short#"},
                        {"show hardware info in html format#lshw -html > lshw.html#"}}},
            {"lsblk +", {{"show help page & available column for lsblk to output#lsblk --help#"},
                         {"show block device info with full path displayed#lsblk -p#"},
                         {"show block device info with chosen column to display (available column & desc see help)#lsblk -o NAME,MOUNTPOINT#"}}},
            {"lscpu +"},
            {"lspci +", {{"show pci info#lspci#"},
                         {"show pci info in tree format#lspci -t#"},
                         {"show pci info with detailed info of each device#lspci -v#"}}},
            {"lsscsi +", {{"show scsi/sata info#lsscsi#"},
                          {"show scsi/sata info with device size as additional info#lsscsi -s#"}}},
            {"sata +", {{"show sata info#hdparm /dev/sda1#"}}},
            {"lsusb +", {{"show usb info#lsusb#"},
                         {"show usb info (verbose)#lsusb -v#"}}},
            {"memory +", {{"show memory info by reading dmi tables#dmidecode -t memory#"}}},
            {"system +", {{"show system info by reading dmi tables#dmidecode -t system#"}}},
            {"bios +", {{"show bios info by reading dmi tables#dmidecode -t bios#"}}},
            {"processor +", {{"show processor info by reading dmi tables#dmidecode -t processor#"}}}}},
    };
    return hardware_ptr;
}

#endif
