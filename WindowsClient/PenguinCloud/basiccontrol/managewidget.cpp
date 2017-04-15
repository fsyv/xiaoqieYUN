#include "managewidget.h"

ManageWidget::ManageWidget(QWidget *parent) : BasicWidget(parent)
{
    setDroped(false);
    resize(800, 600);
    init();
}

ManageWidget::~ManageWidget()
{
    delete download_manage;
    delete upload_manage;
    delete tabwidget;
}

void ManageWidget::init()
{
    tabwidget = new QTabWidget(this);
    tabwidget->resize(this->size());

    download_manage = new DownloadManage(this);
    upload_manage = new UploadManage(this);

    tabwidget->addTab(download_manage, tr("下载管理"));
    tabwidget->addTab(upload_manage, tr("上传管理"));
}

DownloadManage *ManageWidget::getDownloadManage()
{
    return download_manage;
}

UploadManage *ManageWidget::getUploadManage()
{
    return upload_manage;
}
