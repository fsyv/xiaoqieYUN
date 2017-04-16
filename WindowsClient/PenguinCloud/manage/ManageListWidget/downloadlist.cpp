#include "downloadlist.h"

#include <QLabel>
#include <QProgressBar>
#include "../BasisCtrl/picturelabel.h"
#include "../BasisCtrl/pauselabel.h"
#include "../BasisCtrl/stoplabel.h"
#include "../file/file.h"

DownloadList::DownloadList(QWidget *parent) :
    QWidget(parent),
    m_pFile(nullptr),
    m_pFileIco(nullptr),
    m_pFileName(nullptr),
    m_pFileSize(nullptr),
    m_pSurplusTime(nullptr),
    m_pProgressBar(nullptr),
    m_pCurrentSpeed(nullptr),
    m_pPauseButton(nullptr),
    m_pStopButton(nullptr)
{
    setFixedHeight(50);
    initWidget();
    setWidgetLayout();
}

DownloadList::~DownloadList()
{
    m_pFile = 0;
    destroyWidget();
}

void DownloadList::setFile(File *file)
{
    m_pFile = file;

    QFileInfo fileInfo(file->getName());

    //加载文件Ico

    setIco();
    setName(fileInfo.fileName());
    setSize(0LL, m_pFile->getSize());
    updateProgressBar(0);
    setSpeed("等待中...");

}

void DownloadList::initWidget()
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
}

void DownloadList::setWidgetLayout()
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

void DownloadList::destroyWidget()
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

void DownloadList::setIco()
{

}

void DownloadList::setName(QString name)
{
    //设置文件名字
    //如果文件名太长，显示...
    QFontMetrics elideFont(m_pFileName->font());
    m_pFileName->setText(elideFont.elidedText(fileInfo.fileName(), Qt::ElideRight, m_pFileName->width()));
}

void DownloadList::setSize(qint64 currentSize, qint64 totalSize)
{

}

void DownloadList::updateProgressBar(int progress)
{
    m_pProgressBar->setValue(progress);
}

void DownloadList::setSpeed(QString speed)
{
    m_pCurrentSpeed->setText(speed);
}

void DownloadList::setSpeed(qint64 speed)
{

}

void DownloadList::resizeEvent(QResizeEvent *e)
{
    setWidgetLayout();
    QWidget::resizeEvent(e);
}
