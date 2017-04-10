#include "uploadfiletoserver.h"

#define MAX_READ_BUG (64 * 1024)

UploadFileToServer::UploadFileToServer(QString localFilePath, QUrl remoteUrl, QObject *parent):
    AbstractNetwork(parent),
    m_pTcpSocket(nullptr),
    m_bRun(true)
{
    m_i64CurrentUploadSize = 0LL;

    QFileInfo fileInfo(localFilePath);

    m_file.setFileName(fileInfo.filePath());
    if(m_file.open(QIODevice::ReadOnly))
    {
        m_i64FileSize = quint64(m_file.size());
    }

    m_pTcpSocket = new QTcpSocket(this);
    connect(m_pTcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
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
    return double(1.0 * m_i64CurrentUploadSize / m_i64FileSize);
}

void UploadFileToServer::pause()
{
    m_bRun = false;

    QFile tmpFile(m_file.fileName() + ".tmp");
    qDebug() << "m_file.fileName()"<< m_file.fileName();
    tmpFile.open(QIODevice::WriteOnly);
    QTextStream out(&tmpFile);

    //给0.5秒的断开网络时间
    m_pTcpSocket->waitForDisconnected(500);

    out << "currentsize:" << QString::number(m_i64CurrentUploadSize);
    out << "serverUrl:" << m_serverUrl.toString() << endl;
    out.flush();

    tmpFile.close();
}

void UploadFileToServer::stop()
{
    m_bRun = false;
    //给0.5秒的暂停时间
    m_pTcpSocket->waitForDisconnected(500);
}

bool UploadFileToServer::getRun() const
{
    return m_bRun;
}

int UploadFileToServer::sendMsg(Msg *msg)
{
    msg->m_uiCheckCrc = 0xAFAFAFAF;
    return m_pTcpSocket->write((char *)msg, m_iMsgStructLen + msg->m_iMsgLen);
}

void UploadFileToServer::updateFile()
{
    //文件偏移到当前位置
    m_file.seek(m_i64CurrentUploadSize);

    QDataStream dataStream(&m_file);
    dataStream.setVersion(QDataStream::Qt_5_6);

    char *sendBuf = new char[MAX_READ_BUG + 1];
    memset(sendBuf, 0, MAX_READ_BUG);

    int ret = 0;

    while(!dataStream.atEnd() && m_bRun)
    {
        ret = dataStream.readRawData(sendBuf, MAX_READ_BUG);

        m_i64CurrentUploadSize += qint64(ret);

        m_pTcpSocket->write(sendBuf, ret);

        memset(sendBuf, 0, ret);
    }

    m_pTcpSocket->close();
    delete []sendBuf;
}

void UploadFileToServer::readMessage()
{
    QByteArray byteArray = m_pTcpSocket->readAll();

    //翻译buf
    Msg *msg = (Msg *)byteArray.data();

    UploadMsg uploadMsg;
    memcpy(&uploadMsg, msg->m_aMsgData, msg->m_iMsgLen);

    m_i64CurrentUploadSize = uploadMsg.m_llCurrentSize;

    qDebug() << "开始上传";
    updateFile();
}

void UploadFileToServer::displayState(QAbstractSocket::SocketState)
{
    qDebug() << m_pTcpSocket->state();
    //如果状态改成可上传，则开始上传
    //updateFile();
}

void UploadFileToServer::displayError(QAbstractSocket::SocketError)
{
    qDebug()<< m_pTcpSocket->errorString();
}
