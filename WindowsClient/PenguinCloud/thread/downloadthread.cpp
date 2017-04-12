#include "downloadthread.h"

#include <QDir>

#include "../network/downloadfiletoserver.h"

DownloadThread::DownloadThread(QString localPath, QString remotePath, QObject *parent):
    UpdateFileThread(localPath, remotePath, parent),
    m_download(nullptr)
{
    m_fileinfo.setFile(localPath);

    //生成路径
    QDir dir;
    dir.mkpath(m_fileinfo.path());
}

DownloadThread::~DownloadThread()
{
    if(m_download)
        delete m_download;
    m_download = nullptr;
}

void DownloadThread::stopCurrenTask()
{
    if(m_download)
    {
        m_download->stop();
    }
}

void DownloadThread::pauseCurrenTask()
{
    if(m_download)
    {
        m_download->pause();
    }
}

void DownloadThread::setFileSize(qint64 fileSize)
{
    m_i64FileSize = fileSize;
}
void DownloadThread::run()
{
    qDebug() << "DownloadThread::run()";

    m_download = new DownloadFileToServer(m_stLocalPath, m_serverUrl, m_i64FileSize);
    exec();
}

bool DownloadThread::getCurrentStatus()
{
    if(m_download)
    {
        return m_download->getRun();
    }
    return false;
}
double DownloadThread::getCurrentTaskProgress()
{
    //从当前上传进度中取
    if(m_download)
        return m_download->getCurrentProgress();
    return 0.0;
}
