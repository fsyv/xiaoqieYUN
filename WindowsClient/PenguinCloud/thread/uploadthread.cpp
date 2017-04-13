#include "uploadthread.h"

#include "../network/uploadfiletoserver.h"


UploadThread::UploadThread(QString localPath, QString remotePath, QObject *parent):
    UpdateFileThread(localPath, remotePath, parent),
    m_upload(nullptr)
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

UploadThread::~UploadThread()
{
    if(m_upload)
        delete m_upload;
    m_upload = nullptr;
}

void UploadThread::stopCurrenTask()
{
    if(m_upload)
    {
        m_upload->stop();
    }
}

void UploadThread::pauseCurrenTask()
{
    if(m_upload)
    {
        m_upload->pause();
    }
}

void UploadThread::run()
{
    m_upload = new UploadFileToServer(m_fileinfo.filePath(), m_serverUrl);
}

bool UploadThread::getCurrentStatus()
{
    if(m_upload)
    {
        return m_upload->getRun();
    }
    return false;
}

double UploadThread::getCurrentTaskProgress()
{
    //从当前上传进度中取
    if(m_upload)
        return m_upload->getCurrentProgress();
    return 0.0;
}
