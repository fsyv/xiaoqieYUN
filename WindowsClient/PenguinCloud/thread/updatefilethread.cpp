#include "updatefilethread.h"

UpdateFileThread::UpdateFileThread(QString localPath, QString remotePath, QObject *parent):
    ThreadObject(parent),
    m_pSocket(nullptr),
    m_i64CurrentSize(0LL),
    m_bFinished(false)
{
    m_iTimerID = 0;
    setLocalPath(localPath);
    setRemotePath(remotePath);
}

UpdateFileThread::~UpdateFileThread()
{

}

void UpdateFileThread::start()
{
    startCheckCurrentProgressTimer();
}

void UpdateFileThread::pause()
{
    qDebug() << "UpdateFileThread::pause";
    //停止timer
    stopCheckCurrentProgressTimer();
    //暂停也是让这个线程退出，但是干得事情不一样
    pauseCurrenTask();
}

void UpdateFileThread::stop()
{
    qDebug() << "UpdateFileThread::stop";
    //停止timer
    stopCheckCurrentProgressTimer();
    //退出前需要处理一些东西
    stopCurrenTask();
}

void UpdateFileThread::setFileSize(qint64 fileSize)
{
    m_i64FileSize = fileSize;
}

QString UpdateFileThread::getLocalPath() const
{
    return m_stLocalPath;
}

void UpdateFileThread::setLocalPath(const QString &stLocalPath)
{
    m_stLocalPath = stLocalPath;
}

QString UpdateFileThread::getRemotePath() const
{
    return m_stRemotePath;
}

void UpdateFileThread::setRemotePath(const QString &stRemotePath)
{
    m_stRemotePath = stRemotePath;
}

void UpdateFileThread::setServerUrl(QString serverIP, quint16 port)
{
    m_serverUrl.setHost(serverIP);
    m_serverUrl.setPort(port);
    m_serverUrl.setPath(QString("/") + m_stRemotePath);
}

bool UpdateFileThread::operator ==(const UpdateFileThread &other) const
{
    if(this->m_stLocalPath == other.getLocalPath() &&
            this->m_stRemotePath == other.getRemotePath())
        return true;
    return false;
}

bool UpdateFileThread::operator ==(const UpdateFileThread *other) const
{
    if(!other)
        return false;

    if(other == this)
        return true;

    if(this->m_stLocalPath == other->getLocalPath() &&
            this->m_stRemotePath == other->getRemotePath())
        return true;
    return false;
}

qint64 UpdateFileThread::getCurrentTaskProgress()
{
    return m_i64CurrentSize;
}

void UpdateFileThread::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == m_iTimerID)
    {
        qint64 progress = getCurrentTaskProgress();
        emit currentTaskProgress(progress);

        //当前任务完成就停止Timer
        if(m_bFinished)
            stopCheckCurrentProgressTimer();
    }
    else
    {
        ThreadObject::timerEvent(event);
    }
}

void UpdateFileThread::startCheckCurrentProgressTimer()
{
    if(m_iTimerID)
        stopCheckCurrentProgressTimer();

    //一秒钟检测一次当前运行的状态
    m_iTimerID = startTimer(1000);
    qDebug() << "m_iTimerID  start" << m_iTimerID;
}

void UpdateFileThread::stopCheckCurrentProgressTimer()
{
    mutex.lock();
    if(m_iTimerID)
    {
        qDebug() << "m_iTimerID  end" << m_iTimerID;
        killTimer(m_iTimerID);
        m_iTimerID = 0;
    }
    mutex.unlock();
}

void UpdateFileThread::stopCurrenTask()
{

}

void UpdateFileThread::pauseCurrenTask()
{

}

