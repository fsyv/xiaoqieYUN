#include "uploadfiletoserver.h"

#define MAX_READ_BUG (64 * 1024)

UploadFileToServer::UploadFileToServer(QString localFilePath, QUrl remoteUrl, QObject *parent):
    AbstractNetwork(parent),
    m_pTcpSocket(nullptr),
    m_pUpdateFileMsg(nullptr),
    m_bRun(true)
{
    m_u64CurrentUploadSize = quint64(0);

    //检测是否是暂停的文件
    QFileInfo fileInfo(localFilePath + QString(".tmp"));
    if(fileInfo.exists())
    {
        QFile file(fileInfo.filePath());
        if(file.open(QIODevice::ReadOnly))
        {
            QTextStream in(&file);

            //读取当前已发送的大小
            QString size = in.readLine();
            size.remove("currentsize:");
            m_u64CurrentUploadSize = size.toULongLong();

            QString serverUrl = in.readLine();
            serverUrl.remove("serverUrl:");
            QUrl url(serverUrl);

            //如果当前URL跟要上传的URL不相等，则重新上传
            if(url != remoteUrl)
                m_u64CurrentUploadSize = quint64(0);
        }
    }

    fileInfo.setFile(localFilePath);

    m_file.setFileName(fileInfo.filePath());
    if(m_file.open(QIODevice::ReadOnly))
    {
        m_u64FileSize = quint64(m_file.size());
    }

    //文件偏移到当前位置
    m_file.seek(m_u64CurrentUploadSize);

    m_pTcpSocket = new QTcpSocket(this);

    connect(m_pTcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(displayState(QAbstractSocket::SocketState)));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));

    m_pTcpSocket->connectToHost(remoteUrl.host(), remoteUrl.port());

    UploadMsg uploadMsg;

    memset(&uploadMsg, 0, sizeof(UploadMsg));
    strcpy(uploadMsg.fileName, remoteUrl.path().toUtf8().data());
    strcat(uploadMsg.fileName, fileInfo.fileName().toUtf8().data());

    //等待连接文件服务器
    m_pTcpSocket->waitForConnected();

    sendUploadMsg(uploadMsg);
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

void UploadFileToServer::pause()
{
    m_bRun = false;
    //给1秒的暂停时间
    m_pTcpSocket->waitForDisconnected(1000);

    QFile tmpFile(m_file.fileName() + ".tmp");
    qDebug() << "m_file.fileName()"<< m_file.fileName();
    tmpFile.open(QIODevice::WriteOnly);

    QTextStream out(&tmpFile);
    out << "currentsize:" << QString::number(m_u64CurrentUploadSize);
    out << "serverUrl:" << m_serverUrl.toString() << endl;
    out.flush();

    tmpFile.close();
}

void UploadFileToServer::stop()
{
    m_bRun = false;
    //给1秒的暂停时间
    m_pTcpSocket->waitForDisconnected(1000);
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

    while(!dataStream.atEnd() && m_bRun)
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
