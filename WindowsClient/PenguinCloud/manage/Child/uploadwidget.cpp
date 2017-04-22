#include "uploadwidget.h"

#include "../stable.h"

#include "../ChildTopWidget/uploadtopwidget.h"
#include "../ManageListWidget/managelistwidget.h"
#include "../ManageListWidget/uploadlist.h"

#include "../file/file.h"

UploadWidget::UploadWidget(QWidget *parent) :
    QWidget(parent),
    m_pTopWidget(nullptr),
    m_pListWidget(nullptr),
    m_pVBosLayout(nullptr)
{
    m_pTopWidget = new UploadTopWidget;
    m_pListWidget = new ManageListWidget;
    m_pVBosLayout = new QVBoxLayout(this);
    m_pVBosLayout->setContentsMargins(0, 0, 0, 0);
    m_pVBosLayout->setSpacing(0);

	m_pRunningTask = new QList<QWidget *>;
	m_pWaittingTask = new QList<QWidget *>;
    m_pVBosLayout->addWidget(m_pTopWidget);
    m_pVBosLayout->addWidget(m_pListWidget);
	setMaxTaskNumbers(5);
}

UploadWidget::~UploadWidget()
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

void UploadWidget::addTask(File *file)
{
	static int i = 0;

	if (!contains(file))
	{
		UploadList *uploadList = new UploadList(m_pListWidget);

		connect(uploadList, SIGNAL(start(QListWidgetItem*)), this, SLOT(startTask(QListWidgetItem*)));
		connect(uploadList, SIGNAL(pause(QListWidgetItem*)), this, SLOT(pauseTask(QListWidgetItem*)));
		connect(uploadList, SIGNAL(stop(QListWidgetItem*)), this, SLOT(stopTask(QListWidgetItem*)));
		connect(uploadList, SIGNAL(finished(QListWidgetItem*)), this, SLOT(finishedTask(QListWidgetItem*)));

		m_pListWidget->setItemWidget(uploadList->getListWidgetItem(), uploadList);

		uploadList->setFile(file);
	}
	else
	{
		//任务已存在，先不处理
		delete file;
	}

}

int UploadWidget::getMaxTaskNumbers() const
{
	return m_iMaxTaskNumbers;
}

void UploadWidget::setMaxTaskNumbers(int iMaxTaskNumbers)
{
	m_iMaxTaskNumbers = iMaxTaskNumbers;
}

bool UploadWidget::contains(File *file)
{
	QListWidgetItem *item;
	UploadList *widget;
	for (int i = 0; i < m_pListWidget->count(); ++i)
	{
		item = m_pListWidget->item(i);
		widget = (UploadList *)m_pListWidget->itemWidget(item);

		if (!widget)
			continue;

		if (widget->getFile() == file)
			return true;
	}
	return false;
}


void UploadWidget::startTask(QListWidgetItem *item)
{
	UploadList *widget = (UploadList *)m_pListWidget->itemWidget(item);

	if (m_pRunningTask->count() < m_iMaxTaskNumbers)
	{
		m_pRunningTask->append(widget);
		widget->startUpload();
	}
	else
		m_pWaittingTask->append(widget);

}

void UploadWidget::pauseTask(QListWidgetItem *item)
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

void UploadWidget::stopTask(QListWidgetItem *item)
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


	m_pListWidget->removeItemWidget(item);
}

void UploadWidget::finishedTask(QListWidgetItem *item)
{
	UploadList *widget = (UploadList *)m_pListWidget->itemWidget(item);
	m_pRunningTask->removeOne(widget);

	if (m_pWaittingTask->count())
	{
		widget = (UploadList *)m_pWaittingTask->takeFirst();
		widget->startUpload();
	}

	emit finished(widget->getFile());

	int index = m_pListWidget->findItem(item);

	if (index >= 0)
	{
		m_pListWidget->removeItemWidget(item);
		m_pListWidget->takeItem(index);

		delete widget;
		widget = nullptr;

		delete item;
		item = nullptr;
	}
}
