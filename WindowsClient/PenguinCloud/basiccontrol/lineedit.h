#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QLineEdit>

class QLabel;
class QHBoxLayout;
class LineEdit : public QLineEdit
{
    Q_OBJECT
public:
    LineEdit(QWidget *parent = 0);

    //接口
    void setLeftPixmap(const QString &filename);
private:
    void init();
    QLabel *pix_label; // 显示图片
    QHBoxLayout *h_layout; // 窗口的layout
};

#endif // LINEEDIT_H
