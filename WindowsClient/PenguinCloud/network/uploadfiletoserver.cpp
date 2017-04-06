#include "uploadfiletoserver.h"

#include <stdio.h>

UploadFileToServer::UploadFileToServer(const QFileInfo &info, UploadMsg uploadMsg, QObject *parent):
    AbstractNetwork(parent),
    m_pTcpSocket(nullptr)
{
    m_fileinfo = info;

    m_pTcpSocket = new QTcpSocket(this);
    connect(m_pTcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    m_pTcpSocket->connectToHost(SERVER_IP, uploadMsg.serverFilePort);

    qDebug() << m_pTcpSocket->state();
    qDebug() << sendUploadMsg(uploadMsg);
}

int UploadFileToServer::sendMsg(Msg *msg)
{
    msg->m_uiCheckCrc = 0xAFAFAFAF;
    return m_pTcpSocket->write((char *)msg, m_iMsgStructLen + msg->m_iMsgLen);
}

void UploadFileToServer::updateFile()
{
    qDebug() << m_fileinfo.filePath();
    FILE *fp = open(m_fileinfo.filePath(), "rb");
    int ret = 0;

    char sendBuf[1025];
    memset(sendBuf, 0, 1024);

    while(!EOF(fp))
    {
        ret = fread(sendBuf, sizeof(char), 1024, fp);
        m_pTcpSocket->write(sendBuf, ret);
        memset(sendBuf, 0, ret);
    }

    close(fp);
    m_pTcpSocket->close();
}

void UploadFileToServer::readMessage()
{
    QByteArray byteArray = m_pTcpSocket->readAll();

    //翻译buf
    Msg *msg = (Msg *)byteArray.data();

    UploadMsg uploadMsg;
    memcpy(&uploadMsg, msg->m_aMsgData, msg->m_iMsgLen);

    if(uploadMsg.m_iLoginStatus)
    {
        qDebug() << "开始上传";
        updateFile();
    }
}

void UploadFileToServer::displayError(QAbstractSocket::SocketError)
{
    qDebug()<< m_pTcpSocket->errorString();
}
