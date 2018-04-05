#include "check.h"


int check_dir(const char * name){
    DIR * dir = opendir(name);
    if(dir){
        closedir(dir);
        return 1;
    }
    return 0;
}

int dir_in_dir(const char * src, const char * dest){

    char *path_1, *path_2;
    char buf_1[128], buf_2[128];

    path_1 = realpath(src, buf_1);
    path_2 = realpath(dest, buf_2);
    int l_1 = strlen(path_1);
    int l_2 = strlen(path_2);
    int length = l_1 > l_2 ? l_2 : l_1;
    if(strncmp(path_1, path_2, length) == 0)
        return 1;
    else
        return 0;
}

