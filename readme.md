### # preview
![usage preview](./hi.gif)


### # todo
!) make the max window size automatic follow the width & height of terminal window size.  
!) make the max tab width adaptive to the margin left on the right.  
!) when no test file to show, then no popup window action made, just stay there:  
!) let the popup menu use relative path, so that let the project portable.  
!) disable menu close when hitting enter on middle tab, only jump back to shell when current menu is the last one.  
!) try: make the editor like vim or just embeded nvim/vim inside.  
!) add help pages for showing how to control the shuttle panel.


### # restful design to organize the menu resources
nested menu resources should be organized in order like:

```text
object + resource + operations
```

rather than

```text
operations + object + resource
```


### # project structure

```txt
.
├── desc
├── form.h
├── jaro.h
├── leven.h
├── main.cpp
├── main.o
├── makefile
├── menu
│   ├── base.h
│   ├── blog.h
│   ├── cicd.h
│   ├── code.h
│   ├── crontab.h
│   ├── dev.h
│   ├── docker.h
│   ├── encryption.h
│   ├── filesys.h
│   ├── gnu.h
│   ├── http.h
│   ├── kernel.h
│   ├── latex.h
│   ├── mac.h
│   ├── menu.h
│   ├── misc.h
│   ├── network.h
│   ├── os.h
│   ├── performance.h
│   ├── process.h
│   ├── revision.h
│   ├── search.h
│   ├── sysmonitor.h
│   ├── term.h
│   ├── time_.h
│   ├── tmux.h
│   ├── tool.h
│   ├── transhell.h
│   ├── user.h
│   └── vim.h
├── out
├── popup.h
├── readme
└── utils.h

2 directories, 72 files
```


### # others
todo: pipe implementation in c conclusion  
ref: https://medium.com/swlh/understanding-pipes-in-unix-with-a-sample-implementation-9fe110d36412#1569

todo: a visual guide to caching inside gitlab ci/cd  
ref: https://about.gitlab.com/blog/2022/09/12/a-visual-guide-to-gitlab-ci-caching/
