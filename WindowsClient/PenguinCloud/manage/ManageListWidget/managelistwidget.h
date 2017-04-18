#ifndef MANAGELISTWIDGET_H
#define MANAGELISTWIDGET_H

#include <QListWidget>

QT_BEGIN_HEADER
class QListWidget;
QT_END_NAMESPACE

class ManageListWidget : public QListWidget
{
public:
    ManageListWidget(QWidget *parent = nullptr);
    ~ManageListWidget();
};

#endif // MANAGELISTWIDGET_H
