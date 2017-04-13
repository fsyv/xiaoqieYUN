#ifndef CONNECTTOSERVER_H
#define CONNECTTOSERVER_H

#include <QMutex>

#include "abstractnetwork.h"

//接收Buf最大缓存
#define RECV_BUF_MAX_SIZE 64 * 1024

//发送Buf最大缓存
#define SEND_BUF_MAX_SIZE RECV_BUF_MAX_SIZE

#define SERVER_PORT 36975

class ConnectToServer : public AbstractNetwork
{
    Q_OBJECT
public:
    static ConnectToServer* getInstance();
    virtual ~ConnectToServer();
private:
    ConnectToServer(QObject *parent = nullptr);
    static ConnectToServer* conn;
    static QMutex mutex;

    char *p_aRecvBuf;
    char *p_cRearBuf;
    char *p_cHeadBuf;
    int m_iMsgLen;

private slots:
    void readMessage();
    void displayState(QAbstractSocket::SocketState);
    void displayError(QAbstractSocket::SocketError);
};

#endif // CONNECTTOSERVER_H
