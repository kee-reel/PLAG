#ifndef MAINFORM_H
#define MAINFORM_H

#include <QDebug>
#include <QWidget>
#include <QPainter>
#include <QAbstractItemModel>
#include <QAbstractProxyModel>
#include <QResizeEvent>

#include "../TaskSketchModel/itasksketchmodel.h"
#include "galleryform.h"

namespace Ui {
class MainForm;
}
//! \addtogroup TaskSketchView_imp
//! \{
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
    void on_buttonClear_clicked();
    void on_buttonSave_clicked();
    void on_buttonOpenGallery_clicked();
    void on_buttonClose_clicked();
};
//! \}
#endif // MAINFORM_H
