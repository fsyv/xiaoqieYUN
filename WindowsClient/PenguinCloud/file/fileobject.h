#pragma once
#pragma execution_character_set("utf-8")

#include <QObject>
#include <QDateTime>

class FileObject : public QObject
{
    Q_OBJECT
public:
    FileObject(QString remoteName, qint64 size, QDateTime dateTime);
    FileObject(QString remoteName, QDateTime dateTime);
    virtual ~FileObject();

    QString getRemoteName() const;
    void setRemoteName(const QString &remoteName);

    QDateTime getLatModiryTime() const;
    void setLatModiryTime(const QDateTime &latModiryTime);

    qint64 getSize() const;
    void setSize(const qint64 &i64Size);

protected:
    //远程相对于用户名的路径
    QString m_stRemoteName;
    QDateTime m_latModiryTime;
    qint64 m_i64Size;
};

