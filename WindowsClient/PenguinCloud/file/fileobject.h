#ifndef FILEOBJECT_H
#define FILEOBJECT_H

#include <QtCore>

class FileObject
{
public:
    FileObject(QString name, qint64 size, QDateTime dateTime);
    FileObject(QString name, QDateTime dateTime);
    virtual ~FileObject();

    QString getName() const;
    void setName(const QString &name);

    QDateTime getLatModiryTime() const;
    void setLatModiryTime(const QDateTime &latModiryTime);

    qint64 getSize() const;
    void setSize(const qint64 &i64Size);

protected:
    QString m_stName;
    QDateTime m_latModiryTime;
    qint64 m_i64Size;
};

#endif // FILEOBJECT_H
