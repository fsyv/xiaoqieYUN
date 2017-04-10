#ifndef DOWNLOADMANAGE_H
#define DOWNLOADMANAGE_H

#include <QtWidgets>
#include "basicwidget/basicwidget.h"
class DownloadManage : public BasicWidget
{
    Q_OBJECT
public:
    explicit DownloadManage(BasicWidget *parent = 0);
    void addRow(const QString &filename, QProgressBar* &progress, QPushButton* &cancel, QPushButton* &paste);
signals:

public slots:

private:
    void init();

    QLabel *title;
    QTableWidget *download;
};

#endif // DOWNLOADMANAGE_H
