#include "rwfile.h"
#include <QTextStream>
RWFile::RWFile(const QString &_filename)
{
    filename = _filename;
}

void RWFile::write(const QString &_username, const QString &_password)
{
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << _username + " " + _password + "\n";
    }
}

QPair<QString, QString> RWFile::read()
{
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        in >> username >> password;
    }
    return QPair<QString, QString>(username, password);
}
