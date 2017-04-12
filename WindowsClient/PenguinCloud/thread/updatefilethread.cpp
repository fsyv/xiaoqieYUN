#include "updatefilethread.h"

UpdateFileThread::UpdateFileThread(QString localPath, QString remotePath, QObject *parent):
    QThread(parent)
{
    m_iTimerID = 0;
    setLocalPath(localPath);
    setRemotePath(remotePath);
}

void UpdateFileThread::pause()
{
    qDebug() << "UpdateFileThread::pause";
    //停止timer
    stopCheckCurrentProgressTimer();
    //暂停也是让这个线程退出，但是干得事情不一样
    pauseCurrenTask();
    //退出这个线程
    QThread::exit();
}

void UpdateFileThread::stop()
{
    qDebug() << "UpdateFileThread::stop";
    //停止timer
    stopCheckCurrentProgressTimer();
    //退出前需要处理一些东西
    stopCurrenTask();
    //退出这个线程
    QThread::exit();
}

void UpdateFileThread::start()
{
    qDebug() << "UpdateFileThread::start";

    //默认以最低优先级启动线程
    QThread::start(LowestPriority);
    startCheckCurrentProgressTimer();
}

void UpdateFileThread::setFileSize(qint64 fileSize)
{

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

void UpdateFileThread::setServerUrl(QString serverHost)
{
    m_serverUrl.setUrl(serverHost);
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

