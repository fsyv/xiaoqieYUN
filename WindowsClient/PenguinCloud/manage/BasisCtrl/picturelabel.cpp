#include "picturelabel.h"

PictureLabel::PictureLabel(QWidget *parent) :
    QLabel(parent)
{

}

PictureLabel::PictureLabel(const QPixmap &picture, QWidget *parent):
    PictureLabel(parent)
{
    setPixmap(QPixmap(picture));
    setScaledContents(true);
}

PictureLabel::~PictureLabel()
{

}
