#ifndef CHECK_H
#define CHECK_H

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "conf.h"

/*
typedef struct {
    file_inf * next;
    char * path;
    char * name;
    int type; //8 - regular file, 4 - directory

} file_inf; */
int check_dir(const char*);
int dir_in_dir(const char*, const char*);

int exists(char*);
void rm_files();

#endif