#ifndef CODE_H
#define CODE_H

#include "base.h"

MenuItem* Method::get_code_ptr(){
    MenuItem* code_ptr = new MenuItem;
    code_ptr->name = "code";
    code_ptr->submenu = {
        {"code +", {
            {"language +", {
                {"golang +", {{"show go help page#go --help#"},
                              {"env +", {{"show go env help page#go help env#"},
                              {"list go env variables#go env#"},
                              {"show certain env variable value#go env ${env_var_name}#"},
                              {"change env var value (nothing change if value not valid)#go env -w ${env}=${value}#"},
                              {"usefull env configs +", {{"module are enabled regardless of whether a go.mod file is present, any directory without a go.mod file becomes its own module#go env -w GO111MODULE=on#"},
                                                         {"modules are enabled if go.mod is present in cur/parent dir#go env -w GO111MODULE=auto#"},
                                                         {"modules are disabled, use GOPATH for all imports#go env -w GO111MODULE=off#"}}}}},
                              {"go mod +", {{"show help page#go help mod#"},
                                            {"init cur dir as a module with name#go mod init ${modname}#"},
                                            {"peeling module off cur dir#rm go.mod go.sum#"},
                                            {"tidy modules (add missing & remove unused mods & adapt mods according to newly golang version)#go mod tidy#"},
                                            {"show src -> dependency pairs of cur module#go mod graph#"}}},
                              {"go get +", {{"show help page#go help get#"},
                                            {"add package to cur module#go get ${pkgname}#"},
                                            {"remove package downloaded#cd $GOPATH && del the related dir#"}}},
                              {"go doc +", {{"show src code of a symbolf#go doc -src client.NewClientWithOpts#"},
                                            {"show oneline doc of symbos in golang package#go doc -short github.com/docker/docker/api/types/container#"},
                                            {"show full doc of golang package#go doc -all github.com/docker/docker/api/types/container#"}}},
                              {"go build +", {{"build the program#go build ${program.go}#"},
                                              {"show help page#go help build#"},
                                              {"show build cmd flow without actually build the program#go build -n ${program.go}#"},
                                              {"show build cmd flow and build the program#go build -x ${program.go}#"},
                                              {"build the program with data racing detection annotations#go build -race ${program.g}#"}}},
                              {"go asm +", {{"print asm using src code#go build -gcflags -S ${program.go}#"},
                                            {"print asm purely#go tool objdump ${binary} >asm 2>&1#"},
                                            {"print asm with golang src code#go tool objdump -S ${binary} >asm 2>&1#"}}},
                              {"code format +", {{"show auto format tool help#gofmt --help#"},
                                                 {"format go program and output in stdout#gofmt ${path/test.go}#"},
                                                 {"format go program in place#gofmt -w ${path/test.go}#"}}}}},
                {"rust +", {{"rustc +", {{"show help page or rustc#rustc --help#"},
                                         {"compile single rc src#rustc ${main.rc}#"}}},
                            {"cargo +", {{"show help page#cargo --help#"},
                                         {"create scaffold for new project#cargo new ${project_name}#"}}}}},
                {"python +", {{"pytest +", {{"show test result of ut script#pytest test_xxx.py#"},
                                            {"show test result with program stdout of ut test#pytest -rP test_xxxx.py#"}}},
                              {"syntax +", {{"formatted string while keep {{ & }} persistent (co-work with jinja2 template)#f'{{{{ a formatted str {placeholder_var} }}}}' -- will output -> {{ a formatted str ${value of the var} }}#"}}}}},
                {"shell +", {{"setup env variable for current shell#export ${var}=${val}#"},
                             {"unset env variable for current shell#unset ${var}#"},
                             {"setup env variable for all shell#echo \"export ${var}=${val}\" >> ~/.bashrc && source ~/.bashrc#"}}},
                {"c +"},
                {"cpp +"},
                {"json +"},
                {"yaml +", {{"*multiline string in yaml##yaml"}}}}
            },
            {"debug +", {
                {"gdb +", {{"show manual#http://www.yolinux.com/TUTORIALS/GDB-Commands.html#"},
                           {"enable gdb in tui mode#sudo gdb -tui out#"},
                           {"polling the win#ctrl+x; o#"},
                           {"select source code win#focus src#"},
                           {"select commandline win#focus cmd#"},
                           {"select assembly win#focus asm#"},
                           {"select register win#focus reg#"},
                           {"execute exact 1 line in source code#s (step)#"},
                           {"execute 1 line in source code#n (next)#"},
                           {"refresh tui win#ctrl+l#"},
                           {"call functions to check the result#call func(para1, para2...)#"},
                           {"disassemble 100bytes of instructions after $pc#disassemble $pc,+100#"},
                           {"disassemble 100bytes of instructions after function (e.g. main)#disassemble main,+100#"},
                           {"break at function#break ${function_name}#"}}},
                {"pdb +", {{"list 11 lines arround current execution line#l.#"},
                           {"list code in range of [startline, endline]#l ${startline},${endline} (l 146,170)#"},
                           {"list code in range of [startline, startline+count] (count<startline)#l ${startline},${+count} (l 146,20)#"},
                           {"list lines appended to current shown context lines#<Enter>#"},
                           {"breakpoints +", {{"set pdb init breakpoint#import pdb; pdb.set_trace()#"},
                                              {"set breakpoint at line num 80#break 80#"},
                                              {"list all breakpoint with sequence number#b#"},
                                              {"clear certain breakpoint#clear ${breakpoint sequence number}#"}}},
                           {"continue execution (no-following func jump)#n#"},
                           {"continue execution (following func jump)#s#"},
                           {"continue execution (stop untill next breakpoint)#c#"},
                           {"jump back/forward to certain line & continue execution#j ${lineno}#"},
                           {"jump to function return clause#r#"},
                           {"show stacktrace (call sequence)#w or where#"},
                           {"show function arguments#a#"}}},
                {"dlv +", {{"golang debugger doc#https://github.com/go-delve/delve/tree/master/Documentation#"},
                           {"config vim as dlv default editor by cmd edit (vi is not correct supported)#export DELVE_EDITOR=vim#"},
                           {"config the number of line range displayed by cmd list#config source-list-line-count 20#"},
                           {"debug golang program with option#dlv debug --check-go-version=false ${program.go} -- -option1 -option2 'fuck'#"},
                           {"list a range of src code arround program:line 20#list ${program.go}:20#"},
                           {"list certain function in certain package#list ${package}.${func}#"},
                           {"edit or show the program lines using edtior configured#edit ${program.go}:20#"}}},
                {"strace +", {{"trace system calls as the cmd executing (follow forks & output inline)#strace -e trace=file,open,read,write -f ${cmd_to_follow}#"},
                              {"trace system calls as the cmd executing (follow forks & output to different file)#strace -e trace=file,open,read,write -ff ${cmd_to_follow}#"}}},
                {"valgrind +", {{"show manual#man valgrind#"},
                                {"use memcheck tool for purpose of memory leak check#valgrind --tool=memcheck --leak-check=full ${path_to_program}#"}}}},
            },
            {"compilation +", {
                {"elf +", {{"search for symbol from binary by inspecting its elf format#readelf -s --wide ${binary} | grep ${symbolname}#"}}}}}},
        },
    };
    return code_ptr;
}

#endif
