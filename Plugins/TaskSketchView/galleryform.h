#ifndef GALLERYFORM_H
#define GALLERYFORM_H

#include <QWidget>

#include "galleryitem.h"

namespace Ui {
class GalleryForm;
}

class GalleryForm : public QWidget
{
    Q_OBJECT

public:
    explicit GalleryForm(QWidget *parent = 0);
    ~GalleryForm();

    void AddImage(QImage image);

private:
    Ui::GalleryForm *ui;
    QList<GalleryItem*> galleryItems;
};

#endif // GALLERYFORM_H
