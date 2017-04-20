#pragma once
#pragma execution_character_set("utf-8")

#include <QVector>
#include "network/msgtype.h"
typedef unsigned long memlen_t;

class Tools
{
public:
    Tools();
    static void *memstr(const void *src, memlen_t src_len, const void *des);
    static QVector<QStringList> getTableRow(QByteArray &byteArray);
    static FileType getFileType(const QString &filename);
    static QString sizeToString(const qint64 &fileSize);
};

