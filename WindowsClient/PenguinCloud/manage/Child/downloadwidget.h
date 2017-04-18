#ifndef DOWNLOADWIDGET_H
#define DOWNLOADWIDGET_H

#include <QWidget>
#include <QMap>
#include <QList>

#include "../network/msgtype.h"

QT_BEGIN_NAMESPACE
class QWidget;
class TopWidget;
class ManageListWidget;
class QVBoxLayout;
class UpdateFileThread;
class File;
class ConnectToServer;
class ThreadPool;
QT_END_NAMESPACE

class DownloadWidget : public QWidget
{
    Q_OBJECT
public:
    DownloadWidget(QWidget *parent = nullptr);
    ~DownloadWidget();

    void addTask(File *file);

    int getMaxTaskNumbers() const;
    void setMaxTaskNumbers(int iMaxTaskNumbers);

private:
    TopWidget *m_pTopWidget;
    ManageListWidget *m_pListWidget;
    QVBoxLayout *m_pVBosLayout;

    QMap<File *, UpdateFileThread *> *m_pExecutingTask;
    QList<File *> *m_pWaittingTask;

    //最大任务数量
    int m_iMaxTaskNumbers;
    ConnectToServer *m_pConnectToServer;

    ThreadPool *m_pThreadPool;

protected slots:
    void startTask(File *file);
    void pauseTask(File *file);
    void stopTask(File *file);
    void finishedTask(File *file);
    void recvDownloadFile_readyReadDownloadMsg(DownloadMsg downloadMsg);

signals:
    void taskFinished(File *);
};

#endif // DOWNLOADWIDGET_H
