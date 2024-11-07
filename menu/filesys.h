#ifndef FILESYS_H
#define FILESYS_H

#include "base.h"

MenuItem* Method::get_filesys_ptr(){
    MenuItem* filesys_ptr = new MenuItem;
    filesys_ptr->name = "filesys";
    filesys_ptr->submenu = {
        {"file & filesystem +", {
            {"file operations +", {{"file permissions +", {{"change owner:group +", {{"change owner:group recursively for dir/subdir#sudo chown -R ${owner}:${group} ${dir}#"}}},
                                                           {"change rwx +"}}},
                                   {"file time +", {{"set file atime/mtime as date:time#touch -d ${date:-2023-11-22} ${time:-10:27:46} ${file}#"}}},
                                   {"file type#file ${filename}#"},
                                   {"file attributes +", {{"add attribute to the file#setfattr -n ${key} -v ${value} ${path_to_file}#"},
                                                          {"get attribute of the file#getfattr -d ${path_to_file}#"},
                                                          {"del attribute of the file#setfattr -x ${key} ${path_to_file}#"}}},
                                   {"list size of all file/dir sorted under certain dir#du -ah --max-depth=1 | sort -h#"},
                                   {"dd +", {{"show manual (tool to copy, covert, format file)#man dd#"},
                                             {"write mac addr to offset (num) of file (bs: 1 byte each time, notrunc: keep the rest untouched)#echo -n -e '{mac_addr_bytes}' | dd of=${output_file} bs=1 seek=${num} conv=notrunc#"}}}}},
            {"dir operations +", {{"create dir under $PWD#mkdir ${dirname}#"},
                                  {"create dir under $PWD (recursively + no err even exist)#mkdir -p main/sub/last#"},
                                  {"create dir under / (recursively + no err even exist)#mkdir -p /main/sub/last#"},
                                  {"list size of all dirs sorted at certain path#du -h --max-depth=1 | sort -h#"},
                                  {"dir stack +", {{"list dirs in directory stack (the tip of dir stack is always cur dir)#dirs#"},
                                                   {"clear all directory stack#dirs -c#"},
                                                   {"switch the tip (cur dir) & the 2nd dir in dir stack (switch between 2 dir)#pushd#"},
                                                   {"push certain dir into stack top (set as cur dir)#pushd ${dir}#"},
                                                   {"set dir stack tip dir as certain dir (switch to certain dir)#pushd +n#"}}}}},
            {"remove file/dir +", {{"remove all except for certain object in certain dir#shopt -s extglob && rm -rf !(${folder or file name})#"},
                                   {"remove file startwith hypen '-'#rm ./${-filename} or rm -- ${-filename}#"}}},
            {"ln +", {{"create symbolic link files#ln -s ${abspath_to_origin_file} ${path_to_target_link}#"}}},
            {"readlink +", {{"get 1 level deep softlink target of current file/dir#readlink ${softlink}#"},
                            {"get final end softlink target of current file/dir#readlink -f ${softlink}#"}}},
            {"lsof +", {{"show manual of lsof#man lsof#"},
                        {"show all open fd info (cmd, pid, tid, user, fd, type, device, size/off, node, name)#lsof#"},
                        {"show all open fd info for certain user#lsof -u ${user}#"},
                        {"show all open fd info for certain process#lsof -p ${pid}#"},
                        {"show all open fd info for processes executing the cmd that begins with xxx#lsof -c ${xxx}#"},
                        {"show all open fd info under certain dir#lsof +D ${dir}#"},
                        {"show all open fd info belong to network address: [46][protocol][@hostname|hostaddr][:service|port] (e.g. lsof -i 4tcp@0:50542)#lsof -i [46][protocol][@hostname|hostaddr][:service|port]#"}}},
            {"zip/unzip +", {{"zip the dir to xxx.zip#zip -r ${zipfile}.zip ${dirtozip}#"},
                             {"unzip the xxx.zip#unzip ${zipfile}.zip#"},
                             {"unzip the xxx.zip to certain folder#unzip ${zipfile}.zip -d ${destdir}#"},
                             {"split input xxx.zip to serverl trunks<=size (xxx.zip-aa, xxx.zip-ab...)#split -b ${size} ${xxx.zip} ${xxx.zip-}#"},
                             {"recombinate zip trunks (xxx.zip-aa, xx.zip-ab...) back to xxx.zip#cat ${xxx.zip-*} ${xxx.zip}#"}}},
            {"tar/untar +", {{"untar the content of tar#tar -xvf ${xxx.tar}#"},
                             {"untar the content of tar.gz (gzip)#tar -xzvf ${xxx.tar.gz}#"},
                             {"untar the content of tar.bz2 (bzip2)#tar -xjvf ${xxx.tar.bz2#"},
                             {"tar files under dir using gzip (tar.gz)#tar -czvf ${xxx.tar.gz} ${dir}#"},
                             {"tar files under dir but excluding files under certain folder using gzip#tar --exclude='*/${foldername}/*' -zcvf ${out.tgz} ${indir}#"}}},
            {"tree +", {{"show manual#man tree#"},
                        {"show contents of certain depth in tree-format#tree -L ${num_of_layers_to_show}#"}}},
            {"scp +", {{"copy dir from local:dir to server:path#scp -r ${dir} ${user}@${ip}:${path}#"},
                       {"copy file from local:file to server:path#scp ${file} ${user}@${ip}:${path}#"},
                       {"copy dir from server:dir to local:path#scp -r ${user}@${ip}:${dir} ${path}#"},
                       {"copy file from server:file to local:path#scp ${user}@${ip}:${file} ${localpath}#"}}},
            {"rsync +", {{"*sync all dir/file in source dir to target (e.g. rsync -Pcauv /repo/metung/devtools/hostfw .)#rsync -Pcauv ${source_dir} ${target_dir}#rsync"},
                         {"*show all dir/file in source dir that need to be synced (dry-run)#rsync -Pcauvn ${source_dir} ${target_dir}#rsync"}}},
            {"mount +", {{"show mount info of all filesystems#mount#"}}},
            {"findmnt +", {{"show mount info of a specific filesystem for all source in graphic format (TARGET, SOURCE, FSTYPE, OPTIONS)#findmnt --target ${dir}#"},
                           {"show mount info of a specific filesystem for all source in df format (TARGET, SOURCE, FSTYPE, OPTIONS)#findmnt --df --target ${dir}#"},
                           {"show certain column raw data without headings for a given dir (include TARGET, SOURCE, FSTYPE, OPTIONS)#findmnt -n -o ${column} --target ${dir}#"}}},
            {"df +", {{"show [Filesystem, Size, Used, Avail, Use%, Mounted on] of a dir#df -h ${dir}#"},
                      {"show [Filesystem, Inodes, IUsed, IFree, IUse%, Mounted on] of a dir#df -ih ${dir}#"},
                      {"show file system type of certain dir#df -T ${dir}#"}}},
            {"du +", {{"list file space usage of each item under dir (largest on bottom)#du -h ${dir} | sort -h#"},
                      {"list file space usage of each item under dir (smallest on bottom)#du -h ${dir} | sort -hr#"},
                      {"list disk storage takeup by each user (from high to low, need su/sudo)#cd /home && du -d 1 -h | sort -hr#"},
                      {"list top-25 disk storage takeup folders start of all depth from cur dir (from high to low, need su/sudo)#du -xkh | sort -hr | head -25#"},
                      {"list top-25 disk storage takeup folder of all depth from cur dir (from low to high, need su/sudo)#du -xkh | sort -h | tail -25#"}}}}},
    };
    return filesys_ptr;
}

#endif
