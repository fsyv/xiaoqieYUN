#include "uploadwidget.h"

#include <QVBoxLayout>

#include "../ChildTopWidget/uploadtopwidget.h"
#include "../ManageListWidget/managelistwidget.h"

UploadWidget::UploadWidget(QWidget *parent) :
    QWidget(parent),
    m_pTopWidget(nullptr),
    m_pListWidget(nullptr),
    m_pVBosLayout(nullptr)
{
    m_pTopWidget = new UploadTopWidget;
    m_pListWidget = new ManageListWidget;
    m_pVBosLayout = new QVBoxLayout(this);

    m_pVBosLayout->addWidget(m_pTopWidget);
    m_pVBosLayout->addWidget(m_pListWidget);
}

UploadWidget::~UploadWidget()
{

}
