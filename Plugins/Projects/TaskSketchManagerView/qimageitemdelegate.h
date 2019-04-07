#ifndef QIMAGEITEMDELEGATE_H
#define QIMAGEITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QApplication>
#include <QImage>
#include <QHash>

#include "galleryitem.h"

class QImageItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
private:
    QHash<void*, GalleryItem> galleryImages;
public:
    explicit QImageItemDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};
#endif // QIMAGEITEMDELEGATE_H
