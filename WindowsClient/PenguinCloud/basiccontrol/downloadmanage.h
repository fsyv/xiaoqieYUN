#ifndef DOWNLOADMANAGE_H
#define DOWNLOADMANAGE_H

#include <QtWidgets>
#include "basicwidget/basicwidget.h"
class DownloadManage : public BasicWidget
{
    Q_OBJECT
public:
    explicit DownloadManage(BasicWidget *parent = 0);

signals:

public slots:

private:


    QLabel *title;
    QTableWidget *download;
};

#endif // DOWNLOADMANAGE_H
