#ifndef CHECK_H
#define CHECK_H

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int check_dir(const char*);
int dir_in_dir(const char*, const char*);

#endif