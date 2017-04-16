#ifndef DOWNLOADWIDGET_H
#define DOWNLOADWIDGET_H

#include <QWidget>
#include <QMap>
#include <QList>

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

signals:
    void taskFinished(File);
};

#endif // DOWNLOADWIDGET_H
