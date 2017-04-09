#ifndef IMAGEPREVIEW_H
#define IMAGEPREVIEW_H

#include "basicwidget/basicwidget.h"

#include <QtWidgets>
class ImagePreView : public BasicWidget
{
public:
    ImagePreView(QWidget *parent = 0);
    void setPixmap(const QPixmap &pix);

protected:
    void resizeEvent(QResizeEvent *event);

public slots:
    void zoomin();  //放大
    void zoomout(); //缩小
    void download();


private:

    void init();

    QPushButton *left_button;
    QPushButton *right_button;
    QPushButton *download_button;
    QPushButton *fd_button;
    QPushButton *sx_button;
    QLabel *image_view;


    QTimer *t;
    QPixmap pix;
    QMovie *load_gif;

    bool hasPixmap;

    double ratio = 1.0;
};

#endif // IMAGEPREVIEW_H
