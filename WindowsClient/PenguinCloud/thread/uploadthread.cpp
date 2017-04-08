#include "uploadthread.h"

#include "../network/uploadfiletoserver.h"


UploadThread::UploadThread(QFileInfo fileinfo, UploadMsg uploadMsg, QObject *parent):
    UpdateFileThread(parent),
    m_upload(nullptr)
{
    if(!fileinfo.exists())
    {
        throw fileinfo.filePath() + ": not exits";
    }

    if(!fileinfo.isFile())
    {
        throw fileinfo.filePath() + "not a File!";
    }

    m_fileinfo = fileinfo;

    m_serverUrl.setHost(QString(uploadMsg.serverFileIP));
    m_serverUrl.setPort(uploadMsg.serverFilePort);
    m_serverUrl.setPath(QString(uploadMsg.uploadPath));
    qDebug() << m_serverUrl;
}

void UploadThread::stopCurrenTask()
{

}

void UploadThread::pauseCurrenTask()
{

}

void UploadThread::run()
{
    m_upload = new UploadFileToServer(m_fileinfo.filePath(), m_serverUrl);
    exec();
}

double UploadThread::getCurrentTaskProgress()
{
    //从当前上传进度中取
    if(m_upload)
        return m_upload->getCurrentProgress();
    return 0.0;
}
