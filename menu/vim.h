#ifndef VIM_H
#define VIM_H

#include "base.h"

MenuItem* Method::get_vim_ptr(){
    MenuItem* vim_ptr = new MenuItem;
    vim_ptr->name = "vim";
    vim_ptr->submenu = {
        {"vim +", {
            {"nvim img +", {{"edit nvim dockerfile#nvim /Users/mac/nvim/Dockerfile#"},
                            {"build nvim image##"},
                            {"invoke nvim image by script##"}}},
            {"vim cmd +", {{"create & edit a new copy of current file: new.log#:sav new.log#"},
                           {"create a new file using a range of lines#:{linestart},${lineend}w ${out.file}#"}}},
            {"vimdiff +", {{"specify the tool as vimdiff#--tool=vimdiff#"},
                           {"vimdiff window layout#[local, base, remote]#"},
                           {"vimdiff switch between windows#ctrl+w,h (move to left), ctrl+w,l (move to right)#"}}},
            {"regex match +", {{"search instance match pattern (start with lib, arbitary char in middle, end with tar.gz)#:g/lib.*tar.gz#"},
                               {"search instance match pattern in line range#/\%>9l\%<33llib.*tar.gz#"},
                               {"search instance match pattern in line range (press no to navi)#:10,32s/lib.*tar.gz//gc#"},
                               {"match lines does not contain the word foo#/^\(\(.*foo.*\)\@!.\)*$#"},
                               {"match lines does not contain certain pattern#/^\(\(.*lib.*tar.gz.*\)\@!.\)*$#"},
                               {"show lines does not contain certain pattern#:g!/lib.*tar.gz/p#"},
                               {"show lines ccontain certain pattern#:g/lib.*tar.gz/p#"},
                               {"delete all lines match pattern#:g/lib.*tar.gz/d#"},
                               {"delete all lines does not match pattern#:g!/lib.*tar.gz/d#"}}}}
        },
    };
    return vim_ptr;
}

#endif
