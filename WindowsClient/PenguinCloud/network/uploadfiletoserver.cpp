#include "uploadfiletoserver.h"

#define MAX_READ_BUG (64 * 1024)

UploadFileToServer::UploadFileToServer(QString localFilePath, QUrl remoteUrl, QObject *parent):
    AbstractNetwork(parent),
    m_pTcpSocket(nullptr),
    m_pUpdateFileMsg(nullptr)
{
    m_u64CurrentUploadSize = quint64(0);

    m_file.setFileName(localFilePath);
    if(m_file.open(QIODevice::ReadOnly))
    {
        m_u64FileSize = quint64(m_file.size());
    }

    //检测是否是暂停的文件
    //began
    {

    }
    //end

    m_pTcpSocket = new QTcpSocket(this);

    connect(m_pTcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(displayState(QAbstractSocket::SocketState)));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));

    m_pTcpSocket->connectToHost(remoteUrl.host(), remoteUrl.port());
}

UploadFileToServer::~UploadFileToServer()
{
    m_file.close();
//    if(m_pTcpSocket->state() == )
}

double UploadFileToServer::getCurrentProgress()
{
    return double(1.0 * m_u64CurrentUploadSize / m_u64FileSize);
}

int UploadFileToServer::sendMsg(Msg *msg)
{
    msg->m_uiCheckCrc = 0xAFAFAFAF;
    return m_pTcpSocket->write((char *)msg, m_iMsgStructLen + msg->m_iMsgLen);
}

int UploadFileToServer::sendUpdateFileMsg(UpdateFileMsg *updateFileMsg)
{
    updateFileMsg->m_uiCheckCrc = 0xAFAFAFAF;
    return m_pTcpSocket->write((char *)updateFileMsg, sizeof(UpdateFileMsg) + updateFileMsg->m_iMsgLen);
}

void UploadFileToServer::updateFile()
{
    int fileMsgStructLen = sizeof(UpdateFileMsg);

    QDataStream dataStream(&m_file);
    dataStream.setVersion(QDataStream::Qt_5_6);

    m_pUpdateFileMsg = (UpdateFileMsg *)new char[fileMsgStructLen + MAX_READ_BUG + 1];
    memset(m_pUpdateFileMsg, 0, fileMsgStructLen + MAX_READ_BUG);
    m_pUpdateFileMsg->m_ullFileSize = m_u64FileSize;

    int ret = 0;

    while(!dataStream.atEnd())
    {
        ret = dataStream.readRawData(m_pUpdateFileMsg->m_aMsgData, MAX_READ_BUG);

        m_pUpdateFileMsg->m_iMsgLen = ret;

        m_u64CurrentUploadSize += quint64(ret);
        m_pUpdateFileMsg->m_ullCurrentSize = m_u64CurrentUploadSize;

        sendUpdateFileMsg(m_pUpdateFileMsg);

        memset(m_pUpdateFileMsg->m_aMsgData, 0, m_pUpdateFileMsg->m_iMsgLen);
    }

    m_pTcpSocket->close();
}

void UploadFileToServer::displayState(QAbstractSocket::SocketState)
{
    qDebug() << m_pTcpSocket->state();
    //如果状态改成可上传，则开始上床
    //updateFile();
}

void UploadFileToServer::displayError(QAbstractSocket::SocketError)
{
    qDebug()<< m_pTcpSocket->errorString();
}
