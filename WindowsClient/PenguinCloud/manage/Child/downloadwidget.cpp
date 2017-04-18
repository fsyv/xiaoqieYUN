#include "downloadwidget.h"

#include "../stable.h"

#include "../network/connecttoserver.h"
#include "../network/connecttofileserver.h"
#include "../ChildTopWidget/downloadtopwidget.h"
#include "../ManageListWidget/managelistwidget.h"
#include "../ManageListWidget/downloadlist.h"
#include "../thread/downloadthread.h"


DownloadWidget::DownloadWidget(QWidget *parent) :
    QWidget(parent),
    m_pTopWidget(nullptr),
    m_pListWidget(nullptr),
    m_pVBosLayout(nullptr),
    m_pWaittingTask(nullptr),
    m_pConnectToServer(nullptr),
    m_pThreadPool(nullptr)
{
    m_pThreadPool = new ThreadPool();

    m_pTopWidget = new DownloadTopWidget;
    m_pListWidget = new ManageListWidget;
    m_pVBosLayout = new QVBoxLayout(this);

    m_pExecutingTask = new QMap<File *, UpdateFileThread *>;
    m_pWaittingTask = new QList<File *>;

    m_pVBosLayout->addWidget(m_pTopWidget);
    m_pVBosLayout->addWidget(m_pListWidget);

    setMaxTaskNumbers(5);

    m_pConnectToServer = ConnectToServer::getInstance();
    connect(m_pConnectToServer, SIGNAL(readyReadDownloadMsg(DownloadMsg)), this, SLOT(recvDownloadFile_readyReadDownloadMsg(DownloadMsg)));
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
    if(m_pExecutingTask->count() < m_iMaxTaskNumbers)
    {
        DownloadMsg downloadMsg;
        memset(&downloadMsg, 0, sizeof(DownloadMsg));
        strcpy(downloadMsg.fileName, file->getRemoteName().toUtf8().data());

        m_pConnectToServer->sendDownloadMsg(downloadMsg);

        m_pExecutingTask->insert(file, nullptr);
    }
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

void DownloadWidget::recvDownloadFile_readyReadDownloadMsg(DownloadMsg downloadMsg)
{
    File file(downloadMsg.fileName);

    for(auto cur = m_pExecutingTask->begin(); cur != m_pExecutingTask->end(); ++cur)
    {
        if(*(cur.key()) == file)
        {
            File *f = cur.key();

            QListWidgetItem *item = m_pListWidget->item(m_pWaittingTask->indexOf(f) + m_pExecutingTask->count() - 1);

            DownloadList *downloadList = (DownloadList *)m_pListWidget->itemWidget(item);

            DownloadThread *thread = new DownloadThread(f->getLocalName(), f->getRemoteName(), this);
            connect(thread, &UpdateFileThread::currentTaskProgress, downloadList, &DownloadList::updateTask_currentSize);
            thread->setServerUrl(QString(SERVER_IP), downloadMsg.serverFilePort);
            cur.value() = thread;

            thread->start();
            m_pThreadPool->addJob(thread);
        }
    }
}

