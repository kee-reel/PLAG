#include "galleryform.h"
#include "ui_galleryform.h"

GalleryForm::GalleryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GalleryForm)
{
    ui->setupUi(this);
}

GalleryForm::~GalleryForm()
{
    delete ui;
}
