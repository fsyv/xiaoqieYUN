#include "imagepreview.h"

ImagePreView::ImagePreView(QWidget *parent) : BasicWidget(parent)
{
    init();
    setBackgroundColor(QColor("33, 33, 34"));
    resize(1300, 800);

}
ImagePreView::~ImagePreView()
{
    qDebug() << "析构";
}

void ImagePreView::init()
{
    left_button = new QPushButton(this);
    left_button->setToolTip("上一张");
    left_button->setStyleSheet("QPushButton{border:none;image:url(\":/resource/image/ImageView/before_normal.png\")} "
                               "QPushButton:hover{image:url(\":/resource/image/ImageView/before.png\")}");
    connect(left_button, &QPushButton::clicked, this, [&](){ emit before(); });


    right_button = new QPushButton(this);
    right_button->setToolTip("下一张");
    right_button->setStyleSheet("QPushButton{border:none;image:url(\":/resource/image/ImageView/next_normal.png\")} "
                                "QPushButton:hover{image:url(\":/resource/image/ImageView/next.png\")}");
    connect(right_button, &QPushButton::clicked, this, [&](){ emit next(); });

    download_button = new QPushButton(this);
    download_button->setToolTip(tr("下载"));
    download_button->setStyleSheet("QPushButton{border:none;image:url(\":/resource/image/ImageView/download_normal.png\")} "
                                   "QPushButton:hover{image:url(\":/resource/image/ImageView/download.png\")}");

    fd_button = new QPushButton(this);
    fd_button->setToolTip(tr("放大"));
    fd_button->setStyleSheet("QPushButton{border:none;image:url(\":/resource/image/ImageView/fd_normal.png\")} "
                             "QPushButton:hover{image:url(\":/resource/image/ImageView/fd.png\")}");
    connect(fd_button, &QPushButton::clicked, this, &ImagePreView::zoomin);


    sx_button = new QPushButton(this);
    sx_button->setToolTip(tr("缩小"));
    sx_button->setStyleSheet("QPushButton{border:none;image:url(\":/resource/image/ImageView/sx_normal.png\")} "
                             "QPushButton:hover{image:url(\":/resource/image/ImageView/sx.png\")}");
    connect(sx_button, &QPushButton::clicked, this, &ImagePreView::zoomout);

    image_view = new QLabel(this);
    image_view->setAlignment(Qt::AlignCenter);

    load_gif = new QMovie(":/resource/image/ImageView/loading.gif");
    image_view->setMovie(load_gif);
    load_gif->start();

    hasPixmap = false;
}

void ImagePreView::resizeEvent(QResizeEvent *event)
{
    BasicWidget::resizeEvent(event);


    int w = width();
    int h = height();

    left_button->setGeometry(0, 0, 50, h);
    right_button->setGeometry(w - 50, 30, 50, h - 30);
    image_view->setGeometry(50, 30 , w - 100, h - 60);

    fd_button->setGeometry((width() - 30) / 2 + 30, height() - 30, 30, 30);
    download_button->setGeometry((width() - 30) / 2 - 15, height() - 30, 30, 30);
    sx_button->setGeometry((width() - 30) / 2 - 60, height() - 30, 30, 30);
    if(hasPixmap)
    {
        double s = qMin(image_view->height() * 1.0 / pix.height() , image_view->width() * 1.0 / pix.width());
        image_view->setPixmap(pix.scaled(QSize(s * pix.width(), s * pix.height())));
    }
}

void ImagePreView::setPixmap(const QPixmap &_pix)
{
    load_gif->stop();
    pix = _pix;
    hasPixmap = true;
    image_view->setPixmap(pix);
}

void ImagePreView::zoomin()
{
    if(hasPixmap)
    {
        ratio *= 1.2;
        image_view->setPixmap(pix.scaled(QSize(ratio * pix.width(), ratio * pix.height())));
    }
}

void ImagePreView::zoomout()
{
    if(hasPixmap)
    {
        ratio *= 0.8;
        image_view->setPixmap(pix.scaled(QSize(ratio * pix.width(), ratio * pix.height())));
    }
}
