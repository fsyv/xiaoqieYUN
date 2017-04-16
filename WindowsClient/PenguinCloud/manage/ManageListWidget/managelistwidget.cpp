#include "managelistwidget.h"

ManageListWidget::ManageListWidget(QWidget *parent) :
    QListWidget(parent)
{
    setStyleSheet("QListView{border: 1px solid rgb(202, 212, 219);}");
}

ManageListWidget::~ManageListWidget()
{

}
