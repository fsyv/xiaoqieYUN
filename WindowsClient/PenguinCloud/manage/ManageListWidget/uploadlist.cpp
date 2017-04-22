#include "uploadlist.h"

#include "stable.h"
#include "../BasisCtrl/picturelabel.h"
#include "../BasisCtrl/pauselabel.h"
#include "../BasisCtrl/stoplabel.h"
#include "../file/file.h"
#include "../tools/tools.h"
#include "../thread/uploadthread.h"
#include "../network/connecttoserver.h"

UploadList::UploadList(QListWidget *listWidget, QWidget *parent) : 
    QWidget(parent),
    m_pFile(nullptr),
    m_i64CurrentSize(0LL),
    m_pFileIco(nullptr),
    m_pFileName(nullptr),
    m_pFileSize(nullptr),
    m_pSurplusTime(nullptr),
    m_pProgressBar(nullptr),
    m_pCurrentSpeed(nullptr),
    m_pPauseButton(nullptr),
    m_pStopButton(nullptr),
    m_pUploadThread(nullptr)
{
    setFixedHeight(50);
    initWidget();
    setWidgetLayout();

    m_eCurrentStatus = CurrentStatus::NOSTATUS;

    m_pListWidgetItem = new QListWidgetItem(listWidget);
    m_pListWidgetItem->setSizeHint(QSize(1, 50));

    m_pConnectToServer = ConnectToServer::getInstance();
	connect(m_pConnectToServer, SIGNAL(readyReadUploadMsg(UploadMsg)), this, SLOT(recvUploadFile_readyReadUploadMsg(UploadMsg)));
}

UploadList::~UploadList()
{
    m_pFile = 0;
    destroyWidget();
}

void UploadList::setFile(File *file)
{
    m_pFile = file;

    QFileInfo fileInfo(file->getRemoteName());

    //加载文件Ico

    setIco();
    setName(fileInfo.fileName());
    setSize(m_i64CurrentSize, m_pFile->getSize());
    m_pSurplusTime->setText("--");
    updateProgressBar(0);
    setSpeed("等待中...");

    //加入就开始任务
    m_pPauseButton->startClick();
}

File *UploadList::getFile() const
{
    return m_pFile;
}

QListWidgetItem *UploadList::getListWidgetItem() const
{
    return m_pListWidgetItem;
}

void UploadList::startUpload()
{
	UploadMsg uploadMsg;
	memset(&uploadMsg, 0, sizeof(UploadMsg));
	strcpy(uploadMsg.fileName, m_pFile->getRemoteName().toUtf8().data());

	m_pConnectToServer->sendUploadMsg(uploadMsg);
}

void UploadList::initWidget()
{
    m_pFileIco = new PictureLabel(this);
    m_pFileName = new QLabel(this);
    m_pFileSize = new QLabel(this);
    m_pSurplusTime = new QLabel(this);
    m_pProgressBar = new QProgressBar(this);
    m_pProgressBar->setMaximum(100);
    m_pCurrentSpeed = new QLabel(this);
    m_pPauseButton = new PauseLabel(this);
    m_pStopButton = new StopLabel(this);
    connect(m_pPauseButton, SIGNAL(start()), this, SLOT(start_pauseButton()));
    connect(m_pPauseButton, SIGNAL(pause()), this, SLOT(pause_pauseButton()));
    connect(m_pStopButton, SIGNAL(stop()), this, SLOT(stop_stopButton()));
}

void UploadList::setWidgetLayout()
{
    int height = this->height();
    int width = this->width();

    //二分之一
    int height_2 = height / 2;
    int width_2 = width / 2;

    m_pFileIco->move(5, height_2 - 20);
    m_pFileIco->resize(QSize(35, 40));

    m_pFileName->resize(QSize(width_2 - 45, 20));
    m_pFileName->move(45, height_2 - 20);
    QFontMetrics elideFont(m_pFileName->font());
    m_pFileName->setText(elideFont.elidedText(m_pFileName->text(), Qt::ElideRight, m_pFileName->width()));

    m_pFileSize->resize(QSize(width_2 - 45, 20));
    m_pFileSize->move(45, height_2);

    m_pSurplusTime->move(width_2, height_2 - 10);
    m_pSurplusTime->resize(QSize(55, 20));

    m_pStopButton->move(width - 45, height_2 - 10);

    m_pPauseButton->move(width - 100, height_2 - 10);

    m_pProgressBar->move(width_2 + 80, height_2 - 20);
    m_pProgressBar->resize(width_2 - 200, 20);

    m_pCurrentSpeed->move(width_2 + 80, height_2);
    m_pCurrentSpeed->resize(width_2 - 200, 20);
}

void UploadList::destroyWidget()
{
    if(m_pFileIco)
        delete m_pFileIco;
    m_pFileIco = nullptr;

    if(m_pFileName)
        delete m_pFileName;
    m_pFileName = nullptr;

    if(m_pFileSize)
        delete m_pFileSize;
    m_pFileSize = nullptr;

    if(m_pSurplusTime)
        delete m_pSurplusTime;
    m_pSurplusTime = nullptr;

    if(m_pProgressBar)
        delete m_pProgressBar;
    m_pProgressBar = nullptr;

    if(m_pCurrentSpeed)
        delete m_pCurrentSpeed;
    m_pCurrentSpeed = nullptr;

    if(m_pPauseButton)
        delete m_pPauseButton;
    m_pPauseButton = nullptr;

    if(m_pStopButton)
        delete m_pStopButton;
    m_pStopButton = nullptr;
}

void UploadList::setIco()
{

}

void UploadList::setName(QString name)
{
    //设置文件名字
    //如果文件名太长，显示...
    QFontMetrics elideFont(m_pFileName->font());
    m_pFileName->setText(elideFont.elidedText(name, Qt::ElideRight, m_pFileName->width()));
}

void UploadList::setSize(qint64 currentSize, qint64 totalSize)
{
    QString cSize = Tools::sizeToString(currentSize);
    QString tSize = Tools::sizeToString(totalSize);
    m_pFileSize->setText(cSize + QString("/") + tSize);
}

void UploadList::updateProgressBar(int progress)
{
    m_pProgressBar->setValue(progress);
}

void UploadList::setSpeed(QString speed)
{
    m_pCurrentSpeed->setText(speed);
}

void UploadList::setSpeed(qint64 speed)
{
    QString speedStr = Tools::sizeToString(speed);
    setSpeed(speedStr + QString("/s"));
}

void UploadList::resizeEvent(QResizeEvent *e)
{
    setWidgetLayout();
    QWidget::resizeEvent(e);
}

void UploadList::updateTask_currentSize(qint64 currentSize)
{
    setSpeed(currentSize - m_i64CurrentSize);
    m_i64CurrentSize = currentSize;
    setSize(m_i64CurrentSize, m_pFile->getSize());
    updateProgressBar(m_i64CurrentSize * 1.0 / m_pFile->getSize() * 100);

    if(m_i64CurrentSize == m_pFile->getSize())
    {
        if(m_eCurrentStatus == CurrentStatus::RUNNING)
        {
			delete m_pUploadThread;
			m_pUploadThread = nullptr;
        }

        m_eCurrentStatus = CurrentStatus::FINISHED;
        emit finished(m_pListWidgetItem);
    }
}

void UploadList::start_pauseButton()
{
    m_eCurrentStatus = CurrentStatus::WAITTING;
    emit start(m_pListWidgetItem);
}

void UploadList::pause_pauseButton()
{
    if(m_eCurrentStatus == CurrentStatus::RUNNING)
    {
		m_pUploadThread->pause();
		delete m_pUploadThread;
		m_pUploadThread = nullptr;
    }

    m_eCurrentStatus = CurrentStatus::PAUSED;
    emit pause(m_pListWidgetItem);
}

void UploadList::stop_stopButton()
{
    if(m_eCurrentStatus == CurrentStatus::RUNNING)
    {
		m_pUploadThread->stop();
		delete m_pUploadThread;
		m_pUploadThread = nullptr;
    }

    m_eCurrentStatus = CurrentStatus::STOP;
    emit stop(m_pListWidgetItem);
}

void UploadList::recvUploadFile_readyReadUploadMsg(UploadMsg uploadMsg)
{
	disconnect(m_pConnectToServer, SIGNAL(readyReadUploadMsg(UploadMsg)), this, SLOT(recvUploadFile_readyReadUploadMsg(UploadMsg)));

	if (m_eCurrentStatus == CurrentStatus::WAITTING)
	{
		m_eCurrentStatus = CurrentStatus::RUNNING;

		m_pUploadThread = new UploadThread(m_pFile->getLocalName(), m_pFile->getRemoteName(), this);
		connect(m_pUploadThread, &UpdateFileThread::currentTaskProgress, this, &UploadList::updateTask_currentSize);
		m_pUploadThread->setServerUrl(QString(SERVER_IP), uploadMsg.serverFilePort);

		m_pUploadThread->start();
		ThreadPool::getInstance()->addJob(m_pUploadThread);
	}
}