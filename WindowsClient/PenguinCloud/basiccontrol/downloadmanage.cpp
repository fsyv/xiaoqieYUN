#include "downloadmanage.h"
DownloadManage::DownloadManage(BasicWidget *parent) : BasicWidget(parent)
{
    //this->setBackgroundColor(QColor(Qt::gray));
//    acceptDrop(false);
//    hideCloseIcon();

    title = new QLabel(tr("下载管理"), this);
    title->move(20, 20);

    download = new QTableWidget(this);
    download->move(0, 60);
    download->resize(800, 600);
    QStringList headers;
    headers << "FileName" << "Progress" << "work";
    download->setColumnCount(3);
    download->setHorizontalHeaderLabels(headers);

    QProgressBar *prog = new QProgressBar;
    prog->setValue(0);
    prog->setMaximum(1024);
    //connect()
    QPushButton *button = new QPushButton("cannel");

    QTableWidgetItem *item1 = new QTableWidgetItem("filename");
    QTableWidgetItem *item2 = new QTableWidgetItem();
    QTableWidgetItem *item3 = new QTableWidgetItem();

    download->insertRow(download->rowCount());
    download->setItem(0, 0, item1);
    download->setItem(0, 1, item2);
    download->setItem(0, 2, item3);



    download->setCellWidget(0, 1, prog);
    download->setCellWidget(0, 2, button);
}
