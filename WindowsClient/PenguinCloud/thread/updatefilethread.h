#ifndef UPDATEFILETHREAD_H
#define UPDATEFILETHREAD_H

#include "ThreadObject.h"

#include <QTimerEvent>
#include <QUrl>
#include <QFile>
#include <qDebug>

#include "network/connecttofileserver.h"


class UpdateFileThread : public ThreadObject
{
    Q_OBJECT
public:
    UpdateFileThread(QString localPath, QString remotePath, QObject *parent = nullptr);
    ~UpdateFileThread();

    //开始任务
    virtual void start();
    //暂停任务
    virtual void pause();
    //停止任务
    virtual void stop();
    //设置文件大小
    virtual void setFileSize(qint64 fileSize);

    QString getLocalPath() const;
    void setLocalPath(const QString &stLocalPath);

    QString getRemotePath() const;
    void setRemotePath(const QString &stRemotePath);

    //文件服务器地址+端口
    void setServerUrl(QString serverIP, quint16 port);

    bool operator ==(const UpdateFileThread &other) const;
    bool operator ==(const UpdateFileThread *other) const;

protected:
    virtual double getCurrentTaskProgress() final;

    //定时检测当前任务进行状态
    void timerEvent(QTimerEvent *event);
    void startCheckCurrentProgressTimer();
    void stopCheckCurrentProgressTimer();

    //停掉当前任务
    virtual void stopCurrenTask();
    //暂停当前任务
    virtual void pauseCurrenTask();

    ConnectToFileServer *m_pSocket;
    //本地路径
    QString m_stLocalPath;
    //远程路径
    QString m_stRemotePath;
    //定时器ID
    int m_iTimerID;
    //服务器URL
    QUrl m_serverUrl;
	QFile m_file;
    //当前文件大小
    qint64 m_i64CurrentSize;
    //文件大小
    qint64 m_i64FileSize;
    //任务是否完成
    //包括暂停或者取消或者成功下载完
    bool m_bFinished;
signals:
    void currentTaskProgress(double);
};

#endif // UPDATEFILETHREAD_H
