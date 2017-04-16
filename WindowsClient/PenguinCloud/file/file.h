#ifndef FILE_H
#define FILE_H

#include "fileobject.h"

class File : public FileObject
{
public:
    File(QString name, qint64 size, QDateTime dateTime);
    File(const File &file);
    File();

    bool operator ==(const File &file) const;

    QString getMD5() const;
    void setMD5(const QString &value);

private:
    QString MD5;
};

#endif // FILE_H
