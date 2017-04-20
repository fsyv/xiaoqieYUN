#pragma once
#pragma execution_character_set("utf-8")

#include <QListWidget>

QT_BEGIN_HEADER
class QListWidget;
class QListWidgetItem;
QT_END_NAMESPACE

class ManageListWidget : public QListWidget
{
public:
    ManageListWidget(QWidget *parent = nullptr);
    ~ManageListWidget();

	int findItem(QListWidgetItem *item);
};

