#ifndef ARGS_H
#define ARGS_H

#include <math.h>
#include <string.h>
#include "conf.h"

int to_digit(char);
int parse(char*);
int set_time(char**, int, int, long int*);
int set_mmap(char**, int, int, size_t*);



#endif