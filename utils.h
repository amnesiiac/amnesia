#ifndef UTILS_H_
#define UTILS_H_

// declarations
static char* trim_whitespaces(char *str);
char* getrealpath(const char* symlink, size_t len=100);

// ncurses fill fields blanks with spaces, trim appended spaces to get result
static char* trim_whitespaces(char *str){
    char *end;
    while(isspace(*str)){ // trim leading spaces
        str++;
    }
    if(*str == 0){ // if sll apaces
        return str;
    }
    end = str + strnlen(str, 128) - 1; // trim trailing spaces
    while(end > str && isspace(*end)){
        end--;
    }
    *(end+1) = '\0'; // end
    return str;
}

char* getrealpath(const char* symlink, size_t len){
    char abs_path[len];
    char actual[len+1];
    return realpath(symlink, NULL);
}

#endif

