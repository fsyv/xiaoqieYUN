#include "managetabwidget.h"

#include <QResizeEvent>

ManageTabWidget::ManageTabWidget(QWidget *parent) :
    QTabWidget(parent)
{

}

ManageTabWidget::~ManageTabWidget()
{

}

void ManageTabWidget::resizeEvent(QResizeEvent *e)
{
    QTabWidget::resizeEvent(e);
}
