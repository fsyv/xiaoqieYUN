#ifndef DOWNLOADTHREAD_H
#define DOWNLOADTHREAD_H

#include <QFileInfo>
#include <QUrl>

#include "updatefilethread.h"

#include "../network/msgtype.h"

class DownloadFileToServer;

class DownloadThread : public UpdateFileThread
{
    Q_OBJECT
public:
    DownloadThread(QString localPath, QString remotePath, QObject *parent = nullptr);
    ~DownloadThread();
    //停掉当前任务
    void stopCurrenTask() override;
    //暂停当前任务
    void pauseCurrenTask() override;
    //设置文件大小
    virtual void setFileSize(qint64 fileSize) override;
	void run();

    bool getCurrentStatus();
private:
    qint64 m_i64FileSize;
    double getCurrentTaskProgress() override;
    DownloadFileToServer *m_download;
    QFileInfo m_fileinfo;
};

#endif // DOWNLOADTHREAD_H
