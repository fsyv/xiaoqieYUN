#include "managewidget.h"

#include <QVBoxLayout>

#include "ManageTabWidget/managetabwidget.h"

#include "Child/uploadwidget.h"
#include "Child/downloadwidget.h"
#include "Child/finishedwidget.h"

ManageWidget::ManageWidget(QWidget *parent):
    QWidget(parent),
    m_pVBoxLayout(nullptr),
    m_pTabWidget(nullptr),
    m_pUploadWidget(nullptr),
    m_pDownloadWidget(nullptr),
    m_pFinishedWidget(nullptr)
{
    m_pTabWidget = new ManageTabWidget(this);

    m_pUploadWidget = new UploadWidget;
    m_pDownloadWidget = new DownloadWidget;
    m_pFinishedWidget = new FinishedWidget;

    m_pTabWidget->addTab(m_pUploadWidget, QString("上传"));
    m_pTabWidget->addTab(m_pDownloadWidget, QString("下载"));
    m_pTabWidget->addTab(m_pFinishedWidget, QString("完成"));

    m_pVBoxLayout = new QVBoxLayout(this);
    m_pVBoxLayout->addWidget(m_pTabWidget);
}

ManageWidget::~ManageWidget()
{

}

void ManageWidget::addUploadTask(File *file)
{

}

void ManageWidget::addDownloadTask(File *file)
{
    m_pDownloadWidget->addTask(file);
}

void ManageWidget::addFinishedTask(File *file)
{

}
