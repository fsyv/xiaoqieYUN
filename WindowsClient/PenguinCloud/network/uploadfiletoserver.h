#ifndef UPLOADFILETOSERVER_H
#define UPLOADFILETOSERVER_H

#include "abstractnetwork.h"

#include <QTcpSocket>
#include <QFile>
#include <QFileInfo>
#include <QDataStream>
#include <QUrl>
#include <QDebug>

class UploadFileToServer : public AbstractNetwork
{
    Q_OBJECT
public:
    UploadFileToServer(QString localFilePath, QUrl remoteUrl, QObject *parent = nullptr);
    ~UploadFileToServer();

    double getCurrentProgress();
    void pause();
    void stop();

private:
    QTcpSocket *m_pTcpSocket;
    QFile m_file;
    QUrl m_serverUrl;

    qint64 m_i64CurrentUploadSize;
    qint64 m_i64FileSize;

    bool m_bRun;

    //实现父类sendMsg方法
    int sendMsg(Msg *msg);
    void updateFile();

protected slots:
    void displayState(QAbstractSocket::SocketState);
    void displayError(QAbstractSocket::SocketError);
};

#endif // UPLOADFILETOSERVER_H
