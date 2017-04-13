#ifndef UPLOADTHREAD_H
#define UPLOADTHREAD_H

#include <QFileInfo>
#include <QDataStream>
#include <QUrl>

#include "updatefilethread.h"

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
    //上传文件
    void loadDataFromFile(ConnectToFileServer *server, const UploadMsg &uploadMsg);

    void run();
};

#endif // UPLOADTHREAD_H
