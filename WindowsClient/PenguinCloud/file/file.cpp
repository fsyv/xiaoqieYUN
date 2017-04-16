#include "file.h"

File::File(QString name, qint64 size, QDateTime dateTime) :
    FileObject(name, size, dateTime)
{

}

File::File(const File &file) :
    File(file.getName(), file.getSize(), file.getLatModiryTime())
{
    MD5 = file.getMD5();
}

File::File() :
    File(QString(""), 0, QDateTime::currentDateTime())
{
    MD5 = QDateTime::currentDateTime().toString();
}

bool File::operator ==(const File &file) const
{
//    if(MD5 == file.getMD5())
//    {
//        return true;
//    }

    if(m_stName == file.getName())
        return true;
    return false;
}

QString File::getMD5() const
{
    return MD5;
}

void File::setMD5(const QString &value)
{
    MD5 = value;
}
