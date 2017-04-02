﻿#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "basicwidget/basicwidget.h"
#include "network/msgtype.h"

class QLabel;
class QPushButton;
class QToolButton;
class QListView;
class QTableView;
class ConnectToServer;

class MainWidget : public BasicWidget
{
public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

    QString getUserName() const;
    void setUserName(const QString &UserName);

    QString getPrePath() const;
    void setPrePath(const QString &PrePath);

    QString getCurrentPath() const;
    void setCurrentPath(const QString &CurrentPath);

    void replyFileLists(const QString &FolderPath);

protected:
    void paintEvent(QPaintEvent *event);

protected slots:
    void recvFileLists(FileListsMsg fileListsMsg);

private:
    void init();
    void setListViewItem();
    void setTableView();

    ConnectToServer *m_pConnectToServer;

    QLabel *label; // 显示图标
    QPushButton *download;
    QPushButton *upload;
    QPushButton *dele;
    QPushButton *share;
    QListView *listView;
    QTableView *tableView;

    QString m_stUserName;
    QString m_stPrePath;
    QString m_stCurrentPath;
};

#endif // MAINWIDGET_H