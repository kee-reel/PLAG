#include "galleryitem.h"

GalleryItem::GalleryItem(QImage &image, QWidget *parent) : QWidget(parent)
{
    imageHandler = image;
    imageAspect = image.width() / image.height();
    resize(image.size());
}

void GalleryItem::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    // TODO: Insert Serg AspectWidget feature
    painter.drawImage(rect(), imageHandler);
    painter.end();
}
