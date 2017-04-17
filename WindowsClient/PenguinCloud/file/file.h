#ifndef FILE_H
#define FILE_H

#include "fileobject.h"

class File : public FileObject
{
    Q_OBJECT
public:
    File(QString localName, QString remoteName, qint64 size, QDateTime dateTime);
    File(const File &file);
    File(QString localName, QString remoteName);
    File();

    bool operator ==(const File &file) const;

    QByteArray getMD5() const;
    void setMD5(const QByteArray &value);

    QString getLocalName() const;
    void setLacalName(const QString &localName);

    void updateMD5();

private:
    //本地绝对路径
    QString m_stLocalName;
    QByteArray MD5;
};

#endif // FILE_H
