#include "loadfile.h"

#include <QUrl>
#include <QFile>
#include <QFileInfo>
#include <QNetworkReply>

LoadFile::LoadFile(QObject *parent) : QObject(parent)
  , reply(Q_NULLPTR)
  , file(Q_NULLPTR)
{

}
void LoadFile::loadFileFormUrl(const QString& _url)
{
    const QUrl url = QUrl::fromUserInput(_url);

    if(url.isValid())
        emit urlInvalid();

    QString filename = url.fileName();

    if(filename.isEmpty())
        emit urlInvalid();

    file = new QFile(filename);

    if(!file->open(QIODevice::WriteOnly))
        emit urlInvalid();

    startRequest(url);

}
void LoadFile::startRequest(const QUrl &url)
{
    reply = m.get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, this, &LoadFile::httpFinished);
    connect(reply, &QIODevice::readyRead, this, &LoadFile::httpReadyRead);
}

void LoadFile::httpFinished()
{
    if(file){
        qDebug() << 1;
        QFileInfo f(*file);
        filepath = f.absoluteFilePath();
        file->close();
    }

    emit loadCompleted();
}

void LoadFile::httpReadyRead()
{
    if(file)
        file->write(reply->readAll());
    qDebug() << "s";
}

QString LoadFile::getFilePath1()
{
    return filepath;
}
