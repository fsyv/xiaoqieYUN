#include "uploadthread.h"


UploadThread::UploadThread(QString localPath, QString remotePath, QObject *parent):
    UpdateFileThread(localPath, remotePath, parent)
{
    QFileInfo fileInfo(localPath);

    if(!fileInfo.isFile())
    {
        throw fileInfo.fileName() + "not a File!";
    }

    if(!fileInfo.exists())
    {
        throw fileInfo.filePath() + ": not exits";
    }
    else
    {
        if(m_file.open(QIODevice::ReadOnly))
        {
            m_i64FileSize = quint64(m_file.size());
        }
    }
}

UploadThread::~UploadThread()
{

}

void UploadThread::stopCurrenTask()
{

}

void UploadThread::pauseCurrenTask()
{

}

void UploadThread::loadDataFromFile(ConnectToFileServer *server, const UploadMsg &uploadMsg)
{
    //文件偏移到当前位置
    m_file.seek(m_i64CurrentSize);

    QDataStream dataStream(&m_file);
    dataStream.setVersion(QDataStream::Qt_5_6);

    char *sendBuf = new char[MAX_READ_BUF + 1];
    memset(sendBuf, 0, MAX_READ_BUF);

    int ret = 0;

    while(!dataStream.atEnd() && m_bFinished)
    {
        ret = dataStream.readRawData(sendBuf, MAX_READ_BUF);

        m_i64CurrentSize += qint64(ret);

        server->write(sendBuf, ret);

        memset(sendBuf, 0, ret);
    }

    server->close();
    delete []sendBuf;
    m_bFinished = true;
}

void UploadThread::run()
{
    m_pSocket = new ConnectToFileServer(m_serverUrl);

    UploadMsg uploadMsg;

    memset(&uploadMsg, 0, sizeof(DownloadMsg));
    strcpy(uploadMsg.fileName, m_stRemotePath.toUtf8().data());

    m_pSocket->sendUploadMsg(uploadMsg);

    while(!m_bFinished && m_pSocket->isConnected())
    {
        if(m_pSocket->isReadable())
        {
            QByteArray byteArray = m_pSocket->readAll();
            //翻译buf
            Msg *msg = (Msg *)byteArray.data();

            UploadMsg uploadMsg;
            memcpy(&uploadMsg, msg->m_aMsgData, msg->m_iMsgLen);

            loadDataFromFile(m_pSocket, uploadMsg);
        }
    }

    delete m_pSocket;
    m_pSocket = nullptr;
}


