#include "galleryform.h"
#include "ui_galleryform.h"

GalleryForm::GalleryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GalleryForm)
{
    ui->setupUi(this);
    connect(ui->buttonClose, SIGNAL(clicked(bool)), this, SLOT(close()));
    focusedItem = nullptr;
}

GalleryForm::~GalleryForm()
{
    for(int i = 0; i < galleryItems.count(); ++i)
        delete galleryItems[i];
    delete ui;
}

void GalleryForm::AddImage(int index, QByteArray &rawImage)
{
    QImage image;
    if(!image.loadFromData(rawImage))
    {
        qDebug() << "Cant read image";
        return;
    }

    GalleryItem *item = new GalleryItem(image);
    galleryItems.insert(index, item);
    connect(item, SIGNAL(OnClicked(GalleryItem*)), SLOT(OnItemSelected(GalleryItem*)));
    QVBoxLayout *scrollLayout = static_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout());
    scrollLayout->insertWidget(index, item);
}

void GalleryForm::SetModel(QAbstractItemModel *model)
{
//    ui->listView->setModel(model);
//    QImageItemDelegate *delegate = new QImageItemDelegate(this);
//        ui->listView->setItemDelegate(delegate);
}

void GalleryForm::OnItemSelected(GalleryItem *item)
{
    if(focusedItem)
        focusedItem->isInFocus = false;

    focusedItem = item;
    focusedItem->isInFocus = true;
}

void GalleryForm::on_buttonDelete_clicked()
{
    if(!focusedItem) return;
    int index = galleryItems.indexOf(focusedItem);
    galleryItems.removeAt(index);
    delete focusedItem;
    focusedItem = nullptr;

    emit OnItemDelete(index);
}

void GalleryForm::on_buttonConvertToTask_clicked()
{
    if(!focusedItem) return;
    int index = galleryItems.indexOf(focusedItem);

    emit OnItemConvert(index);
}
