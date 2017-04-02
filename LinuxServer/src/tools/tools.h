#ifndef LINUXSERVER_TOOLS_TOOLS_H
#define LINUXSERVER_TOOLS_TOOLS_H

#include "stdio.h"

typedef unsigned long memlen_t;

//内存查找
void *memstr(const void *src, memlen_t src_len, const void *des);

#endif //LINUXSERVER_TOOLS_TOOLS_H
