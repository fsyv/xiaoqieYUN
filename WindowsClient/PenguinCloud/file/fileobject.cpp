#include "fileobject.h"

FileObject::FileObject(QString remoteName, qint64 size, QDateTime dateTime) :
    QObject(),
    m_stRemoteName(remoteName),
    m_latModiryTime(dateTime),
    m_i64Size(size)
{

}

FileObject::FileObject(QString remoteName, QDateTime dateTime) :
    FileObject(remoteName, 0LL, dateTime)
{

}

FileObject::~FileObject()
{

}

QString FileObject::getRemoteName() const
{
    return m_stRemoteName;
}

void FileObject::setRemoteName(const QString &remoteName)
{
    m_stRemoteName = remoteName;
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
