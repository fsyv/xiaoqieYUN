#ifndef UPLOADFILETOSERVER_H
#define UPLOADFILETOSERVER_H

#include "abstractnetwork.h"

#include <QTcpSocket>
#include <QFile>
#include <QDataStream>
#include <QUrl>
#include <QDebug>

#include "updatefilemsg.h"

class UploadFileToServer : public AbstractNetwork
{
    Q_OBJECT
public:
    UploadFileToServer(QString localFilePath, QUrl remoteUrl, QObject *parent = nullptr);
    ~UploadFileToServer();

    double getCurrentProgress();

private:
    QTcpSocket *m_pTcpSocket;
    QFile m_file;
    UpdateFileMsg *m_pUpdateFileMsg;

    quint64 m_u64CurrentUploadSize;
    quint64 m_u64FileSize;

    //实现父类sendMsg方法
    int sendMsg(Msg *msg);
    int sendUpdateFileMsg(UpdateFileMsg *updateFileMsg);
    void updateFile();

protected slots:
    void displayState(QAbstractSocket::SocketState);
    void displayError(QAbstractSocket::SocketError);
};

#endif // UPLOADFILETOSERVER_H
