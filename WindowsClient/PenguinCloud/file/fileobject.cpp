#include "fileobject.h"

FileObject::FileObject(QString name, qint64 size, QDateTime dateTime) :
    m_stName(name),
    m_i64Size(size),
    m_latModiryTime(dateTime)
{

}

FileObject::FileObject(QString name, QDateTime dateTime) :
    FileObject(name, 0LL, dateTime)
{

}

FileObject::~FileObject()
{

}

QString FileObject::getName() const
{
    return m_stName;
}

void FileObject::setName(const QString &name)
{
    m_stName = name;
}

QDateTime FileObject::getLatModiryTime() const
{
    return m_latModiryTime;
}

void FileObject::setLatModiryTime(const QDateTime &latModiryTime)
{
    m_latModiryTime = latModiryTime;
}

qint64 FileObject::getSize() const
{
    return m_i64Size;
}

void FileObject::setSize(const qint64 &i64Size)
{
    m_i64Size = i64Size;
}
