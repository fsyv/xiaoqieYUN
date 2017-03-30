#ifndef LINUXSERVER_TOOLS_TOOLS_H
#define LINUXSERVER_TOOLS_TOOLS_H

#include <unistd.h>
#include <stdio.h>

#ifdef __x86_64__
//64位
typedef unsigned long memlen_t;
#elif __i386__
//32位
typedef unsigned int memlen_t;
#endif

//内存查找
void *memstr(const void *src, memlen_t src_len, const void *des);

#endif //LINUXSERVER_TOOLS_TOOLS_H
