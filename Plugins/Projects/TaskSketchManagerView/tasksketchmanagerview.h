#ifndef TASKSKETCHVIEW_H
#define TASKSKETCHVIEW_H

#include <QApplication>
#include <QDebug>
#include <QLayout>
#include <QAbstractProxyModel>
#include <QPainter>
#include <QAbstractItemModel>
#include <QResizeEvent>

#include "../../Common/plugin_base.h"

#include "../../Interfaces/itasksketchmanager.h"
#include "paintwidget.h"
#include "galleryform.h"

//! \addtogroup TaskSketchManager_dep
//!  \{
class TaskSketchManagerView : public PluginBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IPlugin)

public:
    TaskSketchManagerView(QWidget *parent = nullptr);
    virtual ~TaskSketchManagerView() override;

private:
    ITaskSketchManager *myModel;
    PaintWidget *paintWidgetTypeEditor;

    QAbstractItemModel *sketchModel;
    QAbstractItemModel *taskModel;
    GalleryForm *galleryForm;

    QString imageFormat;

    virtual void resizeEvent(QResizeEvent *event) override;

signals:
    void OnItemConvert(int index);

private slots:
    void OnItemDelete(int index);
    void OnItemConvertSlot(int index);
    void on_buttonClear_clicked();
    void on_buttonSave_clicked();
    void on_buttonOpenGallery_clicked();
    void on_buttonClose_clicked();

    // PluginBase interface
protected:
    virtual void onAllReferencesSet() override;
    virtual void onAllReferencesReady() override;
};
//!  \}
#endif // TASKSKETCHVIEW_H
