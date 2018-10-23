#include "galleryitem.h"

GalleryItem::GalleryItem(QWidget *parent)
    : QWidget(parent)
{
    isHover = false;
    isInFocus = false;
}

GalleryItem::GalleryItem(QImage image, QWidget *parent)
    : QWidget(parent)
{
    SetImage(image);
    isHover = false;
    isInFocus = false;
}

GalleryItem::GalleryItem(QByteArray rawImage, QWidget *parent)
    : QWidget(parent)
{
    SetImage(rawImage);
    isHover = false;
    isInFocus = false;
}

void GalleryItem::SetImage(QImage &image)
{
    imageHandler = image;
    imageAspect = imageHandler.width() / (float)imageHandler.height();
    resize(imageHandler.size());
    setMinimumHeight(imageHandler.height()/3);
}

void GalleryItem::SetImage(QByteArray &rawImage)
{
    imageHandler.loadFromData(rawImage);
    imageAspect = imageHandler.width() / (float)imageHandler.height();
    resize(imageHandler.size());
    setMinimumHeight(imageHandler.height()/3);
}

void GalleryItem::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    // TODO: Insert Serg AspectWidget feature
    float newAspect = width() / (float)height();
    QRect pictureRect;
    if(newAspect > imageAspect)
    {
        pictureRect.setWidth(height() * imageAspect);
        pictureRect.setHeight(height());
    }
    else
    {
        pictureRect.setWidth(width());
        pictureRect.setHeight(width() / imageAspect);
    }

    QBrush brush(Qt::black);
    QPen pen(brush, 2);

    painter.setPen(pen);
    float opacity = isInFocus ? 1 : (isHover ? 0.7 : 0.5);
    painter.setOpacity(opacity);
    painter.drawImage(pictureRect, imageHandler);
    painter.drawRect(pictureRect);
    painter.end();
}

void GalleryItem::enterEvent(QEvent *event)
{
    isHover = true;
    repaint();
}

void GalleryItem::leaveEvent(QEvent *event)
{
    isHover = false;
    repaint();
}

void GalleryItem::mouseReleaseEvent(QMouseEvent *event)
{
    emit OnClicked(this);
}
