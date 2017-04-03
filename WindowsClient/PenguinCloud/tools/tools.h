#ifndef TOOLS_H
#define TOOLS_H

#include <QVector>

typedef unsigned long memlen_t;

class Tools
{
public:
    Tools();
    static void *memstr(const void *src, memlen_t src_len, const void *des);
    static QVector<QStringList> getTableRow(QByteArray &byteArray);
};

#endif // TOOLS_H
