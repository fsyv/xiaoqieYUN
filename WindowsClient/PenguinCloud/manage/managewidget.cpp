#include "managewidget.h"

#include "../stable.h"

#include "ManageTabWidget/managetabwidget.h"

#include "Child/uploadwidget.h"
#include "Child/downloadwidget.h"
#include "Child/finishedwidget.h"

#include "../file/file.h"

ManageWidget::ManageWidget(QWidget *parent):
    BasicWidget(parent),
    m_pVBoxLayout(nullptr),
    m_pTabWidget(nullptr),
    m_pUploadWidget(nullptr),
    m_pDownloadWidget(nullptr),
    m_pFinishedWidget(nullptr)
{
    setDroped(false);
    setBackgroundColor(QColor(255, 255, 255));

    m_pTabWidget = new ManageTabWidget(this);
    m_pTabWidget->setObjectName("manageTabWidget");

    m_pUploadWidget = new UploadWidget;
    m_pDownloadWidget = new DownloadWidget;
    m_pFinishedWidget = new FinishedWidget;

    m_pTabWidget->addTab(m_pUploadWidget, "正在上传");
    m_pTabWidget->addTab(m_pDownloadWidget, "正在下载");
    m_pTabWidget->addTab(m_pFinishedWidget, "传输完成");


    m_pVBoxLayout = new QVBoxLayout(this);
    m_pVBoxLayout->addWidget(m_pTabWidget);
    m_pVBoxLayout->setSpacing(0);
    m_pVBoxLayout->setContentsMargins(0, 0, 0, 0);


    connect(m_pDownloadWidget, &DownloadWidget::finished, this, &ManageWidget::task_finished);
	connect(m_pUploadWidget, &UploadWidget::finished, this, &ManageWidget::task_finished);
}

ManageWidget::~ManageWidget()
{

}

void ManageWidget::addUploadTask(File *file)
{
	m_pUploadWidget->addTask(file);
}

void ManageWidget::addDownloadTask(File *file)
{
    m_pDownloadWidget->addTask(file);
}

void ManageWidget::addFinishedTask(File *file)
{
    m_pFinishedWidget->addTask(file);
}

void ManageWidget::task_finished(File *file)
{
    QSound::play("://resource/sound/finished.wav");
    addFinishedTask(file);
}
