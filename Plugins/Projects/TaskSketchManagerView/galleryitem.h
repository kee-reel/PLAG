#ifndef GALLERYITEM_H
#define GALLERYITEM_H

#include <QByteArray>
#include <QDebug>
#include <QImage>
#include <QPainter>
#include <QPaintEvent>
#include <QWidget>

class GalleryItem : public QWidget
{
    Q_OBJECT
public:
    bool isInFocus;

    GalleryItem(QWidget *parent = 0);
    GalleryItem(QImage image, QWidget *parent = 0);
    GalleryItem(QByteArray rawImage, QWidget *parent = 0);

    void SetImage(QImage &image);
    void SetImage(QByteArray &rawImage);

    void paint(QPainter *painter, const QRect &rect, const QPalette &palette) const;

private:
    QImage imageHandler;
    float imageAspect;
    bool isHover;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    void OnClicked(GalleryItem*);
};
#endif // GALLERYITEM_H
