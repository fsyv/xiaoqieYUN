#include "updatefilethread.h"

UpdateFileThread::UpdateFileThread(QObject *parent):
    QThread(parent)
{
    m_iTimerID = 0;
}

void UpdateFileThread::pause()
{
    //暂停也是让这个线程退出，但是干得事情不一样
    pauseCurrenTask();
    //退出这个线程
    QThread::exit();
}

void UpdateFileThread::stop()
{
    //退出前需要处理一些东西
    stopCurrenTask();
    //退出这个线程
    QThread::exit();
}

void UpdateFileThread::start()
{
    //默认以最低优先级启动线程
    QThread::start(LowestPriority);
}

void UpdateFileThread::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == m_iTimerID)
    {
        emit currentTaskProgress(getCurrentTaskProgress());
    }
    else
    {
        QThread::timerEvent(event);
    }
}

void UpdateFileThread::startCheckCurrentProgressTimer()
{
    if(m_iTimerID)
        stopCheckCurrentProgressTimer();

    //一秒钟检测一次当前运行的状态
    m_iTimerID = startTimer(1000);
}

void UpdateFileThread::stopCheckCurrentProgressTimer()
{
    if(m_iTimerID)
    {
        killTimer(m_iTimerID);
        m_iTimerID = 0;
    }
}

void UpdateFileThread::stopCurrenTask()
{

}

void UpdateFileThread::pauseCurrenTask()
{

}
