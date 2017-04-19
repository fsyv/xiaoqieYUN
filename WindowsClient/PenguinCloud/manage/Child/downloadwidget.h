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
class QListWidgetItem;
class File;
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
    bool contains(File *file);

    TopWidget *m_pTopWidget;
    ManageListWidget *m_pListWidget;
    QVBoxLayout *m_pVBosLayout;

    //将具体的界面加到这个队列里
    QList<QWidget *> *m_pRunningTask;
    QList<QWidget *> *m_pWaittingTask;

    //最大任务数量
    int m_iMaxTaskNumbers;

protected slots:
    void startTask(QListWidgetItem *item);
    void pauseTask(QListWidgetItem *item);
    void stopTask(QListWidgetItem *item);
    void finishedTask(QListWidgetItem *item);

signals:
    void finished(File *);
};

#endif // DOWNLOADWIDGET_H
