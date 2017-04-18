#ifndef DOWNLOADWIDGET_H
#define DOWNLOADWIDGET_H

#include <QWidget>
#include <QMap>
#include <QList>

#include "../file/file.h"

QT_BEGIN_NAMESPACE
class QWidget;
class TopWidget;
class ManageListWidget;
class QVBoxLayout;
class UpdateFileThread;
class File;
QT_END_NAMESPACE

class DownloadWidget : public QWidget
{
    Q_OBJECT
public:
    DownloadWidget(QWidget *parent = nullptr);
    ~DownloadWidget();

    void addTask(File *file);

private:
    TopWidget *m_pTopWidget;
    ManageListWidget *m_pListWidget;
    QVBoxLayout *m_pVBosLayout;

    QMap<File *, UpdateFileThread *> *m_pExecutingTask;
    QList<File *> *m_pWaittingTask;

protected slots:
    void startTask(File *file);
    void pauseTask(File *file);
    void stopTask(File *file);
    void finishedTask(File *file);

signals:
    void taskFinished(File);
};

#endif // DOWNLOADWIDGET_H
