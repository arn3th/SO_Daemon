#ifndef CONF_H
#define CONF_H

#include <stdlib.h>

typedef struct {
    char* s_dir;
    char* d_dir;
    long time;
    int r;
    size_t mmap_size;
} conf;

conf get_conf();

#endif