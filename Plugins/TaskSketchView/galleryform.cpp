#include "galleryform.h"
#include "ui_galleryform.h"

GalleryForm::GalleryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GalleryForm)
{
    ui->setupUi(this);
    connect(ui->buttonClose, SIGNAL(clicked(bool)), this, SLOT(close()));
}

GalleryForm::~GalleryForm()
{
    delete ui;
}
