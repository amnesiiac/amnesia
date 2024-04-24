#ifndef BLOG_H
#define BLOG_H

#include "base.h"

MenuItem* Method::get_blog_ptr(){
    MenuItem* blog_ptr = new MenuItem;
    blog_ptr->name = "blog";
    blog_ptr->submenu = {
        {"blog +",
            {{"twistefatezzz +", {
                {"edit twistfatezzz blog#cd ~/twistfatezz.github.io"},
                {"start twistfatezzz jekyll server#jekyll serve"}}},
             {"melon +", {
                {"edit melon blog dockerfile#nvim /User/mac/paper/Dockerfile#"},
                {"edit melon blog#nvim /Users/mac/paper/blog/#"},
                {"start melon jekyll server#docker run -it --rm -p 4000:4000 -w=/paper -v /Users/mac/paper/blog/:/paper -h melon blog bundle exec jekyll serve --host 0.0.0.0#"}}}}}
    };
    return blog_ptr;
}

#endif
