#include "downloadwidget.h"

#include "../stable.h"

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

    m_pRunningTask = new QList<File *>();
    m_pWaittingTask = new QList<File *>();

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
    if(!m_pWaittingTask->contains(file))
    {
        QListWidgetItem *item = new QListWidgetItem(m_pListWidget);
        item->setSizeHint(QSize(1, 50));

        DownloadList *downloadList = new DownloadList();

        connect(downloadList, SIGNAL(start(File*)), this, SLOT(startTask(File*)));
        connect(downloadList, SIGNAL(finished(File*)), this, SLOT(finishedTask(File*)));

        downloadList->setFile(file);

        m_pListWidget->setItemWidget(item, downloadList);
        m_pWaittingTask->append(item);
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

void DownloadWidget::startTask(File *file)
{
//    if(m_pExecutingTask->count() < m_iMaxTaskNumbers)
//    {

//    }
}

void DownloadWidget::finishedTask(File *file)
{
    emit finished(file);
}
