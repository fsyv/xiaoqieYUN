#ifndef DOWNLOADFILETOSERVER_H
#define DOWNLOADFILETOSERVER_H

#include "abstractnetwork.h"
#include <QTcpSocket>
#include <QFile>
#include <QFileInfo>
#include <QDataStream>
#include <QUrl>
#include <QDebug>
class DownloadFileToServer : public AbstractNetwork
{
    Q_OBJECT
public:
    DownloadFileToServer(QString localFilePath, QUrl remoteUrl, QObject *parent = nullptr);
    ~DownloadFileToServer();
    double getCurrentProgress();
    void pause();
    void stop();
private:
    QTcpSocket *m_pTcpSocket;
    QFile m_file;
    QDataStream m_out;
    QUrl m_serverUrl;

    qint64 m_i64CurrentDownloadSize;
    qint64 m_i64FileSize;

    bool m_bRun;
    //实现父类sendMsg方法
    int sendMsg(Msg *msg);

protected slots:
    void readMessage();
	void displayState(QAbstractSocket::SocketState);
    void displayError(QAbstractSocket::SocketError);
};

#endif // DOWNLOADFILETOSERVER_H
