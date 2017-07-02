#ifndef TASKSKETCHVIEW_H
#define TASKSKETCHVIEW_H

#include <QApplication>
#include <QDebug>
#include <QLayout>

#include "../TaskSketchModel/itasksketchmodel.h"
#include "mainform.h"

//! \defgroup TaskSketchView
//!     \ingroup MainMenuPlugin_rel_v
//! \defgroup TaskSketchView_imp Implementation
//!     \ingroup TaskSketchView

//! \addtogroup TaskSketchView_imp
//! \{
class TaskSketchView : public QObject, IViewPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IViewPlugin)

public:
    TaskSketchView();
    ~TaskSketchView();

private:
    ITaskSketchModel *myModel;

    MainForm *mainForm;

    // IPlugin interface
public:
    void OnAllSetup() override;
    QString GetLastError() override;

    // IPluginView interface
public:
    void AddModel(QObject* model) override;
    bool Open(IModelPlugin *model, QWidget *parent) override;
public slots:
    bool Close() override;
signals:
    void OnClose(IViewPlugin *pointer);
    void OnClose();
};
//! \}
#endif // TASKSKETCHVIEW_H
