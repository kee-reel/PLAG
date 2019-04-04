#include "qimageitemdelegate.h"

QImageItemDelegate::QImageItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{

}

QWidget *QImageItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    GalleryItem *item = new GalleryItem(index.data().toByteArray(), parent);
    //galleryImages.insert(index.internalPointer(), item);
    return item;
}

void QImageItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    GalleryItem *item = static_cast<GalleryItem*>(editor);
    //item->SetImage(index.data().toByteArray());
}

void QImageItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

}

void QImageItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void QImageItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //QStyledItemDelegate::paint(painter, option, index);
    //GalleryItem *item = new GalleryItem(index.data().toByteArray());
//    if(galleryImages.contains(index.internalPointer()))
//    {
//        painter->begin(galleryImages[index.internalPointer()]);
//        painter->end();
//    }
}
