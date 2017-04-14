#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include<QMap>
#include <QStack>
#include <QQueue>
#include "basicwidget/basicwidget.h"
#include "network/msgtype.h"
#include "basiccontrol/pdfwidget.h"
#include "basiccontrol/filetablewidget.h"
#include "basiccontrol/managewidget.h"
#include "tools/tools.h"

class QLabel;
class QPushButton;
class QToolButton;
class QListView;
class QTableView;
class ConnectToServer;
class QFileInfo;
class DownloadManage;
class UpdateFileThread;
class FileObject;
class ThreadPool;

class MainWidget : public BasicWidget
{
    Q_OBJECT
public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
    QString getUserName() const;
    QString getCurrentPath() const;
    QString getPrePath() const;

    void setUserName(const QString &UserName);
    void setPrePath(const QString &PrePath);
    void setCurrentPath(const QString &CurrentPath);

    void replyFileLists(const QString &FolderPath);


    void setPreviewWidget(FileType);



protected:
    void paintEvent(QPaintEvent *event);


signals:
    void paste(bool);
public slots:
    void recvFileLists(QByteArray byteArray);
    void recvUploadFile_readyReadUploadMsg(UploadMsg uploadMsg);
    void recvDownloadFile_readyReadDownloadMsg(DownloadMsg downloadMsg);
    void getDir(QString dirname);
    void previousDir();
    void uploadFile_upload() noexcept;
    void doloadFile_download();
    void newFolder(const QString &folderName);
    void removeFileOrFolder(const QString &path);
    void rename(const QString &newName, const QString &oldName);
    void renameError(RenameMsg r);
    void show_manage();
    void refresh();
    void removeSelected();
    void copySelectFilesOrFolder(const QStringList &path);
    void moveSelectFilesOrFolder(const QStringList &path);
    void pasteSelected();
    void errorHandle(ErrorMsg msg);                                         // 错误处理
    void preview(const QString &path);
    void show_prview(PreviewArray previewMsg);
private:
    void init();
    void setListViewItem();
    void setFileTable();

    ConnectToServer *m_pConnectToServer;

    QLabel *label; // 显示图标
    QPushButton *download;
    QPushButton *upload;
    QPushButton *dele;
    QPushButton *share;
    QPushButton *previous;
    QListView *listView;
    FileTableWidget *tableWidget;
    DownloadManage *load;
    ManageWidget *manageUpAndDown;


    QLabel *sys_info;
    QPushButton *download_manage;
    QString m_stUserName;

    QStack<QString> path;// current dir

    //上传任务列表
    QMap<QString, UpdateFileThread *> *m_pUploadTaskLists;
    //下载任务列表
    QMap<QString, UpdateFileThread *> *m_pDownloadTaskLists;

    QMap<QString, FileObject *> *m_pFileLists;

    QStringList wholeCopyPath; // 保存所有将要复制的文件的具体路径
    bool isCopy; // true是复制， false是移动

    ThreadPool *m_pThreadPool;
};

#endif // MAINWIDGET_H
