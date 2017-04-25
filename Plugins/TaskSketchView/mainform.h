#ifndef MAINFORM_H
#define MAINFORM_H

#include <QDebug>
#include <QWidget>
#include <QPainter>
#include <QAbstractItemModel>
#include <QAbstractProxyModel>
#include <QResizeEvent>
#include <QBuffer>

#include "../TaskSketchModel/itasksketchmodel.h"
#include "galleryform.h"

namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();
    void SetModel(ITaskSketchModel *model);

private:
    Ui::MainForm *ui;
    ITaskSketchModel *myModel;
    QAbstractItemModel *sketchModel;
    QAbstractItemModel *taskModel;
    GalleryForm *galleryForm;

    QString imageFormat;

    void resizeEvent(QResizeEvent *event);

signals:
    void onClose();
    void OnItemConvert(int index);

private slots:
    void OnItemDelete(int index);
    void OnItemConvertSlot(int index);

    void on_buttonClose_clicked();
    void on_buttonCreate_clicked();
    void on_buttonSave_clicked();
    void on_buttonOpenGallery_clicked();
};

#endif // MAINFORM_H
