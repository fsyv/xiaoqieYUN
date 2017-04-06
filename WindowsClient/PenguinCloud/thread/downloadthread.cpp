#include "downloadthread.h"

#include "../network/downloadfiletoserver.h"

DownloadThread::DownloadThread(DownloadMsg downloadMsg, QObject *parent):
    QThread(parent),
    m_download(nullptr)
{
    m_stDownloadMsg = downloadMsg;
}

void DownloadThread::run()
{
    qDebug() << currentThreadId();
    m_download = new DownloadFileToServer(m_stDownloadMsg);
    exec();
}
