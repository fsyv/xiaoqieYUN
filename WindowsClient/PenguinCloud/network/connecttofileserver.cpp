#include "connecttofileserver.h"

ConnectToFileServer::ConnectToFileServer(QUrl serverUrl, QObject *parent) :
    QTcpSocket(parent)
{
    connectToHost(serverUrl.host(), serverUrl.port());

    //等待连接文件服务器
    waitForConnected();
}

int ConnectToFileServer::sendMsg(Msg *msg)
{
    msg->m_uiCheckCrc = 0xAFAFAFAF;
    return write((char *)msg, m_iMsgStructLen + msg->m_iMsgLen);
}
