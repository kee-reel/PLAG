#ifndef GALLERYFORM_H
#define GALLERYFORM_H

#include <QWidget>
#include <QAbstractItemModel>

#include "qimageitemdelegate.h"

namespace Ui {
class GalleryForm;
}


class GalleryForm : public QWidget
{
    Q_OBJECT

public:
    explicit GalleryForm(QWidget *parent = 0);
    ~GalleryForm();

    void AddImage(int index, QByteArray &rawImage);
    void SetModel(QAbstractItemModel *model);

private slots:
    void OnItemSelected(GalleryItem *item);
    void on_buttonDelete_clicked();
    void on_buttonConvertToTask_clicked();

private:
    Ui::GalleryForm *ui;
    QList<GalleryItem*> galleryItems;
    GalleryItem *focusedItem;

signals:
    void OnItemDelete(int index);
    void OnItemConvert(int index);
};
#endif // GALLERYFORM_H
