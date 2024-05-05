#ifndef CICD_H
#define CICD_H

#include "base.h"

MenuItem* Method::get_cicd_ptr(){
    MenuItem* cicd_ptr = new MenuItem;
    cicd_ptr->name = "cicd";
    cicd_ptr->submenu = {
        {"ci/cd +", {
            {"gitlab ci/cd +", {{"*basic pipeline to register runner for project or a group##gitlabrunner"},
                                {"*basic gitlab yaml usages & cautions##gitlabyaml"}}},
            {"github actions +"}}
        },
    };
    return cicd_ptr;
}

#endif
