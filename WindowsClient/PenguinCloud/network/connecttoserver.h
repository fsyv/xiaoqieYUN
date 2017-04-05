#ifndef CONNECTTOSERVER_H
#define CONNECTTOSERVER_H

#include <QObject>
#include <QTcpSocket>

#include "abstractnetwork.h"

//接收Buf最大缓存
#define RECV_BUF_MAX_SIZE 64 * 1024

//发送Buf最大缓存
#define SEND_BUF_MAX_SIZE RECV_BUF_MAX_SIZE

//#define SERVER_IP "182.254.219.254"
//#define SERVER_IP "192.168.1.155"
//#define SERVER_IP "192.168.89.129"
#define SERVER_IP "127.0.0.1"
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

    //实现父类sendMsg方法
    int sendMsg(Msg *msg);

    QTcpSocket *p_tcpSocket;
    char *p_aRecvBuf;
    char *p_cRearBuf;
    char *p_cHeadBuf;
    int m_iMsgLen;

private slots:
    void readMessage();
    void displayError(QAbstractSocket::SocketError);
};

#endif // CONNECTTOSERVER_H
