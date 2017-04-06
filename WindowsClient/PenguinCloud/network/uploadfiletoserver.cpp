#include "uploadfiletoserver.h"

#include <fstream>

using namespace std;

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
    ifstream fin(m_fileinfo.filePath().toUtf8().data(), ios::in | ios::binary);
    int ret = 0;

    char sendBuf[1025];
    memset(sendBuf, 0, 1024);

    while(!fin.eof())
    {
        fin.read(sendBuf, 1024 * sizeof(char));
        m_pTcpSocket->write(sendBuf, fin.gcount());
        memset(sendBuf, 0, ret);
    }

    fin.close();
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
