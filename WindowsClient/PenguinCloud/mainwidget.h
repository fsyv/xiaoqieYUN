#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "basicwidget/basicwidget.h"

class QLabel;
class QPushButton;
class QToolButton;
class QListView;
class QTableView;
class MainWidget : public BasicWidget
{
public:
    MainWidget(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);



private:
    void init();
    void setListViewItem();
    void setTableView();

    QLabel *label; // 显示图标
    QPushButton *download;
    QPushButton *upload;
    QPushButton *dele;
    QPushButton *share;
    QListView *listView;
    QTableView *tableView;

};

#endif // MAINWIDGET_H
