#include "connecttoserver.h"
#include <QDebug>
ConnectToServer* ConnectToServer::conn = NULL;

ConnectToServer::ConnectToServer(QObject *parent) : QTcpSocket(parent)
{
    this->connectToHost("127.0.0.1", 36975);
}

ConnectToServer* ConnectToServer::getInstance()
{
    if(conn == NULL || conn->state() == QAbstractSocket::UnconnectedState)
    {
        qDebug() << "new instance";
        conn = new ConnectToServer();
    }
    else
        qDebug() << "old instance";
    return conn;
}
