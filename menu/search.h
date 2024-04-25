#ifndef SEARCH_H
#define SEARCH_H

#include "base.h"

MenuItem* Method::get_search_ptr(){
    MenuItem* search_ptr = new MenuItem;
    search_ptr->name = "search";
    search_ptr->submenu = {
        {"search +", {
            {"find +", {
                {"show manual of find#man find#"},
                {"file operations +", {{"list files under certain dir#find ${dir} -type f#"},
                                       {"list files under certain dir matches the name pattern recursively#find . -type f -name '*.cpp'#"},
                                       {"list files under certain dir doesnt match the name pattern recursively#find ${dir} -type f ! -name '*.cpp'#"},
                                       {"list files under certain dir matches the name pattern at given level#find ${dir} -maxdepth ${level} -type f -name '*.cpp'#"},
                                       {"list files under certain dir but exclude ones under desc#find ${dir} -type f ! -path './desc/*'#"},
                                       {"remove files under certain dir but exclude files under certain subdir#find ${dir} -type f ! -path './${subdir}/*' -exec rm -f {} +#"}}},
                {"dir operations +", {{"list dirs under cur dir#find . -type d#"},
                                      {"list dirs under cur dir matches the name pattern recursively#find . -type d -name '*.cpp'#"},
                                      {"list dirs under cur dir doesnt match the name pattern recursively#find . -type d ! -name '*.cpp'#"},
                                      {"remove subdirs under certain dir but exclude level-1 subdir/files recursively match specific pattern#find ${dir} -maxdepth 1 -type d ! -path './${subdirname}' -exec rm -rf {} +#"}}},
                {"soft link operations +"}}
            },
            {"grep +", {
                {"search for matched pattern in file#grep '${pattern}' ${file}#"},
                {"search for matched pattern under dir#grep -r '${pattern}' ${dir}#"},
                {"*exclude dir when search for matched pattern under dir#grep -r --exclude-dir=${dir_pattern} '${pattern}' ${dir}#grep"},
                {"pattern collections +", {
                    {"search for text not matching regex in file/dir#grep -e ${pattern} ...#"},
                    {"search for text not matching regex (only output the matched part)#grep -oe ${pattern} ...#"},
                    {"search for text with regex wildcard supported#grep -E {regex_pattern}#"},
                    {"search for text with regex supported (only output the matched part)#grep -oE ${regex_pattern}#"}}}}}},
        },
    };
    return search_ptr;
}

#endif
