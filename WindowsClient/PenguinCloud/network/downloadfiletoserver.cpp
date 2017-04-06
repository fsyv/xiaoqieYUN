#include "downloadfiletoserver.h"

#include <QDir>

DownloadFileToServer::DownloadFileToServer(DownloadMsg downloadMsg, QObject *parent):
    AbstractNetwork(parent),
    m_pTcpSocket(nullptr)
{
    QDir dir;

    qDebug() << QDir::currentPath();

    if(!dir.exists(QDir::currentPath() + QString("/download")))
    {
        dir.mkdir(QDir::currentPath() + QString("/download"));
    }

    m_fileinfo.setFile(QDir::currentPath() + QString("/download/") + QString(downloadMsg.fileName));
    qDebug() << m_fileinfo.filePath();

    if(m_fileinfo.exists())
    {
        QFile::remove(m_fileinfo.filePath());
    }

    fout.open(m_fileinfo.filePath().toUtf8().data(), ios::out | ios::binary);

    m_pTcpSocket = new QTcpSocket(this);
    connect(m_pTcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    m_pTcpSocket->connectToHost(SERVER_IP, downloadMsg.serverFilePort);
    sendDownloadMsg(downloadMsg);
}
int DownloadFileToServer::sendMsg(Msg *msg)
{
    msg->m_uiCheckCrc = 0xAFAFAFAF;
    return m_pTcpSocket->write((char *)msg, m_iMsgStructLen + msg->m_iMsgLen);
}

void DownloadFileToServer::readMessage()
{
    QByteArray byteArray = m_pTcpSocket->readAll();
    qDebug() << byteArray.length();
    fout.write(byteArray.data(), byteArray.length());
}

void DownloadFileToServer::displayError(QAbstractSocket::SocketError)
{
    qDebug()<< m_pTcpSocket->errorString();
    fout.close();
}
