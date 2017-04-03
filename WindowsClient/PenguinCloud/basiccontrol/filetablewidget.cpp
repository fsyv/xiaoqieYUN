#include "filetablewidget.h"
#include <QFileIconProvider>
#include <QFileInfo>
#include <QHeaderView>
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

void FileTableWidget::setTableRow(QVector<QStringList> &_vec)
{
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
