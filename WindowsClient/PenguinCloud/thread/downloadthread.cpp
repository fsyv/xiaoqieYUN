#include "downloadthread.h"

#include "../network/downloadfiletoserver.h"

DownloadThread::DownloadThread(QString localPath, QString remotePath, QObject *parent):
    UpdateFileThread(localPath, remotePath, parent),
    m_download(nullptr)
{
    m_fileinfo.setFile(localPath);

    if(!m_fileinfo.exists())
    {
        throw localPath + ": not exits";
    }

    if(!m_fileinfo.isFile())
    {
        throw localPath + "not a File!";
    }
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
void DownloadThread::run()
{
    m_download = new DownloadFileToServer(m_stLocalPath, m_serverUrl);
    exec();
}
double DownloadThread::getCurrentTaskProgress()
{
    //从当前上传进度中取
    if(m_download)
        return m_download->getCurrentProgress();
    return 0.0;
}
