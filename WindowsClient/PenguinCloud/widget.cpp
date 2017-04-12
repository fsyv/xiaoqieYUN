#include "widget.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    open = new QPushButton(tr("open"), this);
    label = new QLabel(this);

    view = new ImagePreView();
    view->show();
    connect(view, &ImagePreView::before, this, &Widget::before_page);
    connect(view, &ImagePreView::next, this, &Widget::next_page);
    document = Poppler::Document::load("H:\\1.pdf");
    if (!document || document->isLocked()) {
        delete document;
        return;
    }
    document->setRenderHint(Poppler::Document::TextAntialiasing);

    document->setRenderBackend(Poppler::Document::SplashBackend );

    open->move(0,0);
    label->move(0, 30);
    label->resize(600, 800);
    connect(open, &QPushButton::clicked, this, Widget::openfile);
    resize(600, 800);
}

Widget::~Widget()
{

}

void Widget::openfile()
{

    Poppler::Page* pdfPage = document->page(++i);
    image = pdfPage->renderToImage(92.56, 92.56, 0, 0, 600,800 );
    view->setPixmap(QPixmap::fromImage(image).scaled(600, 800, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    if(image.isNull())
    {
        qDebug() << "error";
        return ;
    }
    update();

}
void Widget::paintEvent(QPaintEvent *event)
{
    //QPainter p(this);
    QWidget::paintEvent(event);
   // p.drawImage(0, 30, image.scaled(width(), height()));

}

void Widget::next_page()
{
    Poppler::Page* pdfPage = document->page(++i);
    image = pdfPage->renderToImage(92.56, 92.56, 0, 0, 600,800 );
    view->setPixmap(QPixmap::fromImage(image).scaled(600, 800, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    if(image.isNull())
    {
        qDebug() << "error";
        return ;
    }
    update();
    delete pdfPage;
}

void Widget::before_page()
{
    if(i <= 0)
        return;
    Poppler::Page* pdfPage = document->page(--i);
    image = pdfPage->renderToImage(92.56, 92.56, 0, 0, 600,800 );
    view->setPixmap(QPixmap::fromImage(image).scaled(600, 800, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    if(image.isNull())
    {
        qDebug() << "error";
        return ;
    }
    update();
    delete pdfPage;
}
