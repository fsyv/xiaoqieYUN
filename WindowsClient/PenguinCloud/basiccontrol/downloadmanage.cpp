#include "downloadmanage.h"
DownloadManage::DownloadManage(BasicWidget *parent) : BasicWidget(parent)
{
    init();
}
DownloadManage::~DownloadManage()
{
   // delete title;
    delete download;
}

void DownloadManage::init()
{
    setDroped(false);
    hideCloseIcon();

//    title = new QLabel(tr("下载管理"), this);
//    title->move(20, 20);

    download = new QTableWidget(this);
    download->move(0, 20);
    download->resize(800, 600);
    QStringList headers;
    headers << "FileName" << "Progress" << "work";
    download->setColumnCount(3);
    download->setHorizontalHeaderLabels(headers);

}
void DownloadManage::addRow(const QString &filename, QProgressBar* &progress, QPushButton* &cancel, QPushButton* &pause)
{
    QWidget *w1 = new QWidget();
    QHBoxLayout *l = new QHBoxLayout();
    l->addWidget(progress);
    w1->setLayout(l);


    pause->setIcon(QIcon(":/resource/image/DownLoadManage/暂停.png"));
    pause->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    pause->setFixedWidth(50);
    cancel->setIcon(QIcon(":/resource/image/DownLoadManage/取消.png"));
    cancel->setFixedWidth(50);

    QWidget *w = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(pause);
    layout->addWidget(cancel);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    w->setLayout(layout);

    QTableWidgetItem *item1 = new QTableWidgetItem(filename);
    QTableWidgetItem *item2 = new QTableWidgetItem();
    QTableWidgetItem *item3 = new QTableWidgetItem();

    download->insertRow(download->rowCount());

    download->setItem(download->rowCount() - 1, 0, item1);
    download->setItem(download->rowCount() - 1, 1, item2);
    download->setItem(download->rowCount() - 1, 2, item3);

    download->setCellWidget(download->rowCount() - 1, 1, w1);
    download->setCellWidget(download->rowCount() - 1, 2, w);

}
