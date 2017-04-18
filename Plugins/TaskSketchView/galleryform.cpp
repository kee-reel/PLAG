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
    for(int i = 0; i < galleryItems.count(); ++i)
        delete galleryItems[i];
    delete ui;
}

void GalleryForm::AddImage(QImage image)
{
    GalleryItem *item = new GalleryItem(image, this);
    galleryItems.append(item);
    QLayout *scrollLayout = ui->scrollAreaWidgetContents->layout();
    scrollLayout->addWidget(item);
}
