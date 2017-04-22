#ifndef DOWNLOADTHREAD_H
#define DOWNLOADTHREAD_H

#include <QDataStream>

#include "updatefilethread.h"

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
    //把下载的数据保存到文件
    void saveFileFromData(ConnectToFileServer *server);

	void run();

private:
    QDataStream m_out;
};

#endif // DOWNLOADTHREAD_H
