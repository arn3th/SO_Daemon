#ifndef CONF_H
#define CONF_H

#include <stdlib.h>
#include <stdio.h>
#include "args.h"

typedef struct {
    char* s_dir;
    char* d_dir;
    long time;
    int r;
    off_t mmap_size;
} conf;

conf get_conf();
conf build_config(int, char**);

#endif