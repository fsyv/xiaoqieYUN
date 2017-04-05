#ifndef UPLOADTHREAD_H
#define UPLOADTHREAD_H

#include <QThread>
#include <QFileInfo>
#include "QDebug"

#include "../network/msgtype.h"

class UploadFileToServer;

class UploadThread : public QThread
{
    Q_OBJECT
public:
    UploadThread(QFileInfo fileinfo, UploadMsg uploadMsg, QObject *parent = nullptr);
    void run();

private:
    UploadFileToServer *m_upload;
    QFileInfo m_fileinfo;
    UploadMsg m_stUploadMsg;
};

#endif // UPLOADTHREAD_H
