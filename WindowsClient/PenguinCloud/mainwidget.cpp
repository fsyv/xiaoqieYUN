#include "mainwidget.h"
#include <QtWidgets>
#include <QString>
#include <QDir>

#include "network/connecttoserver.h"
#include "tools/tools.h"
#include "thread/uploadthread.h"

MainWidget::MainWidget(QWidget *parent) :
    BasicWidget(parent),
    m_pConnectToServer(nullptr),
    m_pFileMap(nullptr)
{
    resize(800, 600);
    init();
    setListViewItem();
    setFileTable();
    this->setBackgroundColor(Qt::white);

    path.push("/");

    m_pConnectToServer = ConnectToServer::getInstance();
    connect(m_pConnectToServer, SIGNAL(readyReadFileListMsg(QByteArray)), this, SLOT(recvFileLists(QByteArray)));
    connect(m_pConnectToServer, SIGNAL(readyReadUploadMsg(UploadMsg)), this, SLOT(recvUploadFile(UploadMsg)));

    connect(tableWidget, &FileTableWidget::requestDir, this, &MainWidget::getDir);
    connect(tableWidget, &FileTableWidget::requestNewfolder, this, &MainWidget::newFolder);
    connect(tableWidget, &FileTableWidget::requestUpload, this, &MainWidget::uploadFile);
    connect(tableWidget, &FileTableWidget::requestRename, this, &MainWidget::rename);

    m_pFileMap = new QMap<QString, QFileInfo *>;
}

MainWidget::~MainWidget()
{
    if(m_pFileMap->count())
    {
        for(auto cur = m_pFileMap->begin(); cur != m_pFileMap->end(); ++cur)
        {
            delete cur.value();
            cur.value() = nullptr;
        }
        m_pFileMap->clear();
    }

    if(m_pFileMap)
        delete m_pFileMap;
    m_pFileMap = nullptr;
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

    previous = new QPushButton(QIcon("://resource/widgets/undo_32.png"),
                               tr(" 返回"), this);


    download->setIconSize(QSize(16,16));
    upload->setIconSize(QSize(16,16));
    share->setIconSize(QSize(16,16));
    dele->setIconSize(QSize(16,16));
    previous->setIconSize(QSize(16,16));

    download->move(5, 81);
    upload->move(80, 81);
    share->move(155, 81);
    dele->move(230, 81);
    previous->move(305, 81);


    download->resize(75, 35);
    upload->resize(75, 35);
    share->resize(75, 35);
    dele->resize(75, 35);
    previous->resize(75, 35);

    download->setObjectName("MainWidget_PushButton");
    upload->setObjectName("MainWidget_PushButton");
    share->setObjectName("MainWidget_PushButton");
    dele->setObjectName("MainWidget_PushButton");
    previous->setObjectName("MainWidget_PushButton");


    //一开始是不能后退的
    previous->setEnabled(false);

    connect(upload, SIGNAL(clicked()), this, SLOT(uploadFile()));
    connect(previous, SIGNAL(clicked()), this, SLOT(previousDir()));
    connect(download, SIGNAL(clicked()), this, SLOT(doloadFile_download()));
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

QString MainWidget::getUserName() const
{
    return m_stUserName;
}

void MainWidget::setUserName(const QString &UserName)
{
    m_stUserName = UserName;
    replyFileLists(getCurrentPath());
}


QString MainWidget::getCurrentPath() const
{
    return path.top();
}

void MainWidget::setCurrentPath(const QString &CurrentPath)
{
    path.push(CurrentPath);

    if(path.top() != "/")
        previous->setEnabled(true);
    //目录改变的 时候发送请求文件列表
    replyFileLists(path.top());
}

void MainWidget::replyFileLists(const QString &FolderPath)
{
    FileListsMsg fileListsMsg;
    memset(&fileListsMsg, 0, sizeof(FileListsMsg));

    strcat(fileListsMsg.m_aFolderPath, m_stUserName.toUtf8().data());
    strcat(fileListsMsg.m_aFolderPath, FolderPath.toUtf8().data());

    m_pConnectToServer->sendFileListMsg(fileListsMsg);
}

void MainWidget::setFileTable()
{
    tableWidget = new FileTableWidget(this);
    tableWidget->resize(650, 480);
    tableWidget->move(150, 120);
}



void MainWidget::recvFileLists(QByteArray byteArray)
{
    tableWidget->setTableRow(Tools::getTableRow(byteArray));
}

void MainWidget::recvUploadFile(UploadMsg uploadMsg)
{
    qDebug()<< "serverPort" << uploadMsg.serverFilePort;
    QString name(uploadMsg.fileName);

    QFileInfo *fileinfo = m_pFileMap->value(name);

    UploadThread *uploadThread = new UploadThread(*fileinfo, uploadMsg);
    uploadThread->start();
}

void MainWidget::getDir(QString dirname)
{
    setCurrentPath(getCurrentPath() + dirname + "/");
}

void MainWidget::previousDir()
{
    if(path.size() > 1)
        path.pop();

    if(path.top() == "/")
        previous->setEnabled(false);


    replyFileLists(path.top());
}

void MainWidget::uploadFile()
{
    QStringList fileList = QFileDialog::getOpenFileNames(
                this,
                QString("选择上传文件"),
                QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).at(0)
                );

    //没有选择文件
    if(!fileList.count())
        return;

    UploadMsg uploadMsg;
    QFileInfo *fileInfo = nullptr;

    for(const QString &str : fileList)
    {
        fileInfo = new QFileInfo(str);

        m_pFileMap->insert(fileInfo->fileName(), fileInfo);

        memset(&uploadMsg, 0, sizeof(UploadMsg));

        strcpy(uploadMsg.fileName, fileInfo->fileName().toUtf8().data());
        strcpy(uploadMsg.uploadPath, m_stUserName.toUtf8().data());
        strcat(uploadMsg.uploadPath, path.top().toUtf8().data());

        m_pConnectToServer->sendUploadMsg(uploadMsg);
    }
}

void MainWidget::doloadFile_download()
{
    qDebug() << listView->currentIndex();
}

void MainWidget::newFolder(const QString &folderName)
{
    QString folderPath = path.top() + folderName;

    NewFolderMsg newFolderMsg;
    memset(&newFolderMsg, 0, sizeof(NewFolderMsg));
    strcpy(newFolderMsg.folderName, m_stUserName.toUtf8().data());
    strcat(newFolderMsg.folderName, folderPath.toUtf8().data());

    m_pConnectToServer->sendNewFolderMsg(newFolderMsg);
}

void MainWidget::rename(const QString &newName, const QString &oldName)
{
    QString new_path = m_stUserName + path.top() + newName;
    QString old_path = m_stUserName + path.top() + oldName;
    RenameMsg renameMsg;
    memset(&renameMsg, 0, sizeof(RenameMsg));
    strcpy(renameMsg.newName, new_path.toUtf8().data());
    strcpy(renameMsg.oldName, old_path.toUtf8().data());
    m_pConnectToServer->sendRenameMsg(renameMsg);
    replyFileLists(path.top());
}

void MainWidget::renameError(RenameMsg r){
       qDebug() << "Rename Error";
}
