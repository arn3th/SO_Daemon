#ifndef DAEMON_H
#define DAEMON_H

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/fs.h>
#include <stdio.h>
#include <fcntl.h>

void create_daemon();

#endif