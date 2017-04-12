#ifndef UPLOADTHREAD_H
#define UPLOADTHREAD_H

#include <QFileInfo>
#include <QUrl>

#include "updatefilethread.h"

#include "../network/msgtype.h"

class UploadFileToServer;

class UploadThread : public UpdateFileThread
{
    Q_OBJECT
public:
    UploadThread(QString localPath, QString remotePath, QObject *parent = nullptr);
    ~UploadThread();

    //停掉当前任务
    void stopCurrenTask() override;
    //暂停当前任务
    void pauseCurrenTask() override;

    void run();

    bool getCurrentStatus();

private:
    double getCurrentTaskProgress() override;

    UploadFileToServer *m_upload;
    QFileInfo m_fileinfo;
};

#endif // UPLOADTHREAD_H
