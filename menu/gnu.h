#ifndef GNU_H
#define GNU_H

#include "base.h"

MenuItem* Method::get_gnu_ptr(){
    MenuItem* gnu_ptr = new MenuItem;
    gnu_ptr->name = "gnu";
    gnu_ptr->submenu = {
        {"gnu cmd +", {
            {"gnu tools manuals#https://www.gnu.org/manual/#"},
            {"sed +", {
                {"print lines to stdout with lineno in range of [start,end]#sed -n '${start},${end}p' ${file}#"},
                {"print lines to stdout with lineno in range of [start,start+incr]#sed -n '${start},+${incr}p' ${file}#"},
                {"derive lines match the pattern into out file#sed -n '/${pattern}/p' ${in} > ${out}#"},
                {"delete lines from file +", {
                    {"delete lines with matched pattern in place (some chars need to be escaped)#sed -i '/${pattern}/d' ${file}#"},
                    {"delete line by lineno in place (lineno count start from 1)#sed -i '${lineno}d' ${file}#"},
                    {"delete a range of line [start,end] in place (lineno count start from 1)#sed -i '${start},${end}d' ${file}#"},
                    {"delete all null lines in place (a null line has nothing)#sed -i '/^$/d' ${file}#"}}}}},
            {"awk +", {
                {"print content >=column for stdin in different line (replace col with num)#awk '{ for(i=${col}; i<=NF; i++) print $i}'#"},
                {"print content >=column for stdin in space separated same line (replace col with num)#awk '{ for(i=${col}; i<=NF; i++) printf \"%s \", $i; print \"\" }'#"}}},
            {"tee +", {
                {"show manual of tee (read from stdin, output to stdout & file)#man tee#"},
                {"accept stdout of cmd as stdin, redirect it to both cur stdout and file (used to make logs persistent)#${cmd} | tee -a ${file}#"}}},
            {"yes +", {
                {"show manual#yes --help#"},
                {"show full documentation#info coreutils yes#"},
                {"repeatly print string to stdout (ctrl+c to stop)#yes ${string}#"},
                {"delete all files without input yes for each possible file#yes | rm -i *.txt#"},
                {"write duplicate lines of string into file#yes ${string} | head -n 10 > ${file}#"},
                {"*use yes with pipe to enable auto input for interactive prompt (set +o pipefail)#yes | ${interactive_cmd}#yes"},
                {"*use yes with pipe to enable auto input for interactive prompt (set -o pipefail)#{ yes || :; } | ${interactive_cmd}#yes"}}},
            {"tty +", {{"show brief login info for current terminal: user tty logintime hostname#who am i#"},
                       {"show brief login info: user tty logintime hostname#who#"},
                       {"show detailed login info: user tty login-date idle-time jcpu-time pcpu-time process#w#"}}}}
        },
    };
    return gnu_ptr;
}

#endif
