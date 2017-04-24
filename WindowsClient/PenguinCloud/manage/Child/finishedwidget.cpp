#include "finishedwidget.h"

#include "../stable.h"

#include "../ChildTopWidget/finishedtopwidget.h"
#include "../ManageListWidget/managelistwidget.h"
#include "../ManageListWidget/finishedlist.h"

FinishedWidget::FinishedWidget(QWidget *parent) : 
    QWidget(parent),
    m_pTopWidget(nullptr),
    m_pListWidget(nullptr),
    m_pVBosLayout(nullptr)
{
    m_pTopWidget = new FinishedTopWidget;
    m_pListWidget = new ManageListWidget;
    m_pVBosLayout = new QVBoxLayout(this);
    m_pVBosLayout->setContentsMargins(0, 0, 0, 0);
    m_pVBosLayout->setSpacing(0);
    m_pVBosLayout->addWidget(m_pTopWidget);
    m_pVBosLayout->addWidget(m_pListWidget);
}

FinishedWidget::~FinishedWidget()
{
    delete m_pTopWidget;
    m_pTopWidget = nullptr;

    delete m_pListWidget;
    m_pListWidget = nullptr;

    delete m_pVBosLayout;
    m_pVBosLayout = nullptr;
}

void FinishedWidget::addTask(File *file)
{
    FinishedList *finishedList = new FinishedList(m_pListWidget);
    connect(finishedList, &FinishedList::clean, this, &FinishedWidget::cleanTask);

    m_pListWidget->setItemWidget(finishedList->getListWidgetItem(), finishedList);

    finishedList->setFile(file);
}

void FinishedWidget::cleanTask(QListWidgetItem *item)
{
    m_pListWidget->removeItemWidget(item);
}
