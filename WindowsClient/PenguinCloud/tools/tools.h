#ifndef TOOLS_H
#define TOOLS_H

typedef unsigned long memlen_t;

class Tools
{
public:
    Tools();
    static void *memstr(const void *src, memlen_t src_len, const void *des);
};

#endif // TOOLS_H
