#include "connecttofileserver.h"

ConnectToFileServer::ConnectToFileServer(QUrl serverUrl, QObject *parent) :
    AbstractNetwork(parent)
{
    connect(this, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(displayState(QAbstractSocket::SocketState)));
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));

    connectToHost(serverUrl.host(), serverUrl.port());

    //等待连接文件服务器
    waitForConnected(1000);
}

ConnectToFileServer::~ConnectToFileServer()
{
    if(state() == QTcpSocket::ConnectedState)
        close();
}

bool ConnectToFileServer::isConnected()
{
    return state() == QTcpSocket::ConnectedState;
}

void ConnectToFileServer::displayState(QAbstractSocket::SocketState)
{
    qDebug() << state();
}
void ConnectToFileServer::displayError(QAbstractSocket::SocketError)
{
    qDebug()<< errorString();
}
