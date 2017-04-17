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
    m_pVBosLayout(nullptr),
    m_pWaittingTask(nullptr)
{
    m_pTopWidget = new DownloadTopWidget;
    m_pListWidget = new ManageListWidget;
    m_pVBosLayout = new QVBoxLayout(this);

    m_pWaittingTask = new QList<File *>;

    m_pVBosLayout->addWidget(m_pTopWidget);
    m_pVBosLayout->addWidget(m_pListWidget);
}

DownloadWidget::~DownloadWidget()
{
    delete m_pTopWidget;
    m_pTopWidget = nullptr;

    delete m_pListWidget;
    m_pListWidget = nullptr;

    delete m_pVBosLayout;
    m_pVBosLayout = nullptr;

    m_pWaittingTask->clear();

    delete m_pWaittingTask;
    m_pWaittingTask = nullptr;
}

void DownloadWidget::addTask(File *file)
{
    if(!m_pWaittingTask->contains(file))
    {
        m_pWaittingTask->append(file);

        QListWidgetItem *item = new QListWidgetItem(m_pListWidget);
        item->setSizeHint(QSize(1, 50));

        DownloadList *downloadList = new DownloadList();

        connect(downloadList, SIGNAL(start(File*)), this, SLOT(startTask(File*)));
        connect(downloadList, SIGNAL(pause(File*)), this, SLOT(pauseTask(File*)));
        connect(downloadList, SIGNAL(stop(File*)), this, SLOT(stopTask(File*)));
        connect(downloadList, SIGNAL(finished(File*)), this, SLOT(finishedTask(File*)));

        downloadList->setFile(file);

        m_pListWidget->setItemWidget(item, downloadList);
    }
    else
    {
        //任务已存在，先不处理
        delete file;
    }

}

void DownloadWidget::startTask(File *file)
{

}

void DownloadWidget::pauseTask(File *file)
{

}

void DownloadWidget::stopTask(File *file)
{

}

void DownloadWidget::finishedTask(File *file)
{

}

