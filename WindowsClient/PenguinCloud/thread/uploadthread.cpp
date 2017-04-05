#include "uploadthread.h"

#include "../network/uploadfiletoserver.h"

UploadThread::UploadThread(QFileInfo fileinfo, UploadMsg uploadMsg, QObject *parent):
    QThread(parent),
    m_upload(nullptr)
{
    m_fileinfo = fileinfo;
    m_stUploadMsg = uploadMsg;
}

void UploadThread::run()
{
    qDebug() << currentThreadId();
    m_upload = new UploadFileToServer(m_fileinfo, m_stUploadMsg);
    exec();
}
