#pragma once
#pragma execution_character_set("utf-8")
#include "managelistwidget.h"

ManageListWidget::ManageListWidget(QWidget *parent) :
    QListWidget(parent)
{
    setStyleSheet("QListView{border: 1px solid rgb(202, 212, 219);}");
}

ManageListWidget::~ManageListWidget()
{

}

int ManageListWidget::findItem(QListWidgetItem *item)
{
	for (int i = 0; i < count(); ++i)
	{
		if (this->item(i) == item)
			return i;
	}
	return -1;
}