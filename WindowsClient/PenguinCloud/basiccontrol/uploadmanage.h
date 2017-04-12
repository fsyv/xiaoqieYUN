#ifndef UPLOADMANAGE_H
#define UPLOADMANAGE_H

#include <QtWidgets>

#include "basicwidget/basicwidget.h"

class UploadManage : public BasicWidget
{
public:
    UploadManage(QWidget *parent = 0);
    void addRow(const QString &filename, QProgressBar* &progress, QPushButton* &cancel, QPushButton* &paste);
    ~UploadManage();

private:
    void init();
    QTableWidget *upload;
};

#endif // UPLOADMANAGE_H
