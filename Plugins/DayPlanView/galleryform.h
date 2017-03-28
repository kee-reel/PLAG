#ifndef GALLERYFORM_H
#define GALLERYFORM_H

#include <QWidget>

namespace Ui {
class GalleryForm;
}

class GalleryForm : public QWidget
{
    Q_OBJECT

public:
    explicit GalleryForm(QWidget *parent = 0);
    ~GalleryForm();

private:
    Ui::GalleryForm *ui;
};

#endif // GALLERYFORM_H
