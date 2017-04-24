#include "finishedlist.h"

#include "../stable.h"
#include "../BasisCtrl/picturelabel.h"
#include "../BasisCtrl/cleanlabel.h"
#include "../file/file.h"
#include "../tools/tools.h"

FinishedList::FinishedList(QListWidget *listWidget, QWidget *parent) :
    QWidget(parent),
    m_pFile(nullptr),
    m_pFileIco(nullptr),
    m_pFileName(nullptr),
    m_pFileSize(nullptr),
    m_pFinishedTime(nullptr),
    m_pCleanButton(nullptr)
{
    setFixedHeight(50);
    initWidget();
    setWidgetLayout();

    m_pListWidgetItem = new QListWidgetItem(listWidget);
    m_pListWidgetItem->setSizeHint(QSize(1, 50));
}

FinishedList::~FinishedList()
{

}

void FinishedList::setFile(File *file)
{
    m_pFile = file;

    QFileInfo fileInfo(file->getRemoteName());

    //加载文件Ico

    setIco();
    setName(fileInfo.fileName());
    setSize(m_pFile->getSize());
    m_pFinishedTime->setText(QTime::currentTime().toString("hh:mm:ss"));
}
File *FinishedList::getFile() const
{
    return m_pFile;
}

QListWidgetItem *FinishedList::getListWidgetItem() const
{
    return m_pListWidgetItem;
}

void FinishedList::initWidget()
{
    m_pFileIco = new PictureLabel(this);
    m_pFileName = new QLabel(this);
    m_pFileSize = new QLabel(this);
    m_pFinishedTime = new QLabel(this);
    m_pCleanButton = new CleanLabel(this);

    connect(m_pCleanButton, SIGNAL(clean()), this, SLOT(clean_cleanButton()));
}

void FinishedList::setWidgetLayout()
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

    m_pFinishedTime->move(width_2, height_2 - 10);
    m_pFinishedTime->resize(QSize(55, 20));

    m_pCleanButton->move(width - 45, height_2 - 10);
}

void FinishedList::destroyWidget()
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

    if(m_pFinishedTime)
        delete m_pFinishedTime;
    m_pFinishedTime = nullptr;

    if(m_pCleanButton)
        delete m_pCleanButton;
    m_pCleanButton = nullptr;
}

void FinishedList::setIco()
{

}

void FinishedList::setName(QString name)
{
    //设置文件名字
    //如果文件名太长，显示...
    QFontMetrics elideFont(m_pFileName->font());
    m_pFileName->setText(elideFont.elidedText(name, Qt::ElideRight, m_pFileName->width()));
}

void FinishedList::setSize(qint64 totalSize)
{
    QString tSize = Tools::sizeToString(totalSize);
    m_pFileSize->setText(tSize);
}

void FinishedList::resizeEvent(QResizeEvent *e)
{
    setWidgetLayout();

    QWidget::resizeEvent(e);
}

void FinishedList::clean_cleanButton()
{
    emit clean(m_pListWidgetItem);
}
