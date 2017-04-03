#include "mainwidget.h"
#include <QtWidgets>

#include "network/connecttoserver.h"

MainWidget::MainWidget(QWidget *parent) :
    BasicWidget(parent),
    m_pConnectToServer(nullptr)
{
    resize(800, 600);
    init();
    setListViewItem();
    setFileTable();
    this->setBackgroundColor(Qt::white);

    m_pConnectToServer = ConnectToServer::getInstance();
    connect(m_pConnectToServer, SIGNAL(readyReadFileListMsg(FileListsMsg)), this, SLOT(recvFileLists(FileListsMsg)));
}

MainWidget::~MainWidget()
{

}

QString MainWidget::getUserName() const
{
    return m_stUserName;
}

void MainWidget::setUserName(const QString &UserName)
{
    m_stUserName = UserName;

    //设置为根目录
    //设置当前路径
    setCurrentPath("/");
    setPrePath("/");

    replyFileLists(getCurrentPath());
}

QString MainWidget::getPrePath() const
{
    return m_stPrePath;
}

void MainWidget::setPrePath(const QString &PrePath)
{
    m_stPrePath = PrePath;
}

QString MainWidget::getCurrentPath() const
{
    return m_stCurrentPath;
}

void MainWidget::setCurrentPath(const QString &CurrentPath)
{
    setPrePath(getCurrentPath());
    m_stCurrentPath = CurrentPath;
}

void MainWidget::replyFileLists(const QString &FolderPath)
{
    FileListsMsg fileListsMsg;
    memset(&fileListsMsg, 0, sizeof(FileListsMsg));

    strcat(fileListsMsg.m_aFolderPath, m_stUserName.toLatin1().data());
    strcat(fileListsMsg.m_aFolderPath, FolderPath.toLatin1().data());

    m_pConnectToServer->sendFileListMsg(fileListsMsg);
}

void MainWidget::setFileTable()
{
    tableWidget = new FileTableWidget(this);

//    tableView->setAlternatingRowColors(true);
//    tableView->setShowGrid(false);
//    tableView->verticalHeader()->hide();   // 隐藏左侧header
//    tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //选中行
//    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);// 不可编辑
    tableWidget->resize(650, 480);
    tableWidget->move(150, 120);

}

void MainWidget::setListViewItem()
{
    listView = new QListView(this);
    QStandardItemModel *model = new QStandardItemModel(this);
    
    QStringList itemsicon, itemsname;
    itemsicon << ":/resource/image/MainWidget/allfile.png" << ":/resource/image/MainWidget/photo.png" <<
          ":/resource/image/MainWidget/doc.png"<< ":/resource/image/MainWidget/film.png" << ":/resource/image/MainWidget/music.png";
    itemsname << "全部文件" << "图片" << "文档" << "视频" << "音乐";

    for(int i = 0; i < itemsname.size(); ++i)
    {
        QStandardItem *item = new QStandardItem(QIcon(itemsicon[i]), itemsname[i]);
        item->setSizeHint(QSize(70, 35));
        model->appendRow(item);
        item->setEditable(false);
    }

    listView->setModel(model);
    listView->move(0, 120);
    listView->resize(150, 480);
}

void MainWidget::init()
{
    label = new QLabel(this);
    label->setPixmap(QPixmap(":/resource/image/title.png"));

    download = new QPushButton(QIcon(":/resource/image/MainWidget/download.png"),
                               tr(" 下载"), this);
    upload = new QPushButton(QIcon(":/resource/image/MainWidget/upload.png"),
                               tr(" 上传"), this);
    share = new QPushButton(QIcon(":/resource/image/MainWidget/share.png"),
                               tr(" 分享"), this);
    dele = new QPushButton(QIcon(":/resource/image/MainWidget/delete.png"),
                               tr(" 删除"), this);


    download->setIconSize(QSize(16,16));
    upload->setIconSize(QSize(16,16));
    share->setIconSize(QSize(16,16));
    dele->setIconSize(QSize(16,16));

    download->move(5, 81);
    upload->move(80, 81);
    share->move(155, 81);
    dele->move(230, 81);

    download->resize(75, 35);
    upload->resize(75, 35);
    share->resize(75, 35);
    dele->resize(75, 35);

    download->setObjectName("MainWidget_PushButton");
    upload->setObjectName("MainWidget_PushButton");
    share->setObjectName("MainWidget_PushButton");
    dele->setObjectName("MainWidget_PushButton");
}

void MainWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    p.save();
    p.setPen(Qt::NoPen);
    p.setBrush(QBrush("#0698f5"));
    p.drawRect(0, 0, this->width(), 80);
    p.restore();
    p.save();
    p.setPen(Qt::NoPen);
    p.drawRect(0, 80, this->width(), 40);
    p.restore();
    p.drawRect(0, 0, width() - 1, height() - 1);
}

void MainWidget::recvFileLists(FileListsMsg fileListsMsg)
{
    qDebug() << "recvFileLists";
}
