#ifndef FILE_H
#define FILE_H

#include "fileobject.h"

class File : public FileObject
{
public:
    File(QString name, qint64 size, QDateTime dateTime);
};

#endif // FILE_H
