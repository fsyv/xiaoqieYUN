#include "finishedwidget.h"

#include <QVBoxLayout>

#include "../ChildTopWidget/finishedtopwidget.h"
#include "../ManageListWidget/managelistwidget.h"

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

}
