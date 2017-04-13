#ifndef UPDATEFILETHREAD_H
#define UPDATEFILETHREAD_H

#include "ThreadObject.h"
#include <QTimerEvent>
#include <QUrl>
#include <qDebug>

class UpdateFileThread : public ThreadObject
{
    Q_OBJECT
public:
    UpdateFileThread(QString localPath, QString remotePath, QObject *parent = nullptr);

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
    void setServerUrl(QString serverHost);
    void setServerUrl(QString serverIP, quint16 port);

    bool operator ==(const UpdateFileThread &other) const;
    bool operator ==(const UpdateFileThread *other) const;

protected:
    virtual double getCurrentTaskProgress() = 0;

    //定时检测当前任务进行状态
    void timerEvent(QTimerEvent *event);
    void startCheckCurrentProgressTimer();
    void stopCheckCurrentProgressTimer();

    //停掉当前任务
    virtual void stopCurrenTask();
    //暂停当前任务
    virtual void pauseCurrenTask();

    //本地路径
    QString m_stLocalPath;
    //远程路径
    QString m_stRemotePath;
    //定时器ID
    int m_iTimerID;
    //标识符
    int m_iIdentifier;
    //服务器URL
    QUrl m_serverUrl;

signals:
    void currentTaskProgress(double);
};

#endif // UPDATEFILETHREAD_H
