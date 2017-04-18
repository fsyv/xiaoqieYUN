﻿#include <QDir>
#include <QString>
#include <QtWidgets>
#include <QStatusBar>

#include <stdio.h>
#include "file/file.h"
#include "mainwidget.h"
#include "file/folder.h"
#include "tools/tools.h"
#include "thread/ThreadPool.h"
#include "thread/uploadthread.h"
#include "thread/downloadthread.h"
#include "network/connecttoserver.h"
#include "basicwidget/mymessagebox.h"
#include "basiccontrol/imagepreview.h"
#include "basiccontrol/downloadmanage.h"


MainWidget::MainWidget(QWidget *parent) :
    BasicWidget(parent),
    m_pConnectToServer(nullptr),
    m_pUploadTaskLists(nullptr),
    m_pDownloadTaskLists(nullptr),
    m_pThreadPool(nullptr)
{
    m_pThreadPool = new ThreadPool();
    resize(800, 600);
    init();
    setListViewItem();
    setFileTable();
    manageUpAndDown = new ManageWidget(this);
    manageUpAndDown->move(1, 80);
    manageUpAndDown->setFixedSize(800, 480);
    manageUpAndDown->hide();
    this->setBackgroundColor(Qt::white);

    path.push("/");

    m_pConnectToServer = ConnectToServer::getInstance();
    connect(m_pConnectToServer, SIGNAL(readyReadFileListMsg(QByteArray)), this, SLOT(recvFileLists(QByteArray)));
    connect(m_pConnectToServer, SIGNAL(readyReadUploadMsg(UploadMsg)), this, SLOT(recvUploadFile_readyReadUploadMsg(UploadMsg)));
    connect(m_pConnectToServer, SIGNAL(readyReadDownloadMsg(DownloadMsg)), this, SLOT(recvDownloadFile_readyReadDownloadMsg(DownloadMsg)));
    connect(m_pConnectToServer, &ConnectToServer::readyReadAckErrorMsg, this, &MainWidget::errorHandle);
    connect(m_pConnectToServer, &ConnectToServer::readyReadPreviewMsg, this, &MainWidget::show_prview);


    connect(tableWidget, &FileTableWidget::requestDir, this, &MainWidget::getDir);
    connect(tableWidget, &FileTableWidget::requestNewfolder, this, &MainWidget::newFolder);
    connect(tableWidget, &FileTableWidget::requestUpload, this, &MainWidget::uploadFile_upload);
    connect(tableWidget, &FileTableWidget::requestRename, this, &MainWidget::rename);
    connect(tableWidget, &FileTableWidget::requestDeleteItem, this, &MainWidget::removeFileOrFolder);
    connect(tableWidget, &FileTableWidget::requestCopy, this, &MainWidget::copySelectFilesOrFolder);
    connect(tableWidget, &FileTableWidget::requestMove, this, &MainWidget::moveSelectFilesOrFolder);
    connect(tableWidget, &FileTableWidget::requestPaste, this, &MainWidget::pasteSelected);
    connect(tableWidget, &FileTableWidget::requestPreview, this, &MainWidget::preview);
    connect(tableWidget, &FileTableWidget::requsetRefresh, this, &MainWidget::refresh);
    //  m_pFileMap = new QMap<QString, QFileInfo *>;


    m_pUploadTaskLists = new QMap<QString, UpdateFileThread *>;
    m_pDownloadTaskLists = new QMap<QString, UpdateFileThread *>;
    m_pFileLists = new QMap<QString, FileObject *>;
}

MainWidget::~MainWidget()
{
    //清空上传列表
    if(m_pUploadTaskLists->count())
    {
        for(auto cur = m_pUploadTaskLists->begin(); cur != m_pUploadTaskLists->end(); ++cur)
        {
            if(cur.value())
            {
                cur.value()->pause();
                delete cur.value();
            }
        }
        m_pUploadTaskLists->clear();
    }

    if(m_pUploadTaskLists)
        delete m_pUploadTaskLists;
    m_pUploadTaskLists = nullptr;

    //清空下载
    if(m_pDownloadTaskLists->count())
    {
        for(auto cur = m_pDownloadTaskLists->begin(); cur != m_pDownloadTaskLists->end(); ++cur)
        {
            if(cur.value())
            {
                //                cur.value()->pause();
                //                //等待任务结束
                //                cur.value()->wait(1000);
                delete cur.value();
            }
        }
        m_pDownloadTaskLists->clear();
    }

    if(m_pDownloadTaskLists)
        delete m_pDownloadTaskLists;
    m_pDownloadTaskLists = nullptr;

    m_pFileLists->clear();
    if(m_pFileLists)
        delete m_pFileLists;
    m_pFileLists = nullptr;

    if(m_pThreadPool)
        delete m_pThreadPool;
    m_pThreadPool = nullptr;
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

    listView->move(1, 120);
    listView->resize(150, 449);
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
    sys_info = new QLabel(this);
    download_manage = new QPushButton(this);
    download_manage->setIcon(QIcon(":/resource/image/MainWidget/download_manage.png"));


    download->setIconSize(QSize(16,16));
    upload->setIconSize(QSize(16,16));
    share->setIconSize(QSize(16,16));
    dele->setIconSize(QSize(16,16));
    previous->setIconSize(QSize(16,16));
    download_manage->setIconSize(QSize(32, 32));

    download->move(5, 81);
    upload->move(80, 81);
    share->move(155, 81);
    dele->move(230, 81);
    previous->move(305, 81);
    download_manage->move(693, 569);

    download->resize(75, 35);
    upload->resize(75, 35);
    share->resize(75, 35);
    dele->resize(75, 35);
    previous->resize(75, 35);
    download_manage->resize(100, 30);
    download->setObjectName("MainWidget_PushButton");
    upload->setObjectName("MainWidget_PushButton");
    share->setObjectName("MainWidget_PushButton");
    dele->setObjectName("MainWidget_PushButton");
    previous->setObjectName("MainWidget_PushButton");
    download_manage->setObjectName("MainWidget_PushButton");

    //一开始是不能后退的
    previous->setEnabled(false);

    connect(upload, SIGNAL(clicked()), this, SLOT(uploadFile_upload()));
    connect(previous, SIGNAL(clicked()), this, SLOT(previousDir()));
    connect(download, SIGNAL(clicked()), this, SLOT(doloadFile_download()));
    connect(download_manage, &QPushButton::clicked, this, &MainWidget::show_manage);
    connect(dele, &QPushButton::clicked, this, &MainWidget::removeSelected);

    isCopy = false;
}

void MainWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    p.save();
    p.setPen(Qt::NoPen);
    p.setBrush(QBrush("#1296db"));
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
    tableWidget->resize(649, 449);
    tableWidget->move(150, 120);
}



void MainWidget::recvFileLists(QByteArray byteArray)
{
    tableWidget->setTableRow(Tools::getTableRow(byteArray));

    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(byteArray, &json_error);
    if(json_error.error == QJsonParseError::NoError)
    {
        if(parse_doucment.isObject())
        {
            QJsonObject object = parse_doucment.object();
            QJsonValue value =  object.value(object.keys().at(0));
            QJsonArray array = value.toArray();
            QString path = object.keys().at(0);

            m_pFileLists->clear();

            for(int i = 0; i < array.size(); ++i)
            {
                QStringList list;

                if(array.at(i).toObject().value("type") == QString("folder"))
                {
                    //文件夹
                    QDateTime dateTime = QDateTime::fromTime_t(array.at(i).toObject()
                                                               .value("lastmodifytime").toInt());
                    QString name = array.at(i).toObject().value("name").toString();

                    m_pFileLists->insert(path + name, new Folder(name, dateTime));
                }
                else if(array.at(i).toObject().value("type") == QString("file"))
                {
                    //文件
                    QDateTime dateTime = QDateTime::fromTime_t(array.at(i).toObject()
                                                               .value("lastmodifytime").toInt());
                    QString name = array.at(i).toObject().value("name").toString();
                    qint64 size = array.at(i).toObject().value("size").toVariant().toLongLong();

                    m_pFileLists->insert(path + name, new File(name, size, dateTime));
                }
            }
        }
    }
}

void MainWidget::recvUploadFile_readyReadUploadMsg(UploadMsg uploadMsg)
{
    QString name(uploadMsg.fileName);

    UploadThread *thread = (UploadThread *)m_pUploadTaskLists->value(name);

    if(thread)
    {
        thread->setServerUrl(QString(SERVER_IP), uploadMsg.serverFilePort);
        thread->start();
        m_pThreadPool->addJob(thread);
    }
}

void MainWidget::recvDownloadFile_readyReadDownloadMsg(DownloadMsg downloadMsg)
{
    QString name(downloadMsg.fileName);

    DownloadThread *thread = (DownloadThread *)m_pDownloadTaskLists->value(name);

    if(thread)
    {
        thread->setServerUrl(QString(SERVER_IP), downloadMsg.serverFilePort);
        FileObject *fileObject = m_pFileLists->value(thread->getRemotePath());
        thread->setFileSize(fileObject->getSize());
        thread->start();
        m_pThreadPool->addJob(thread);
    }
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

void MainWidget::refresh()
{
    replyFileLists(path.top());
}

void MainWidget::uploadFile_upload() noexcept
{
    QStringList fileList = QFileDialog::getOpenFileNames(
                this,
                QString("选择上传文件"),
                QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).at(0)
                );

    //没有选择文件
    if(!fileList.count())
        return;

    for(const QString &str : fileList)
    {
        if(!m_pUploadTaskLists->keys().contains(str))
        {
            try{
                UploadThread *upload_t =  new UploadThread(str, m_stUserName + path.top(), this);
                m_pUploadTaskLists->insert(str, upload_t);


                QPushButton *cancel = new QPushButton();
                cancel->setIcon(QIcon(":/resource/image/DownLoadManage/cancel.png"));
                connect(cancel, &QPushButton::clicked, this, [upload_t](){
                    //取消逻辑
                    upload_t->stop();
                });
                QPushButton *pause = new QPushButton();
                pause->setIcon(QIcon(":/resource/image/DownLoadManage/pause.png"));
//                connect(pause, &QPushButton::clicked, this, [upload_t, pause](){
//                    if(upload_t->getCurrentStatus())
//                    {
//                        upload_t->pause();
//                        pause->setIcon(QIcon(":/resource/image/DownLoadManage/jixu.png"));
//                    }
//                    else
//                    {
//                        upload_t->start();
//                        pause->setIcon(QIcon(":/resource/image/DownLoadManage/pause.png"));
//                    }
//                });

                connect(pause, &QPushButton::clicked, this, [upload_t](){
                    //暂停逻辑
                    upload_t->pause();
                });

                QProgressBar *bar = new QProgressBar();
                bar->setMaximum(100);
                connect(upload_t, &UploadThread::currentTaskProgress, this, [bar](double d){
                    //进度条逻辑
                    bar->setValue(d * 100);
                    qDebug() << d;
                });

                manageUpAndDown->getUploadManage()->addRow(str.split('/').last(), bar, cancel, pause);
                manageUpAndDown->getUploadManage()->addRow(str, bar, cancel, pause);

                UploadMsg uploadMsg;
                memset(&uploadMsg, 0, sizeof(UploadMsg));
                strcpy(uploadMsg.fileName, upload_t->getLocalPath().toUtf8().data());

                m_pConnectToServer->sendUploadMsg(uploadMsg);
            }
            catch(QString e){
                qDebug() << e;
            }
        }
    }
}

void MainWidget::doloadFile_download()
{
    for(int i = 0; i < tableWidget->rowCount(); ++i)
    {
        QTableWidgetItem *_item = tableWidget->item(i, 1);

        if(!_item)
            return ;

        if(tableWidget->item(i, 2)->text() == "文件夹")
        {
        }
        else if(_item->isSelected())
        {
            if(!m_pDownloadTaskLists->keys().contains(m_stUserName + path.top() + _item->text()))
            {
                DownloadThread *uft = new DownloadThread(\
                            QDir::currentPath() + QString("/penguin/") + m_stUserName + path.top() + _item->text(), \
                            m_stUserName + path.top() + _item->text(), \
                            this\
                            );

                m_pDownloadTaskLists->insert(uft->getRemotePath(), uft);

                //在这里添加按钮的槽函数
                QPushButton *cancel = new QPushButton();
                cancel->setIcon(QIcon(":/resource/image/DownLoadManage/cancel.png"));
                connect(cancel, &QPushButton::clicked, this, [uft](){
                    uft->stop();
                });
                QPushButton *pause = new QPushButton();
                pause->setIcon(QIcon(":/resource/image/DownLoadManage/pause.png"));
//                connect(pause, &QPushButton::clicked, this, [uft, pause](){
//                    if(uft->getCurrentStatus())
//                    {
//                        uft->pause();
//                        pause->setIcon(QIcon(":/resource/image/DownLoadManage/jixu.png"));
//                    }
//                    else
//                    {
//                        uft->start();
//                        pause->setIcon(QIcon(":/resource/image/DownLoadManage/pause.png"));
//                    }
//                });

                connect(pause, &QPushButton::clicked, this, [uft](){
                    uft->pause();
                });

                QProgressBar *bar = new QProgressBar();
                bar->setMaximum(100);
                connect(uft, &UpdateFileThread::currentTaskProgress, this, [bar](double d){
                    bar->setValue(d * 100);
                    qDebug() << d;
                });

                manageUpAndDown->getDownloadManage()->addRow(_item->text().split('/').last(), bar, cancel, pause);

                DownloadMsg downloadMsg;
                memset(&downloadMsg, 0, sizeof(DownloadMsg));
                strcpy(downloadMsg.fileName, uft->getRemotePath().toUtf8().data());

                m_pConnectToServer->sendDownloadMsg(downloadMsg);
            }
        }
    }
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

void MainWidget::removeFileOrFolder(const QString &_path)
{
    QString wholepath = m_stUserName + path.top() + _path;

    DeleteMsg deleteMsg;
    memset(&deleteMsg, 0, sizeof(DeleteMsg));
    strcpy(deleteMsg.path, wholepath.toUtf8().data());
    m_pConnectToServer->sendDeleteMsg(deleteMsg);
    replyFileLists(path.top());
}

void MainWidget::renameError(RenameMsg r){
    qDebug() << "Rename Error";
}

void MainWidget::show_manage()
{
    if(manageUpAndDown->isHidden())
    {
        manageUpAndDown->show();
    }
    else
    {
        manageUpAndDown->hide();
    }
}

void MainWidget::removeSelected()
{
    QList<QString> items = tableWidget->getSelectedItem();
    if(items.size() > 0)
    {
        for(auto elem : items)
        {
            removeFileOrFolder(elem);
        }
        MyMessageBox *m = MyMessageBox::showMessageBox(this, "删除成功!", "", "确定",  Ok);
        connect(m, &MyMessageBox::btn2, this, [m](){m->close();});
    }
    else
    {
        MyMessageBox *m = MyMessageBox::showMessageBox(this, "未选中任何项目!", "", "确定",  Warn);
        connect(m, &MyMessageBox::btn2, this, [m](){m->close();});
    }

}

void MainWidget::copySelectFilesOrFolder(const QStringList &_path)
{
    wholeCopyPath.clear(); //先清空

    for(auto elem : _path)
    {
        wholeCopyPath << path.top() + elem;
    }

    isCopy = true;
    emit paste(true);

}

void MainWidget::moveSelectFilesOrFolder(const QStringList &_path)
{
    wholeCopyPath.clear(); //先清空

    for(auto elem : _path)
    {
        wholeCopyPath << path.top() + elem;
    }

    isCopy = false;
    emit paste(true);

}


void MainWidget::pasteSelected()
{
    QString currpath = getUserName() + path.top();
    if(isCopy)
    {
        // 复制操作
        for(auto elem : wholeCopyPath)
        {

            QString tmpPath = getUserName() + elem;
            currpath.chop(1); //移除最后的一个 '/'
            CopyMsg copyMsg;

            memset(&copyMsg, 0, sizeof(MoveMsg));
            strcpy(copyMsg.sourcePath, tmpPath.toUtf8().data());
            strcpy(copyMsg.DestinationPath, currpath.toUtf8().data());
            m_pConnectToServer->sendCopyMsg(copyMsg);
        }

        replyFileLists(path.top());
        emit paste(false);
    }
    else
    {
        //移动操作
        for(auto elem : wholeCopyPath)
        {

            QString tmpPath = getUserName() + elem;
            MoveMsg moveMsg;

            memset(&moveMsg, 0, sizeof(MoveMsg));
            strcpy(moveMsg.sourcePath, tmpPath.toUtf8().data());
            strcpy(moveMsg.DestinationPath, currpath.toUtf8().data());
            m_pConnectToServer->sendMoveMsg(moveMsg);
        }

        replyFileLists(path.top());
        emit paste(false);
    }
}

void MainWidget::errorHandle(ErrorMsg msg)
{
    //之所以使用按位与是因为 在msg中搞得错误类型是 几个值的按位或而来的
    if(msg.m_eErrorType & RenameError)
    {
        QMessageBox::warning(this, tr("无法重命名项目"), tr("存在相同名称的项目！"));
        replyFileLists(path.top());
    }
}

void MainWidget::preview(const QString &_path)
{
    PreviewMsg previewMsg;
    memset(&previewMsg, 0, sizeof(PreviewMsg));

    QString wholepath = getUserName() + path.top() +  _path;
    qDebug() << wholepath;
    strcpy(previewMsg.path, wholepath.toUtf8().data());
    m_pConnectToServer->sendPreviewMsg(previewMsg);

    //    qDebug() << "显示预览";
    //    ImagePreView *pw = new ImagePreView();
    //    QPixmap p1(":/resource/image/title.png");
    //    pw->setPixmap(p1);
    //    pw->show();
    setPreviewWidget(Tools::getFileType(_path));
}

void MainWidget::show_prview(PreviewArray previewMsg)
{
    qDebug() << "显示预览";
    ImagePreView *pw = new ImagePreView();

    QPixmap p1(":/resource/image/title.png");
    pw->setPixmap(p1);
    pw->show();
}

void MainWidget::setPreviewWidget(FileType type)
{
    switch(type)
    {
    case PDF:
    {
        PdfWidget *pdfWidget = new PdfWidget();
        pdfWidget->setPdfFile("H://1.pdf");
        pdfWidget->close();

    }
        break;
    case PICTURE:
    {
        ImagePreView *pre = new ImagePreView();
        pre->show();
    }
        break;

        //音乐啥的处理

    }
}




