#include "downloadwidget.h"

#include "../stable.h"

#include "../ChildTopWidget/downloadtopwidget.h"
#include "../ManageListWidget/managelistwidget.h"
#include "../ManageListWidget/downloadlist.h"

#include "../file/file.h"

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

    m_pRunningTask = new QList<QWidget *>;
    m_pWaittingTask = new QList<QWidget *>;

    m_pVBosLayout->addWidget(m_pTopWidget);
    m_pVBosLayout->addWidget(m_pListWidget);

    setMaxTaskNumbers(5);
}

DownloadWidget::~DownloadWidget()
{
    delete m_pTopWidget;
    m_pTopWidget = nullptr;

    delete m_pListWidget;
    m_pListWidget = nullptr;

    delete m_pVBosLayout;
    m_pVBosLayout = nullptr;

    //这里需要做系统操作，暂时没写
    m_pRunningTask->clear();
    delete m_pRunningTask;
    m_pRunningTask = nullptr;

    m_pWaittingTask->clear();

    delete m_pWaittingTask;
    m_pWaittingTask = nullptr;
}

void DownloadWidget::addTask(File *file)
{
	static int i = 0;

    if(!contains(file))
    {
        DownloadList *downloadList = new DownloadList();

		if (!i)
		{
			connect(downloadList, SIGNAL(start(QListWidgetItem*)), this, SLOT(startTask(QListWidgetItem*)));
			connect(downloadList, SIGNAL(pause(QListWidgetItem*)), this, SLOT(pauseTask(QListWidgetItem*)));
			connect(downloadList, SIGNAL(stop(QListWidgetItem*)), this, SLOT(stopTask(QListWidgetItem*)));
			connect(downloadList, SIGNAL(finished(QListWidgetItem*)), this, SLOT(finishedTask(QListWidgetItem*)));
			++i;
			qDebug() << "i == " << i;
		}

        m_pListWidget->setItemWidget(downloadList->getListWidgetItem(), downloadList);

        downloadList->setFile(file);
    }
    else
    {
        //任务已存在，先不处理
        delete file;
    }

}

int DownloadWidget::getMaxTaskNumbers() const
{
    return m_iMaxTaskNumbers;
}

void DownloadWidget::setMaxTaskNumbers(int iMaxTaskNumbers)
{
    m_iMaxTaskNumbers = iMaxTaskNumbers;
}

bool DownloadWidget::contains(File *file)
{

    QListWidgetItem *item;
    DownloadList *widget;
    for(int i = 0; i < m_pListWidget->count(); ++i)
    {
        item = m_pListWidget->item(i);
        widget = (DownloadList *)m_pListWidget->itemWidget(item);
        if(widget->getFile() == file)
            return true;
    }
    return false;
}


void DownloadWidget::startTask(QListWidgetItem *item)
{
    DownloadList *widget = (DownloadList *)m_pListWidget->itemWidget(item);

    if(m_pRunningTask->count() < m_iMaxTaskNumbers)
    {
        m_pRunningTask->append(widget);
        widget->startDownload();
        qDebug() << "startTask" << widget->getFile()->getRemoteName();
    }
    else
        m_pWaittingTask->append(widget);

}

void DownloadWidget::pauseTask(QListWidgetItem *item)
{
    QWidget *widget = m_pListWidget->itemWidget(item);
	if (!m_pRunningTask->isEmpty() && m_pRunningTask->contains(widget))
    {
        m_pRunningTask->removeOne(widget);
    }

	if (!m_pWaittingTask->isEmpty() && m_pWaittingTask->contains(widget))
    {
        m_pWaittingTask->removeOne(widget);
    }
}

void DownloadWidget::stopTask(QListWidgetItem *item)
{
    QWidget *widget = m_pListWidget->itemWidget(item);

	if (!m_pRunningTask->isEmpty() && m_pRunningTask->contains(widget))
    {
        m_pRunningTask->removeOne(widget);
    }

	if (!m_pWaittingTask->isEmpty() && m_pWaittingTask->contains(widget))
    {
        m_pWaittingTask->removeOne(widget);
    }


    //m_pListWidget->removeItemWidget(item);
}

void DownloadWidget::finishedTask(QListWidgetItem *item)
{
    DownloadList *widget = (DownloadList *)m_pListWidget->itemWidget(item);
    m_pRunningTask->removeOne(widget);

    if(m_pWaittingTask->count())
    {
        widget = (DownloadList *)m_pWaittingTask->takeFirst();
        widget->startDownload();
    }

    emit finished(widget->getFile());
}
