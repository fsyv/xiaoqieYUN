#include "filetablewidget.h"
#include "mainwidget.h"
#include "imagepreview.h"

#include <QFileIconProvider>
#include <QFileInfo>
#include <QHeaderView>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QDateTime>
#include <QTemporaryFile>
#include <QApplication>
#include <QDir>
#include <QCheckBox>
#include <network/connecttoserver.h>

static QString sizeFormat(qint64 size)
{
    double kb = 1024.0;
    double mb = 1024.0 * 1024;
    double gb = mb * 1024.0;

    if(size < kb)
        return QString::number(size) + "b";
    else if(size < mb)
    {
        double k = size / kb;

        return QString::number(k, 'f', 2) + "kb";
    }
    else if(size < gb)
    {
        double m = size / mb;

        return QString::number(m, 'f', 2) + "mb";
    }
    else
    {
        double g = size / gb;

        return QString::number(g, 'f', 2) + "gb";
    }
}

FileTableWidget::FileTableWidget(QWidget *parent) : QTableWidget(parent)
{

    init();

    connect(this, &QTableWidget::currentCellChanged, this, &FileTableWidget::close_editor);
    connect(this, &QTableWidget::cellDoubleClicked, this, &FileTableWidget::opendir);
    //connect(this, &QTableWidget::entered, this, &FileTableWidget::test);
    connect(this, &QTableWidget::itemSelectionChanged, this, &FileTableWidget::selectStatus);

    connect((MainWidget*)parent, &MainWidget::paste, this, [&](bool b)
                                                            {
                                                                isPaste = b;
                                                            });

}
void FileTableWidget::init()
{
    setAlternatingRowColors(true);
    setShowGrid(false);
    setSelectionBehavior(QAbstractItemView::SelectRows); //选中行
    setSelectionMode(QAbstractItemView::SingleSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);// 不可编辑
    setMouseTracking(true);    //开启捕获鼠标功能

    verticalHeader()->hide();   // 隐藏左侧header

    setColumnCount(5);

    setColumnWidth(0, 20);
    setColumnWidth(1, 300);
    setColumnWidth(2, 75);
    setColumnWidth(3, 75);
    setColumnWidth(4, 170);

    QStringList headerlabels;
    headerlabels <<""<<"文件名" << "文件类型" << "文件大小" <<"修改日期";
    setHorizontalHeaderLabels(headerlabels);

    isEditing = false;
    isNewFolder = false;
    isRename = false;
    isPaste = false;
    isOpen = false; //当前操作是打开文件夹

}

void FileTableWidget::selectStatus()
{

    for(int i = 0; i < rowCount(); ++i)
    {
        QCheckBox *cb = static_cast<QCheckBox*>(cellWidget(i, 0));
        if(cb != NULL && item(i, 0) != NULL)
        {
            if(item(i, 0)->isSelected())
            {
                cb->setChecked(true);
            }
            else
            {
                cb->setChecked(false);
            }
        }
    }
}

void FileTableWidget::test(const QModelIndex &index)
{
    int row = index.row();

    for(int i = 0; i < 5; ++i)
    {
        if(item(row, i) != NULL)
            item(row, i)->setBackgroundColor(QColor("#555555"));
    }

    if(pre_row != -1)
    {
        for(int i = 0; i < 5; ++i)
        {
            if(item(pre_row, i) != NULL)
                item(pre_row, i)->setBackgroundColor(Qt::white);

        }
    }
    pre_row = row;

}


//
void FileTableWidget::setTableRow(const QVector<QStringList> &_vec)
{
    pre_row = -1;
    for(int i = 0; i < rowCount();)
    {
        removeRow(0);
    }
    QFileIconProvider p;
    for(int row = 0; row < _vec.size(); ++row)
    {
        QStringList elem = _vec[row];

        insertRow(this->rowCount());
        for(int i = 0; i < 5; ++i)
        {
            QTableWidgetItem *item;
            if(i == 0)
            {
                QCheckBox *box = new QCheckBox;
                box->setSizeIncrement(QSize(20, 20));
                box->setMouseTracking(true);
                item = new QTableWidgetItem;
                connect(box, &QCheckBox::stateChanged, this, &FileTableWidget::selectThisRow);

                this->setCellWidget(row, 0, box);
                setItem(row , 0, item);
            }
            else if( i == 1 )
            {
                QTableWidgetItem *item;
                QTableWidgetItem *item2;
                QIcon icon;
                if( i == 1 )
                {
                    if(elem.at(1) == "folder")
                    {
                        QFileIconProvider p;
                        icon = p.icon(QFileIconProvider::Folder);
                        item = new QTableWidgetItem(icon, elem[0]);
                        item2 = new QTableWidgetItem("文件夹");

                    }
                    else
                    {
                        QStringList staff = elem.at(0).split(".");
                        QString strFileName = QDir::tempPath() + QDir::separator() +
                                QApplication::applicationName() + "_XXXXXX." + staff[staff.size() - 1];
                        QTemporaryFile tmpFile(strFileName);
                        tmpFile.setAutoRemove(false);
                        if(tmpFile.open())
                        {
                            QFileIconProvider p;
                            QFileInfo info(tmpFile.fileName());
                            QString type = p.type(info);
                            item2 = new QTableWidgetItem(type);
                            icon = p.icon(info);
                            item = new QTableWidgetItem(icon, elem[0]);
                        }

                    }

                    setItem(row , 1, item);
                    setItem(row , 2, item2);
                }
            }
            else if(i == 3)
            {
                if(elem[1] == "folder")
                {
                    item = new QTableWidgetItem("-");
                }
                else
                    item = new QTableWidgetItem(sizeFormat(elem[2].toInt()));
                setItem(row , 3, item);
            }
            else if (i == 4)
            {
                item = new QTableWidgetItem(elem[3]);
                setItem(row , 4, item);
            }
        }

    }
}
void FileTableWidget::selectThisRow(int state)
{
    if(state == Qt::Checked)
    {
        QTableWidgetItem *_item = itemAt(mapFromGlobal(QCursor::pos()) - QPoint(-100, horizontalHeader()->height()));
        if(_item != NULL)
        {
            int row = _item->row();
            if(item(row, 1) == NULL)
                return;
            for(int i = 0; i < 5; ++i)
                item(row, i)->setSelected(true);
            //setCurrentItem(item(row, 0));
        }
    }
    else if(state == Qt::Unchecked)
    {
        QTableWidgetItem *_item = itemAt(mapFromGlobal(QCursor::pos()) - QPoint(0, horizontalHeader()->height()));
        if(_item != NULL)
        {
            int row = _item->row();
            if(item(row, 0) == NULL)
                return;
            for(int i = 0; i < 5; ++i)
                item(row, i)->setSelected(false);
        }
    }

}

void FileTableWidget::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "mouseReleaseEvent";
    if(event->button() == Qt::RightButton)
    {
        //    预览    删除 下载  移动  复制  分享
        QMenu *item_menu = new QMenu();
        QAction *preview_action = new QAction(QIcon(":/resource/image/MainWidget/preview.png"), tr("预览"));
        QAction *download_action = new QAction(QIcon(":/resource/image/MainWidget/download.png"), tr("下载"));
        QAction *delete_action = new QAction(QIcon(":/resource/image/MainWidget/delete.png"), tr("删除"));
        QAction *rename_action = new QAction(QIcon(":/resource/image/MainWidget/rename.png"), tr("重命名"));
        QAction *copy_action = new QAction(QIcon(":/resource/image/MainWidget/copy.png"), tr("复制"));
        QAction *move_action = new QAction(QIcon(":/resource/image/MainWidget/move.png"), ("移动"));
        QAction *share_action = new QAction(QIcon(":/resource/image/MainWidget/share.png"), tr("分享"));

        connect(preview_action, &QAction::triggered, this, &FileTableWidget::preview);
        connect(rename_action, &QAction::triggered, this, &FileTableWidget::rename);
        connect(delete_action, &QAction::triggered, this, &FileTableWidget::del);
        connect(download_action, &QAction::triggered, this, &FileTableWidget::download);
        connect(copy_action, &QAction::triggered, this, &FileTableWidget::copy);
        connect(move_action, &QAction::triggered, this, &FileTableWidget::moveitem);
        connect(share_action, &QAction::triggered, this, &FileTableWidget::share);



        item_menu->addAction(preview_action);
        item_menu->addAction(download_action);
        item_menu->addSeparator();
        item_menu->addAction(delete_action);
        item_menu->addAction(rename_action);
        item_menu->addAction(copy_action);
        item_menu->addAction(move_action);
        item_menu->addSeparator();
        item_menu->addAction(share_action);

        //新建文件夹   上传
        QMenu *noitem_menu = new QMenu();
        QAction *new_folder_action = new QAction(QIcon(":/resource/image/MainWidget/newfloder.png"), tr("新建文件夹"));
        QAction *refresh_action = new QAction(QIcon(":/resource/image/MainWidget/refresh.png"), tr("刷新"));
        QAction *paste_action = new QAction(QIcon(":/resource/image/MainWidget/paste.png"), tr("粘贴"));
        QAction *upload_action = new QAction(QIcon(":/resource/image/MainWidget/upload.png"), tr("上传"));

        noitem_menu->addAction(new_folder_action);
        noitem_menu->addAction(refresh_action);
        noitem_menu->addSeparator();
        noitem_menu->addAction(paste_action);
        noitem_menu->addSeparator();
        noitem_menu->addAction(upload_action);
        paste_action->setEnabled(isPaste);
        connect(new_folder_action, &QAction::triggered, this, &FileTableWidget::newfolder);
        connect(refresh_action, &QAction::triggered, this, &FileTableWidget::refresh);
        connect(upload_action, &QAction::triggered, this, &FileTableWidget::upload);
        connect(paste_action, &QAction::triggered, this, [&](){emit requestPaste();});
        //记录菜单显示的位置
        menu_show = event->pos();
        if( itemAt(event->pos()) != 0)
            item_menu->exec(QCursor::pos());
        else
            noitem_menu->exec(QCursor::pos());

    }
    QTableWidget::mouseReleaseEvent(event);
}


void FileTableWidget::rename()
{
    QTableWidgetItem *item = itemAt(menu_show);

    if(item != NULL)
    {
        setCurrentCell(item->row(), 0);
        oldName = item->text();
        openPersistentEditor(item);
        edit_item = item;
        isEditing = true;
        isRename = true;
        editItem(item);
    }

}


void FileTableWidget::preview()
{
    QTableWidgetItem *_item = itemAt(menu_show);

    if(_item != NULL)
    {
        int row = _item->row();
        emit requestPreview(item(row, 1)->text());
        // emit requestDeleteItem(item(row, 1)->text());
    }
}

void FileTableWidget::refresh()
{
    qDebug() << "refresh";
}

void FileTableWidget::del()
{
    QTableWidgetItem *_item = itemAt(menu_show);

    if(_item != NULL)
    {
        int row = _item->row();
        emit requestDeleteItem(item(row, 1)->text());
    }

}

void FileTableWidget::download()
{
    qDebug() << "DownLoad";
}

void FileTableWidget::share()
{
    qDebug() << "share";
}

void FileTableWidget::moveitem()
{
    //返回选中的文件列表
    QStringList copyPaths;
    for(int i = 0; i < rowCount(); ++i)
    {
        if(item(i, 1)->isSelected())
        {
            copyPaths << item(i, 1)->text();
        }
    }

    emit requestMove(copyPaths);
}

void FileTableWidget::copy()
{
    //返回选中的文件列表
    QStringList copyPaths;
    for(int i = 0; i < rowCount(); ++i)
    {
        if(item(i, 1)->isSelected())
        {
            copyPaths << item(i, 1)->text();
        }
    }

    emit requestCopy(copyPaths);
}

void FileTableWidget::upload()
{
    emit requestUpload();
}
void FileTableWidget::newfolder()
{
    insertRow(rowCount());
    QFileIconProvider p;
    QIcon icon = p.icon(QFileIconProvider::Folder);
    edit_item = new QTableWidgetItem(icon, "新建文件夹");
    QTableWidgetItem *type_item = new QTableWidgetItem("文件夹");
    QTableWidgetItem *size_item = new QTableWidgetItem("-");
    QTableWidgetItem *modify_item = new QTableWidgetItem(QDateTime::currentDateTime().toString());
    QCheckBox *box = new QCheckBox;
    box->setSizeIncrement(QSize(20, 20));
    QTableWidgetItem *selectItem = new QTableWidgetItem;
    connect(box, &QCheckBox::stateChanged, this, &FileTableWidget::selectThisRow);
    this->setCellWidget(rowCount() - 1, 0, box);

    setItem(rowCount() - 1, 1, selectItem);
    setItem(rowCount() - 1, 1, edit_item);
    setItem(rowCount() - 1, 2, type_item);
    setItem(rowCount() - 1, 3, size_item);
    setItem(rowCount() - 1, 4, modify_item);
    setCurrentCell(rowCount() - 1, 0);
    openPersistentEditor(edit_item);
    editItem(edit_item);
    isEditing = true;
    isNewFolder = true;
}

void FileTableWidget::close_editor(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    if(isEditing)
        closePersistentEditor(edit_item);
    isEditing = false;

    if(isNewFolder)
    {
        isNewFolder = false;

        emit requestNewfolder(edit_item->text());
    }

    if(isRename)
    {
        isRename = false;
        emit requestRename(edit_item->text(), oldName);
    }
}

void FileTableWidget::opendir(int row, int column)
{
    isOpen = true;
    QTableWidgetItem *_item = item(row, 2);

    if(_item != NULL && _item->text() == "文件夹")
    {
        emit requestDir(item(row, 1 )->text());
    }
    else
    {

    }
}

QList<QString> FileTableWidget::getSelectedItem()
{
    QList<QString> tmp;
    for(int i = 0; i < rowCount(); ++i)
    {
        if(item(i, 1)->isSelected())
            tmp.append(item(i, 1)->text());
    }
    return tmp;
}
