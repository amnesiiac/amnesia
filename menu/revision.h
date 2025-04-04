#ifndef REVISION_H
#define REVISION_H

#include "base.h"

MenuItem* Method::get_revision_ptr(){
    MenuItem* revision_ptr = new MenuItem;
    revision_ptr->name = "revision";
    revision_ptr->submenu = {
        {"revision +", {
            {"git <-> hg#https://wiki.mercurial-scm.org/GitConcepts#"},
            {"git +", {{"git init +", {{"*init git repo in current dir#git init#gitinit"},
                                       {"del git repo in current dir#rm -rf .git#"}}},
                       {"git config +", {{"list all config#git config --list#"},
                                         {"list system level config#git config --list --system#"},
                                         {"*list global level config#git config --list --global#gitconfig"},
                                         {"list local repo level config#git config --list --local#"},
                                         {"list config located at file#git config --list --file ${file}#"}}},
                       {"git clone +", {{"get repo by ssh from remote (no user/passwd needed)#git clone git@github.com:${project}.git#"},
                                        {"get repo by https from remote (user/passwd needed)#git clone https://github.com/${project}.git#"},
                                        {"get only a specific branch from remote#git clone -b ${branch} git@github.com:${project}.git#"}}},
                       {"git diff +", {{"show diff between wkdir vs staged#git diff#"},
                                       {"show diff between wkdir vs staged with colored text#git diff --color#"},
                                       {"show diff between wkdir vs staged without file deletions included#git diff --diff-filter=d#"},
                                       {"show diff between wkdir vs staged with colored word-by-word diff#git diff --color-words#"},
                                       {"show diff between staged vs committed#git diff --staged#"},
                                       {"show diff between any selected 2 files#git diff --no-index ${file1} ${file2}#"}}},
                       {"git show +", {{"show line changes of head#git show HEAD#"},
                                       {"show line changes of 2nd head#git show HEAD^#"},
                                       {"show line changes of certain commit#git show ${commitid}#"},
                                       {"show file changes of certain commit#git show --name-only ${commitid}#"},
                                       {"show file changes of list of commits#git show --name-only ${commitid1} ${commitid2} ${commitid3} ...#"},
                                       {"show content of a file at specified revision#git show ${commitid}:${pathtofile}#"}}},
                       {"git apply +", {{"apply the patch to workdir generated by git diff/show ${commit} > ${patch/diff}#git apply ${patch/diff}#"}}},
                       {"git format-patch +", {{"generate a patch of a range of commits#git format-patch ${startcommit}^..${endcommit} --stdout > ${xxx.patch}#"}}},
                       {"git am +", {{"creates commits by applying patches from git format-patch#git am ${xxx.patch}#"}}},
                       {"git add +", {{"add certain file's changes in wkdir to staged#git add ${file}#"},
                                      {"add changes recursively from cur wkdir to staged(ignore removal)#git add .#"},
                                      {"add changes of all wkdir to staged(hg addremove)#git add --all#"}}},
                       {"git rm +", {{"todo#git rm ${file}#"},
                                     {"todo#git rm -r $[dir}#"},
                                     {"remove file from git tracking cache without really del it#git rm --cached ${file}#"},
                                     {"remove dir from git tracking cache without really del it#git rm -r --cached ${dir}#"}}},
                       {"git status +", {{"show modified files in both working dir & staged#git status#"}}},
                       {"git commit +", {{"amend changes into the HEAD revision, modify the commit msg#git commit --amend#"},
                                         {"amend changes into the HEAD revision, needless to modify commit msg#git commit --amend --no-edit#"},
                                         {"show lastest commit of certain file in project#git rev-list -n 1 HEAD ${file}#"},
                                         {"show the changed files for certain commit id#git diff-tree --no-commit-id --name-only ${commit_id} -r#"},
                                         {"show [filemod, file hash of before state, file hash of current state, operation, filename] of certain commit#git diff-tree --no-commit-id ${commit_id} -r#"}}},
                       {"git time +", {{"show timestamp of latest commit of certain file in project#git rev-list -n 1 HEAD ${file} | xargs git show -s --format=%ai#"}}},
                       {"git reset +", {{"*unstage a file to wkdir#git reset ${file}#gitreset"},
                                        {"*unstage all files to wkdir#git reset#gitreset"},
                                        {"*reset workdir/index/commited to certain rev#git reset --hard ${revision}#gitreset"},
                                        {"*reset a range of committed to index (could be used for squash multiple pending commits)#git reset --soft ${revision}#gitreset"}}},
                       {"git outgoing: check between local cur branch with remote branch#git fetch && git log origin/${branchname}.. --oneline#"},
                       {"git incoming: check between local cur branch with remote branch#git fetch && git log ..origin/${branchname} --oneline#"},
                       {"git log +", {{"*show commits of a branch#git log ${branch}#gitlog"},
                                      {"*show commits of a branch in format: hash/date/message#git log --graph --pretty=\"%C(yellow) Hash: %h %C(blue)Date: %ad %C(red) Message: %s \" --date=iso ${branch}#gitlog"},
                                      {"*show commits of a branch in format: 1-line,graph,decorate#git log --oneline --graph --decorate ${branch}#gitlog"},
                                      {"*show commits in refs/ of a branch in format: 1-line,graph,decorate#git log --oneline --graph --decorate --all ${branch}#gitlog"},
                                      {"*show commits of a file in cur branch#git log --graph --oneline --decorate --follow ${file}#gitlog"},
                                      {"*compare branches: show commits of branchB not of branchA#git log ${branchA}..${branchB} --oneline#gitlog"},
                                      {"show reflog based on all commits#git log --reflog --patch#"},
                                      {"show reflog based on local recent commits#git log --reflog --no-walk --patch#"},
                                      {"*show reflog based on local recent commits#git log --reflog --oneline --no-walk#gitreset"}}},
                       {"git reflog +", {{"*show reflog based on the local changes (more fine-grained than commit)#git reflog#gitreset"}}},
                       {"git annotate +", {{"show annotations: commitid,author,date,content#git annotate --show-stats ${file}#"},
                                           {"shwo annotations for a range of lines: commitid,author,date,content#git annotate --show-stats -L ${startlineno},${endlineno}#"}}},
                       {"git fetch#git fetch#"},
                       {"git pull = git fetch + git merge#git pull#"},
                       {"git push +", {{"push commit to remote (the same branch as local)#git push -u origin#"},
                                       {"push commit to certain branch of origin#git push -u origin ${branch}#"},
                                       {"forcibly overwrite remote with local (same branch between local/remote)#git push -f ${remotename} $(git branch | awk '{print $2}')#"},
                                       {"forcibly overwrite remote with local (different branch between local/remote)#git push -f ${remotename} ${localbranch}:${remotebranch}#"},
                                       {"delete remote branch#git push ${origin} -d ${branch}#"}}},
                       {"git branch +", {{"*list local branches#git branch --list#gitbranch"},
                                         {"*list remote branches#git branch --list -r#gitbranch"},
                                         {"*list local & remote branches#git branch --list -a#gitbranch"},
                                         {"*list local & remote branches (verbose)#git branch --list -av#gitbranch"},
                                         {"*list local & remote branches (complete)#git branch --list -avv#gitbranch"},
                                         {"fetch remote branch to local and switch to it#git fetch origin ${remote_branch} && git checkout ${remote_branch}#"},
                                         {"create local branch based on certain commit id (switch to it)#git checkout -b ${branch_name} ${commit_id}#"},
                                         {"*rename current branch name as ${branch}#git branch -m ${branch}#gitbranch"},
                                         {"*rename (force) current branch name as ${branch}#git branch -M ${branch}#gitbranch"},
                                         {"*del local branch (origin can be omitted)#git branch -d ${origin}/${branch_to_del}#gitbranch"},
                                         {"*del remote branch#git branch -d -r ${origin}/${branch_to_del}#gitbranch"}}},
                       {"git checkout +", {{"*discard wkdir changes & update wkdir to cur branch#git checkout -f#gitcheckout"},
                                           {"*discard wkdir changes & update wkdir to certain branch#git checkout -f -b ${branch}#gitcheckout"},
                                           {"*change wkdir/index to certain branch & point HEAD at the branch#git checkout ${branch}#gitcheckout"},
                                           {"*create new branch & startup at commit#git checkout -b $(branch} ${commit}#gitcheckout"},
                                           {"*revert file1/file2 in wkdir/index to certain commit#git checkout ${commit} -- ${file1} ${file2}...#gitcheckout"}}},
                       {"git rebase +", {{"*rebase upstream changes with cur working branch#git rebase ${upstream_branch}#gitrebase"},
                                         {"*rebase upstream changes with specified branch#git rebase ${upstream_branch} ${working_branch}#gitrebase"},
                                         {"rebase upstream changes with cur working branch in interative mode#git rebase -i ${upstream_branch} ${working_branch}#"},
                                         {"abort the rebasing after interrupt with ctrl+c#git rebase --abort#"},
                                         {"drop the changes of a commit by edit the commit interactively#git rebase -i ${revision} && pick -> drop#"},
                                         {"*rebase local code from upstream#section: how to rebase with upstream#gitrebase"}}},
                       {"git remote +", {{"list configured remote name:url#git remote -v#"},
                                         {"list verbose remote info (urls, head branch, branches)#git remote show origin#"},
                                         {"init remote with name:url for local repo (dryrun if existed)#git remote add ${remote_name} ${remote_repo_url.git}#"},
                                         {"set remote name:url for local repo (replace if existed, fail if no remote)#git remote set-url ${remote_name} ${remote_repo_url.git}#"}}},
                       {"git describe +", {{"show most recent tag reachable for cur commit (abbrev=0 to show only tag without hash postfix)#git describe --tags --abbrev=0#"},
                                           {"show most recent tag reachable for certain commit (abbrev=0 to show only tag without hash postfix)#git describe --tags --abbrev=0 ${commitid}#"}}},
                       {"git rev-parse +", {{"show full hash value of certain commit (e.g. HEAD,HEAD~1...)#git rev-parse ${commit}#"},
                                            {"show shortened hash value of certain commit (e.g. HEAD,HEAD~1...)#git rev-parse --short ${commit}#"}}},
                       {"git ls-tree +", {{"show all traced file names non-recursively for a commit#git ls-tree --name-only ${commit}#"},
                                          {"show all traced file names recursively for a commit#git ls-tree --name-only -r ${commit}#"}}}
					  }},
            {"hg +", {{"hg help +", {{"show available hg format templates#hg help templates#"},
                                     {"show help page for hg subcommand(e.g. hg help diff)#hg help ${subcommand}#"}}},
                      {"*set ~/.hgrc#hgrc content#hgrc"},
                      {"show path for remote repositories#hg path#"},
                      {"hg head +", {{"show all open head in current repo#hg head#"},
                                     {"show all descendant head from start revision#hg head -r ${rev}#"},
                                     {"show all topological head(head without child)#hg head -t#"},
                                     {"show all active head#hg head -a#"},
                                     {"show all closed head#hg head -c#"}}},
                      {"hg diff +", {{"show diff of file(wkdir) with its parent#hg diff ${file}#"},
                                     {"show diff of wkdir with certain revision#hg diff -r ${rev}#"},
                                     {"show diff of file(wkdir) with certain revision#hg diff -r ${rev} ${file}#"},
                                     {"show changes of certain revision#hg diff -c ${rev}#"},
                                     {"show changes stats of certain revision (list changed files with changed line count)#hg diff -c ${rev} --stat#"},
                                     {"show changes of certain file in certain revision#hg diff -c ${rev} ${file}#"}}},
                      {"hg annotate +", {{"show author of each line in certain file#hg annotate -u ${file}#"},
                                         {"show author of each line in certain revision#hg annotate -r ${rev} -u ${file}#"},
                                         {"show author / revision / changeset / lineno of certain revision#hg annotate -u -n -c -l ${file}#"}}},
                      {"hg blame +", {{"show user / date / revision info of a file in certain revsion#hg blame --user --date --number ${file}#"}}},
                      {"hg commit +", {{"commit current changeset#hg commit#"},
                                       {"commit current changeset with messages#hg commit -m ${message}#"},
                                       {"commit changes of wkdir to current parent#hg commit --amend#"},
                                       {"show all commits related to certain line of a file (specify line by pattern)#hg grep --all '${reg_pattern}' ${filename}#"}}},
                      {"hg revert +", {{"tips for testing temporary changes#revert wkdir to ref changeset, do some tests, hg update -C to fallback#"},
                                       {"revert certain file in wkdir to state of certain revision#hg revert -r ${rev} ${file}#"},
                                       {"revert all files in wkdir to state of certain revision#hg revert -r ${rev} --all#"}}},
                      {"hg pull +", {{"pull all incoming changesets to local#hg pull#"},
                                     {"pull all incoming changesets till certain revision to local#hg pull -r ${rev}#"}}},
                      {"hg update +", {{"update cur par rev to a given rev (with workdir contains changes from cur par to given rev)#hg update -r ${rev}#"},
                                       {"update cur par rev to a given rev (with workdir cleaned)#hg update -C -r ${rev}#"},
                                       {"discard changes in wkdir, back to the state of parent rev (no backup)#hg update -C#"}}},
                      {"hg strip +", {{"remove certain revision#hg strip -r ${rev}#"},
                                      {"remove certain revision without backups (usually used after hg update -C -r ${rev})#hg strip -r ${rev} --no-backup#"},
                                      {"restore stripped changeset with the backup file generated by hg#see hg unbundle ${backup} for details#"}}},
                      {"hg export+", {{"export changes of parent revision to screen#hg export#"},
                                      {"export changes of parent revision to file#hg export > ${file}#"},
                                      {"export changes of certain revision to screen#hg export -r ${rev}#"},
                                      {"export changes of certain revision to file#hg export -r ${rev} > ${file}#"}}},
                      {"hg import +", {{"import diff patch and create commit on working head#hg import ${patch}#"},
                                       {"import diff patch to wkdir without commit#hg import --no-commit ${patch}#"}}},
                      {"hg rebase +", {{"rebase revision(src) to the top of another(dst)#hg rebase -s ${rev_src} -d ${rev_dst}#"},
                                       {"rebase revision(src) to the top of another(dst) with merge tool#hg rebase -s ${rev_src} -d ${rev_dst} --tool=vimdiff#"},
                                       {"abort current rebase operation#hg rebase --abort#"},
                                       {"swap the position of two changeset#see desc for details#hgswap#"}}},
                      {"hg backout +", {{"backout(del) latest revision, no merge needed#hg backout -r ${latestrev}#"},
                                        {"backout middle revision, merge needed#hg backout -r ${midrev}#"}}},
                      {"hg status +", {{"show changed files of certain revision#hg status --change ${rev}#"},
                                       {"show changed files of wkdir with certain revision#hg status --rev ${rev}#"},
                                       {"remove all untacked file/dir#cd project rootdir && hg status --unknown --no-status | xargs rm -rf#"}}},
                      {"hg log + (commit info)", {{"show recent num commits#hg log -l ${num}#"},
                                                  {"show commit msg of a revision#hg log -r ${rev}#"},
                                                  {"show commit msg of revision verbosely#hg log -r ${rev} -v#"},
                                                  {"show commits msg list of certain maintainer#hg log --user ${usr}#"},
                                                  {"show commits msg list of certain maintainer in brief mode#hg log --user ${usr} -q#"},
                                                  {"show maintainer list#hg log --template \"{author}\\n\" | sort | uniq#"},
                                                  {"show commits list of some date#hg log --date ${2022-10-20}#"},
                                                  {"show commits list of certain file#hg log ${file}#"},
                                                  {"show commits graph#hg log -G#"},
                                                  {"show brief commits with format#hg log -T \"\\t{date|shortdate}\\t[{rev}]\\t{author|user}\\t{desc}\\n\"#"},
                                                  {"show brief commits with format in graph mode#hg log -G -T \"\\t{date|shortdate}\\t[{rev}]\\t{author|user}\\t{desc}\\n\"#"},
                                                  {"show commit msg & code changes#hg log -pr ${rev}#"}}},
                      {"hg cat +", {{"show file content of certain revision#hg cat -r ${rev} ${file}#"}}},
                      {"hg tag +", {{"show help page for hg tag#hg help tag#"},
                                    {"tag a certain revision by create commit#hg tag -r ${rev} ${tagname}#"},
                                    {"remove certain tag by create a commit#hg tag --remove ${tagname}#"}}},
                      {"hg in/out +", {{"show all changeset pending to be pushed#hg outgoing(out)#"},
                                       {"show all changeset pending to be pulled#hg incoming(in)#"}}},
                      {"hg convert +", {{"*extract commit history of a subfolder from a wholesome repo#hg convert --filemap ${mapfile} ${original_proj_dir} ${new_subrepo_dir}#hgconvert"}}}}}}
        }
    };
    return revision_ptr;
}

#endif

