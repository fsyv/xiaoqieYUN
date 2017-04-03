#include "filetablewidget.h"
#include <QFileIconProvider>
#include <QFileInfo>
#include <QHeaderView>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QDebug>
FileTableWidget::FileTableWidget(QWidget *parent) : QTableWidget(parent)
{

    init();
    QStringList list1;
    list1 << "生化危机6.rmvb" << "视频" << "1.76G" << "2017-03-27 19:20:20";
    QStringList list2;
    list2<< "一生所爱.mp3" << "音频" << "5.8M" << "2017-02-10 20:1:56";

    for(int i = 0; i < 10; ++i)
    {
        if(i % 2 == 0)
        {
            files.push_back(list1);
        }else
        {
            files.push_back(list2);
        }
     }

    setTableRow(files);


}

void FileTableWidget::init()
{
    setAlternatingRowColors(true);
    setShowGrid(false);
    verticalHeader()->hide();   // 隐藏左侧header
    setSelectionBehavior(QAbstractItemView::SelectRows); //选中行
    setEditTriggers(QAbstractItemView::NoEditTriggers);// 不可编辑

    setColumnCount(4);
    setColumnWidth(0, 300);
    setColumnWidth(1, 80);
    setColumnWidth(2, 80);
    setColumnWidth(3, 180);

    QStringList headerlabels;
    headerlabels << "文件名" << "文件类型" << "文件大小" <<"修改日期";
    setHorizontalHeaderLabels(headerlabels);

}

//
void FileTableWidget::setTableRow(QVector<QStringList> &_vec)
{
    //clear();
    for(int row = 0; row < _vec.size(); ++row)
    {
        QStringList elem = _vec[row];
        insertRow(this->rowCount());
        for(int i = 0; i < 4; ++i)
        {
            QTableWidgetItem *item;
            if( i == 0 )
            {
                QFileIconProvider p;
                QFileInfo fileinfo(elem[0]);
                QIcon icon = p.icon(fileinfo);

                item = new QTableWidgetItem(icon, elem[0]);

            }
            else
                item = new QTableWidgetItem(elem[i]);
            setItem(row , i, item);
        }

    }
}


void FileTableWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
//        删除 下载  移动  复制  分享
        QMenu *item_menu = new QMenu();
        QAction *download_action = new QAction(tr("下载"));
        QAction *delete_action = new QAction(tr("删除"));
        QAction *rename_action = new QAction(tr("重命名"));
        QAction *copy_action = new QAction(tr("复制"));
        QAction *move_action = new QAction(tr("移动"));
        QAction *share_action = new QAction(tr("分享"));

        connect(rename_action, &QAction::triggered, this, &FileTableWidget::rename);
        connect(delete_action, &QAction::triggered, this, &FileTableWidget::del);
        connect(download_action, &QAction::triggered, this, &FileTableWidget::download);
        connect(copy_action, &QAction::triggered, this, &FileTableWidget::copy);
        connect(move_action, &QAction::triggered, this, &FileTableWidget::moveitem);
        connect(share_action, &QAction::triggered, this, &FileTableWidget::share);




        item_menu->addAction(download_action);
        item_menu->addAction(delete_action);
        item_menu->addAction(rename_action);
        item_menu->addAction(copy_action);
        item_menu->addAction(move_action);
        item_menu->addAction(share_action);

        //新建文件夹   上传
        QMenu *noitem_menu = new QMenu();
        QAction *new_folder_action = new QAction(tr("新建文件夹"));
        QAction *upload_action = new QAction(tr("上传"));

        noitem_menu->addAction(new_folder_action);
        noitem_menu->addAction(upload_action);

//        记录菜单显示的位置
        menu_show = event->pos();
        if( itemAt(event->pos()) != 0)
             item_menu->exec(QCursor::pos());
        else
            noitem_menu->exec(QCursor::pos());

    }
}


void FileTableWidget::rename()
{
    QTableWidgetItem *item = itemAt(menu_show);
    setCurrentCell(item->row(), 0);
    openPersistentEditor(item);
    editItem(item);

    //
}

void FileTableWidget::del()
{
    QTableWidgetItem *item = itemAt(menu_show);
    this->removeRow(item->row());

    //
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
    qDebug() << "move";
}

void FileTableWidget::copy()
{
    qDebug() << "copy";
}
