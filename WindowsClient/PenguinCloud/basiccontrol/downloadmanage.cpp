#include "downloadmanage.h"
DownloadManage::DownloadManage(BasicWidget *parent) : BasicWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
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
    headers << "文件名称" << "下载进度" << "操作";
    download->setColumnCount(3);
    download->setHorizontalHeaderLabels(headers);
    download->verticalHeader()->hide();
    download->setSelectionBehavior(QAbstractItemView::SelectRows);
    download->setShowGrid(false);
    download->setEditTriggers(QAbstractItemView::NoEditTriggers);

    download->setColumnWidth(0, 200);
    download->setColumnWidth(1, 510);
    download->setColumnWidth(2, 85);


}
void DownloadManage::addRow(const QString &filename, QProgressBar* &progress, QPushButton* &cancel, QPushButton* &pause)
{
    QWidget *w1 = new QWidget();
    QHBoxLayout *l = new QHBoxLayout();
    l->addWidget(progress);
    w1->setLayout(l);

    pause->setFixedWidth(50);
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
    download->setRowHeight(download->rowCount() - 1, 30);


    download->setItem(download->rowCount() - 1, 0, item1);
    download->setItem(download->rowCount() - 1, 1, item2);
    download->setItem(download->rowCount() - 1, 2, item3);

    download->setCellWidget(download->rowCount() - 1, 1, w1);
    download->setCellWidget(download->rowCount() - 1, 2, w);

}
