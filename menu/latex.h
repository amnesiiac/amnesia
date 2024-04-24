#ifndef LATEX_H
#define LATEX_H

#include "base.h"

MenuItem* Method::get_latex_ptr(){
    MenuItem* latex_ptr = new MenuItem;
    latex_ptr->name = "latex";
    latex_ptr->submenu = {
        {"latex +", {{"build texlive pdflatex en#docker run --rm -i -v $PWD:/data latex pdflatex ${en}.tex#"},
                     {"build texlive xelatex zh#docker run --rm -i -v $PWD:/data latex xelatex ${zh}.tex#"}}}
    };
    return latex_ptr;
}

#endif
