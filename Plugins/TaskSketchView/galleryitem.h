#ifndef GALLERYITEM_H
#define GALLERYITEM_H

#include <QWidget>
#include <QImage>
#include <QPaintEvent>
#include <QPainter>

class GalleryItem : public QWidget
{
    Q_OBJECT
public:
    GalleryItem(QImage &image, QWidget *parent = 0);

private:
    QImage imageHandler;
    float imageAspect;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // GALLERYITEM_H
