#ifndef GALLERYITEM_H
#define GALLERYITEM_H

#include <QWidget>

namespace Ui {
class GalleryItem;
}

class GalleryItem : public QWidget
{
    Q_OBJECT

public:
    explicit GalleryItem(QWidget *parent = 0);
    ~GalleryItem();

private:
    Ui::GalleryItem *ui;
};

#endif // GALLERYITEM_H
