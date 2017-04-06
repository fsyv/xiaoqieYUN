#include "uploadfiletoserver.h"

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
    QFile *sendFile = new QFile(m_fileinfo.filePath());	//读取发送文件路径
    if (!sendFile->open(QFile::ReadOnly ))  //读取发送文件
        return;
    QByteArray outBlock;
    outBlock = sendFile->read(sendFile->size());
    qDebug() << "sendFile.size()" << sendFile->size();
    m_pTcpSocket->write(outBlock);
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
