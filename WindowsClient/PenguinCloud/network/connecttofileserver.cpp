#include "connecttofileserver.h"

ConnectToFileServer::ConnectToFileServer(QUrl serverUrl, QObject *parent) :
    AbstractNetwork(parent)
{
    connectToHost(serverUrl.host(), serverUrl.port());

    //等待连接文件服务器
    waitForConnected(1000);
}

