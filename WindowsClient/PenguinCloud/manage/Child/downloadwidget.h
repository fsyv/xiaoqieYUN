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
class File;
class QListWidgetItem;
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

    QList<QListWidgetItem *> *m_pRunningTask;
    QList<QListWidgetItem *> *m_pWaittingTask;

    //最大任务数量
    int m_iMaxTaskNumbers;

protected slots:
    void startTask(File *file);
    void finishedTask(File *file);

signals:
    void finished(File *);
};

#endif // DOWNLOADWIDGET_H
