#ifndef CONF_H
#define CONF_H

#include <stdlib.h>
#include <stdio.h>
#include "args.h"

typedef struct {
    char s_dir[FILENAME_MAX];
    char d_dir[FILENAME_MAX];
    long time;
    int r;
    off_t mmap_size;
} conf;

conf get_conf();
conf build_config(int, char**);
#endif