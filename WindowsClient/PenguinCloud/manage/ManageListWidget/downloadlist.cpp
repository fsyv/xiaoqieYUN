#include "downloadlist.h"

#include <QLabel>
#include "../BasisCtrl/picturelabel.h"
#include "../BasisCtrl/pauselabel.h"
#include "../BasisCtrl/stoplabel.h"

DownloadList::DownloadList(QWidget *parent) :
    QWidget(parent),
    m_pFileIco(nullptr),
    m_pFileName(nullptr),
    m_pFileSize(nullptr),
    m_pSurplusTime(nullptr),
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
    destroyWidget();
}

void DownloadList::initWidget()
{
    m_pFileIco = new PictureLabel(QPixmap(":/Resource/MP4.png"), this);
    m_pFileName = new QLabel(QString("好看哒.mp4"), this);
    m_pFileSize = new QLabel(QString("1.0GB/3.5GB"), this);
    m_pSurplusTime = new QLabel(QString("00:10:36"), this);
    m_pCurrentSpeed = new QLabel(QString("20Mb/s"), this);
    m_pPauseButton = new PauseLabel(this);
    m_pPauseButton->startClick();
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

    m_pFileSize->resize(QSize(width_2 - 45, 20));
    m_pFileSize->move(45, height_2);

    m_pSurplusTime->move(width_2, height_2 - 10);
    m_pSurplusTime->resize(QSize(55, 20));

    m_pStopButton->move(width - 45, height_2 - 10);

    m_pPauseButton->move(width - 100, height_2 - 10);

    m_pCurrentSpeed->move(width_2 + 80, height_2);
    m_pCurrentSpeed->resize(width_2 - 200, 20);

}

void DownloadList::destroyWidget()
{

}

void DownloadList::resizeEvent(QResizeEvent *e)
{
    setWidgetLayout();
    QWidget::resizeEvent(e);
}
