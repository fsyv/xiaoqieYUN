#include "file.h"

#include "../stable.h"


File::File(QString localName, QString remoteName, qint64 size, QDateTime dateTime) :
    FileObject(remoteName, size, dateTime)
{
    m_stLocalName = localName;
}

File::File(const File &file) :
    File(file.getLocalName(), file.getRemoteName(), file.getSize(), file.getLatModiryTime())
{

}

File::File(QString localName, QString remoteName) :
    File(localName, remoteName, 0, QDateTime::currentDateTime())
{

}

File::File(QString remoteName) :
    File(QString(""), remoteName)
{

}

File::File() :
    File(QString(""), QString(""), 0, QDateTime::currentDateTime())
{

}

File::~File()
{

}

bool File::operator ==(const File &file) const
{
    //如果远程相对文件名相同视为同一个文件
    if(m_stRemoteName == file.getRemoteName())
        return true;

    if(MD5 == file.getMD5())
        return true;

    return false;
}

QByteArray File::getMD5() const
{
    return MD5;
}

void File::setMD5(const QByteArray &value)
{
    MD5 = value;
}

QString File::getLocalName() const
{
    return m_stLocalName;
}

void File::setLocalName(const QString &localName)
{
    m_stLocalName = localName;
}

void File::updateMD5()
{
    //将大小为0的为0的文件MD5设置为当前时间
    if(m_stLocalName.isEmpty())
    {
        MD5 = QDateTime::currentDateTime().toString("yyyy-MM-dd.hh:mm:ss:zzz").toUtf8();
    }
    else
    {
        QFile file(m_stLocalName);

        if(file.open(QIODevice::ReadOnly))
        {
            QCryptographicHash md5(QCryptographicHash::Md5);

            setSize(file.size());

            qint64 loadSize = 64 * 1024;

            while(!file.atEnd())
                md5.addData(file.read(loadSize));

            MD5 = md5.result();
        }
        else
        {
            //打开文件失败
            MD5 = QDateTime::currentDateTime().toString("yyyy-MM-dd.hh:mm:ss:zzz").toUtf8();
        }
    }
}
