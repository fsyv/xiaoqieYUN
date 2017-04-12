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
    headers << "FileName" << "Progress" << "work";
    upload->setColumnCount(3);
    upload->setHorizontalHeaderLabels(headers);
}

void UploadManage::addRow(const QString &filename, QProgressBar* &progress, QPushButton* &cancel, QPushButton* &pause)
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

    upload->insertRow(upload->rowCount());

    upload->setItem(upload->rowCount() - 1, 0, item1);
    upload->setItem(upload->rowCount() - 1, 1, item2);
    upload->setItem(upload->rowCount() - 1, 2, item3);

    upload->setCellWidget(upload->rowCount() - 1, 1, w1);
    upload->setCellWidget(upload->rowCount() - 1, 2, w);

}
