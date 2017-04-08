#ifndef UPDATEFILETHREAD_H
#define UPDATEFILETHREAD_H

#include <QThread>
#include <QTimerEvent>
#include <QUrl>

class UpdateFileThread : public QThread
{
    Q_OBJECT
public:
    UpdateFileThread(QObject *parent = nullptr);

    //暂停任务
    virtual void pause();
    //停止任务
    virtual void stop();
    //开始任务
    virtual void start();

protected:
    virtual double getCurrentTaskProgress() = 0;

    //定时检测当前任务进行状态
    void timerEvent(QTimerEvent *event) override;
    void startCheckCurrentProgressTimer();
    void stopCheckCurrentProgressTimer();

    //停掉当前任务
    virtual void stopCurrenTask();
    //暂停当前任务
    virtual void pauseCurrenTask();

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
