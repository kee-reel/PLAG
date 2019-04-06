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

#include "../../Interfaces/itasksketchmodel.h"
#include "mainform.h"
#include "paintwidget.h"

//! \defgroup TaskSketchView
//!     \ingroup MainMenuPlugin_rel_v
//! \defgroup TaskSketchView_imp Implementation
//!     \ingroup TaskSketchView

//! \addtogroup TaskSketchView_imp
//! \{
class TaskSketchView : public PluginBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IPlugin)

public:
    TaskSketchView(QWidget *parent = nullptr);
    virtual ~TaskSketchView() override;

private:
    ITaskSketchModel *myModel;
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
//! \}
#endif // TASKSKETCHVIEW_H
