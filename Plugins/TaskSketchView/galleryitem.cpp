#include "galleryitem.h"
#include "ui_galleryitem.h"

GalleryItem::GalleryItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GalleryItem)
{
    ui->setupUi(this);
}

GalleryItem::~GalleryItem()
{
    delete ui;
}
