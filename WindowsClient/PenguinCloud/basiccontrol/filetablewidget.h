#ifndef FILETABLEWIDGET_H
#define FILETABLEWIDGET_H

#include <QTableWidget>

class FileTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    FileTableWidget(QWidget *parent = nullptr);
    void setTableRow(QVector<QStringList> &_vec);
public slots:
    void rename();
    void del();
    void download();
    void share();
    void moveitem();
    void copy();

    void upload();
    void newfolder();

    void close_editor(int currentRow, int currentColumn, int previousRow, int previousColumn);
protected:
    void mouseReleaseEvent(QMouseEvent *event);
private:
    void init();

    QVector<QStringList> files;
    QPoint menu_show; // 记录菜单显示的位置

    bool isEditing;
    QTableWidgetItem *edit_item;
};

#endif // FILETABLEWIDGET_H
