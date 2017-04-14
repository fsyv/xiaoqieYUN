#include "uploadmanage.h"

UploadManage::UploadManage(QWidget *parent) : BasicWidget(parent)
{
    init();
}

UploadManage::~UploadManage()
{
    delete upload;
}

void UploadManage::init()
{
    setDroped(false);
    hideCloseIcon();

    upload = new QTableWidget(this);
    upload->move(0, 20);
    upload->resize(800, 600);
    QStringList headers;
    headers << "文件名称" << " 上传进度" << "操作";
    upload->setColumnCount(3);
    upload->setHorizontalHeaderLabels(headers);
    upload->verticalHeader()->hide();
    upload->setSelectionBehavior(QAbstractItemView::SelectRows);
    upload->setShowGrid(false);
    upload->setEditTriggers(QAbstractItemView::NoEditTriggers);

    upload->setColumnWidth(0, 200);
    upload->setColumnWidth(1, 510);
    upload->setColumnWidth(2, 85);


}

void UploadManage::addRow(const QString &filename, QProgressBar* &progress, QPushButton* &cancel, QPushButton* &pause)
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

    upload->insertRow(upload->rowCount());

    upload->setRowHeight(upload->rowCount() - 1, 30);

    upload->setItem(upload->rowCount() - 1, 0, item1);
    upload->setItem(upload->rowCount() - 1, 1, item2);
    upload->setItem(upload->rowCount() - 1, 2, item3);

    upload->setCellWidget(upload->rowCount() - 1, 1, w1);
    upload->setCellWidget(upload->rowCount() - 1, 2, w);

}
