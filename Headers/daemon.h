#ifndef DAEMON_H
#define DAEMON_H

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/fs.h>
#include <stdio.h>
#include <fcntl.h>

/**
\brief przeistacza program w demona
*/
void create_daemon();

#endif