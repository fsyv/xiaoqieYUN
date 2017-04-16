#include "downloadwidget.h"

#include <QVBoxLayout>

#include <QPushButton>

#include "../ChildTopWidget/downloadtopwidget.h"
#include "../ManageListWidget/managelistwidget.h"
#include "../ManageListWidget/downloadlist.h"


DownloadWidget::DownloadWidget(QWidget *parent) :
    QWidget(parent),
    m_pTopWidget(nullptr),
    m_pListWidget(nullptr),
    m_pVBosLayout(nullptr)
{
    m_pTopWidget = new DownloadTopWidget;
    m_pListWidget = new ManageListWidget;
    m_pVBosLayout = new QVBoxLayout(this);


    for(int i = 0; i < 10; ++i)
    {
        QListWidgetItem *item = new QListWidgetItem(m_pListWidget);
        item->setSizeHint(QSize(1, 50));

        m_pListWidget->setItemWidget(item, new DownloadList());
    }


    m_pVBosLayout->addWidget(m_pTopWidget);
    m_pVBosLayout->addWidget(m_pListWidget);
}

DownloadWidget::~DownloadWidget()
{

}
