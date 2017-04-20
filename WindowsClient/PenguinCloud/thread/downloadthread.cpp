#include "downloadthread.h"

#include <thread>

#include <QDir>

DownloadThread::DownloadThread(QString localPath, QString remotePath, QObject *parent):
    UpdateFileThread(localPath, remotePath, parent)
{
    QFileInfo fileInfo(localPath);

    if(fileInfo.exists())
    {
        //文件存在
        //检测是否是暂停的文件
        QFileInfo tmpFileInfo(fileInfo.filePath() + QString(".tmp"));
        if(tmpFileInfo.exists())
        {
            QFile file(tmpFileInfo.filePath());
            if(file.open(QIODevice::ReadOnly))
            {
                QTextStream in(&file);

                //读取当前已发送的大小
                QString size = in.readLine();
                size.remove("currentsize:");
                m_i64CurrentSize = size.toULongLong();
            }
            //删除临时文件
            QFile::remove(tmpFileInfo.filePath());
        }
        else
        {
            //文件已存在，且已经下载完成
            QFile::remove(fileInfo.filePath());
        }
    }
    else
    {
        //文件不存在
        //生成路径
        QDir dir;
        dir.mkpath(fileInfo.path());
    }

    m_file.setFileName(fileInfo.filePath());
    if(m_file.open(QIODevice::WriteOnly))
    {
        //文件偏移到当前位置
        //m_file.seek(m_i64CurrentDownloadSize);
        m_out.setDevice(&m_file);
        m_out.setVersion(QDataStream::Qt_5_6);
    }
}

DownloadThread::~DownloadThread()
{
    m_bFinished = true;
    m_file.close();
}

void DownloadThread::stopCurrenTask()
{
    m_bFinished = true;

    m_file.remove();
}

void DownloadThread::pauseCurrenTask()
{
    qDebug() << "pause";

    m_bFinished = true;

    QFile tmpFile(m_file.fileName() + ".tmp");
    tmpFile.open(QIODevice::WriteOnly);
    QTextStream out(&tmpFile);

    out << "currentsize:" << QString::number(m_i64CurrentSize) << endl;
    out.flush();

    tmpFile.close();
}

void DownloadThread::saveFileFromData(ConnectToFileServer *server)
{
    QByteArray byteArray = server->readAll();
    if(byteArray.length())
    {
        m_i64CurrentSize += byteArray.length();
        m_out.writeRawData(byteArray.data(), byteArray.length());
    }
}

void DownloadThread::run()
{
    m_pSocket = new ConnectToFileServer(m_serverUrl);

    DownloadMsg downloadMsg;

    memset(&downloadMsg, 0, sizeof(DownloadMsg));
    strcpy(downloadMsg.fileName, m_stRemotePath.toUtf8().data());
    downloadMsg.m_llCurrentSize = m_i64CurrentSize;

    m_pSocket->sendDownloadMsg(downloadMsg);


    while(!m_bFinished && m_pSocket->isConnected())
    {
        if(m_pSocket->waitForReadyRead(1000))
            saveFileFromData(m_pSocket);
        else
        {
            qDebug() << "任务超时";
            m_bFinished = true;
        }
    }

    delete m_pSocket;
    m_pSocket = nullptr;
}

