#ifndef MANAGELISTWIDGETITEM_H
#define MANAGELISTWIDGETITEM_H

#include <QListWidgetItem>

QT_BEGIN_HEADER
class QListWidgetItem;
QT_END_NAMESPACE

class ManageListWidgetItem : public QListWidgetItem
{
public:
    ManageListWidgetItem();
    ~ManageListWidgetItem();

protected:
    virtual void initWidget();
    virtual void setWidgetLayout();
};

#endif // MANAGELISTWIDGETITEM_H
