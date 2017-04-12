#ifndef MANAGEWIDGET_H
#define MANAGEWIDGET_H
#include "basicwidget/basicwidget.h"
#include "downloadmanage.h"
#include "uploadmanage.h"
#include <QtWidgets>

class ManageWidget : public BasicWidget
{
    Q_OBJECT
public:
    ManageWidget(QWidget *parent = 0);
    ~ManageWidget();

    UploadManage *getUploadManage();
    DownloadManage *getDownloadManage();

private:
    void init();

    DownloadManage *download_manage;
    UploadManage *upload_manage;
    QTabWidget *tabwidget;
};

#endif // MANAGEWIDGET_H
