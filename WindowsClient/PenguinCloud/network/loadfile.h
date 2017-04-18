/**
  *    通过这个类来下载Http文件服务器的文件
  *
  */

#ifndef LOADFILE_H
#define LOADFILE_H

#include <QObject>
#include <QNetworkAccessManager>

class QFile;
class QNetworkReply;

class LoadFile : public QObject
{
    Q_OBJECT
public:
    explicit LoadFile(QObject *parent = 0);
    void loadFileFormUrl(const QString& url);
    QString getFilePath1();
signals:
    void urlInvalid();
    void loadCompleted();

public slots:
    void httpFinished();
    void httpReadyRead();
private:

    void startRequest(const QUrl &url);
    QNetworkReply *reply;
    QNetworkAccessManager m;
    QFile *file;
    QString filepath;
};

#endif // LOADFILE_H
