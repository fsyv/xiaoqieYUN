#include "downloadfiletoserver.h"

#include <QDir>

DownloadFileToServer::DownloadFileToServer(QString localFilePath, QUrl remoteUrl, QObject *parent):
    AbstractNetwork(parent),
    m_pTcpSocket(nullptr),
    m_bRun(true)
{
    m_i64CurrentDownloadSize = 0LL;

    QFileInfo fileInfo(localFilePath);

    if(fileInfo.exists())
    {
        //检测是否是暂停的文件
        fileInfo.setFile(localFilePath + QString(".tmp"));
        if(fileInfo.exists())
        {
            QFile file(fileInfo.filePath());
            if(file.open(QIODevice::ReadOnly))
            {
                QTextStream in(&file);

                //读取当前已发送的大小
                QString size = in.readLine();
                size.remove("currentsize:");
                m_i64CurrentDownloadSize = size.toULongLong();

                QString serverUrl = in.readLine();
                serverUrl.remove("serverUrl:");
                QUrl url(serverUrl);

                //如果当前URL跟要上传的URL不相等，则重新上传
                if(url != remoteUrl)
                    m_i64CurrentDownloadSize = qint64(0);
            }
            //删除临时文件
            QFile::remove(fileInfo.filePath());
        }
        else
        {
            //文件已存在，且已经下载完成
            QFile::remove(localFilePath);
        }
    }

    fileInfo.setFile(localFilePath);

    m_file.setFileName(localFilePath);
    if(m_file.open(QIODevice::WriteOnly))
    {
        m_i64FileSize = quint64(m_file.size());
        //文件偏移到当前位置
        m_file.seek(m_i64CurrentDownloadSize);
        m_out.setDevice(&m_file);
        m_out.setVersion(QDataStream::Qt_5_6);
    }

    m_pTcpSocket = new QTcpSocket(this);
    connect(m_pTcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
	connect(m_pTcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(displayState(QAbstractSocket::SocketState)));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    m_pTcpSocket->connectToHost(remoteUrl.host(), remoteUrl.port());

    DownloadMsg downloadMsg;

    memset(&downloadMsg, 0, sizeof(DownloadMsg));
    strcpy(downloadMsg.fileName, remoteUrl.path().toUtf8().data());
    strcat(downloadMsg.fileName, fileInfo.fileName().toUtf8().data());
    downloadMsg.m_llCurrentSize = m_i64CurrentDownloadSize;

    //等待连接文件服务器
    m_pTcpSocket->waitForConnected();
    sendDownloadMsg(downloadMsg);
}
DownloadFileToServer::~DownloadFileToServer()
{
    m_file.close();
    //    if(m_pTcpSocket->state() == )
}

double DownloadFileToServer::getCurrentProgress()
{
    return double(1.0 * m_i64CurrentDownloadSize / m_i64FileSize);
}

void DownloadFileToServer::pause()
{
    m_bRun = false;

    QFile tmpFile(m_file.fileName() + ".tmp");
    qDebug() << "m_file.fileName()"<< m_file.fileName();
    tmpFile.open(QIODevice::WriteOnly);
    QTextStream out(&tmpFile);

    //给0.5秒的断开网络时间
    m_pTcpSocket->waitForDisconnected(500);

    out << "currentsize:" << QString::number(m_i64CurrentDownloadSize);
    out << "serverUrl:" << m_serverUrl.toString() << endl;
    out.flush();

    tmpFile.close();
}

void DownloadFileToServer::stop()
{
    m_bRun = false;
    //给0.5秒的暂停时间
    m_pTcpSocket->waitForDisconnected(500);
}

bool DownloadFileToServer::getRun() const
{
    return m_bRun;
}

int DownloadFileToServer::sendMsg(Msg *msg)
{
    msg->m_uiCheckCrc = 0xAFAFAFAF;
    return m_pTcpSocket->write((char *)msg, m_iMsgStructLen + msg->m_iMsgLen);
}

void DownloadFileToServer::readMessage()
{
    if(m_bRun)
    {
        QByteArray byteArray = m_pTcpSocket->readAll();
        m_i64CurrentDownloadSize += byteArray.length();
        m_out.writeRawData(byteArray.data(), byteArray.length());
    }
}

void DownloadFileToServer::displayState(QAbstractSocket::SocketState)
{
    qDebug() << m_pTcpSocket->state();
    //如果状态改成可上传，则开始上传
    //updateFile();
}
void DownloadFileToServer::displayError(QAbstractSocket::SocketError)
{
    qDebug()<< m_pTcpSocket->errorString();
}
