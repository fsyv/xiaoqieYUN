#ifndef FILETABLEWIDGET_H
#define FILETABLEWIDGET_H

#include <QTableWidget>

class FileTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    FileTableWidget(QWidget *parent = nullptr);
    void setTableRow(const QVector<QStringList> &_vec);
    QList<QString> getSelectedItem();

public slots:

    void rename();
    void del();
    void download();
    void share();
    void moveitem();
    void copy();

    void upload();
    void newfolder();

    void opendir(int row, int column);
    void close_editor(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void test(const QModelIndex &index);
    void selectStatus();
    void selectThisRow(int state);
signals:
    void requestDir(QString dirname);
    void requestNewfolder(const QString &folderName);
    void requestUpload();
    void requestRename(const QString &newname, const QString &oldname);
    void requestDeleteItem(const QString &path);
protected:
    void mouseReleaseEvent(QMouseEvent *event);
private:
    void init();

    QVector<QStringList> files;
    QPoint menu_show; // 记录菜单显示的位置

    bool isEditing;
    bool isNewFolder;
    bool isRename;
    bool isOpen; //当前操作是打开文件夹
    int pre_row = -1;
    QString oldName;
    QTableWidgetItem *edit_item;
};

#endif // FILETABLEWIDGET_H
