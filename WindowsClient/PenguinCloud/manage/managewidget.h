#ifndef MANAGEWIDGET_H
#define MANAGEWIDGET_H

#include <QWidget>

#include <qDebug>

QT_BEGIN_HEADER
class QVBoxLayout;
class ManageTabWidget;
class UploadWidget;
class DownloadWidget;
class FinishedWidget;
class File;
QT_END_NAMESPACE

class ManageWidget : public QWidget
{
    Q_OBJECT
public:
    ManageWidget(QWidget *parent = nullptr);
    ~ManageWidget();

    //添加上传任务
    void addUploadTask(File *file);
    //添加下载任务
    void addDownloadTask(File *file);

protected:
    void addFinishedTask(File *file);

private:
    QVBoxLayout *m_pVBoxLayout;

    ManageTabWidget *m_pTabWidget;

    UploadWidget *m_pUploadWidget;
    DownloadWidget *m_pDownloadWidget;
    FinishedWidget *m_pFinishedWidget;
};

#endif // MANAGEWIDGET_H
