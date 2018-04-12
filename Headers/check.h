#ifndef CHECK_H
#define CHECK_H

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <utime.h>
#include <time.h>
#include <syslog.h>

#include "conf.h"


int check_dir(const char*);
int dir_in_dir(const char*, const char*);

int exists(char*);
void rm_files(conf);
void recursive_rm(char*);

off_t check_size(char*);
int compare_time(char*, char*);
void change_time(char*, char*);
#endif