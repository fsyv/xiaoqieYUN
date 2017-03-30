#ifndef LINUXSERVER_TOOLS_TOOLS_H
#define LINUXSERVER_TOOLS_TOOLS_H

#include <unistd.h>

//内存查找signed
void *memstr(const void *src, u_int64_t src_len, const char *des);
//内存查找unsigned
void *memustr(const void *src, u_int64_t src_len, const unsigned char *des);

#endif //LINUXSERVER_TOOLS_TOOLS_H
