#ifndef RWFILE_H
#define RWFILE_H

#include <QFile>
#include <QPair>
class RWFile
{
public:
    RWFile(const QString &filename);

    void write(const QString &_username, const QString &_password);
    QPair<QString, QString> read();
private:
    QString username;
    QString password;
    QString filename;
};

#endif // RWFILE_H
