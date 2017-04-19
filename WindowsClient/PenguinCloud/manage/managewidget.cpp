#include "managewidget.h"

#include "../stable.h"

#include "ManageTabWidget/managetabwidget.h"

#include "Child/uploadwidget.h"
#include "Child/downloadwidget.h"
#include "Child/finishedwidget.h"

#include "../file/file.h"

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

    connect(m_pDownloadWidget, &DownloadWidget::finished, this, &ManageWidget::task_finished);
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

void ManageWidget::task_finished(File *file)
{
    QSound::play("://resource/sound/finished.wav");
    addFinishedTask(file);
}
