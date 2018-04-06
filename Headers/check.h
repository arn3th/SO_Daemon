#ifndef CHECK_H
#define CHECK_H

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include "conf.h"


int check_dir(const char*);
int dir_in_dir(const char*, const char*);

int exists(char*);
void rm_files(conf);
void recursive_rm(char*);
#endif