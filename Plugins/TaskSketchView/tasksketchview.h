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
    PluginInfo *pluginInfo;

signals:
    void OnClose(PluginInfo*);
    void OnClose();

    // IPlugin interface
public:
    void SetPluginInfo(PluginInfo *pluginInfo) override;
    void OnAllSetup() override;
    QString GetLastError() override;
    void AddReferencePlugin(PluginInfo *pluginInfo) override;

public slots:
    void ReferencePluginClosed(PluginInfo *pluginInfo) override;

    // IViewPlugin interface
public slots:
    bool Open(IModelPlugin *model, QWidget *parent) override;
    bool Close() override;
};
//! \}
#endif // TASKSKETCHVIEW_H
