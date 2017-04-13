#ifndef CONNECTTOFILESERVER_H
#define CONNECTTOFILESERVER_H

#include <QUrl>
#include <QTcpSocket>

#include "abstractnetwork.h"


class ConnectToFileServer : public AbstractNetwork, public QTcpSocket
{
    Q_OBJECT
public:
    ConnectToFileServer(QUrl serverUrl,QObject *parent = nullptr);

private:
    //实现父类sendMsg方法
    int sendMsg(Msg *msg);

};

#endif // CONNECTTOFILESERVER_H
