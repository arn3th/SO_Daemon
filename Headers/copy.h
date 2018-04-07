#ifndef COPY_H
#define COPY_H

#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>

#include "conf.h"


void work(conf);

void make_copy(char*, char*, char*, off_t);
void copy_normal(char*, char*);
void copy_mmap(char*, char*);

#endif