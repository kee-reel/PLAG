#ifndef TASKLISTVIEW_H
#define TASKLISTVIEW_H

#include <QApplication>
#include <QDebug>
#include <QLayout>
#include <QAbstractProxyModel>

#include "../../Models/TaskListModel/itasktreemodel.h"
#include "designproxymodel.h"
#include "mainform.h"

//! \defgroup TaskListView
//!     \ingroup MainMenuPlugin_rel_v
//! \defgroup TaskListView_imp Implementation
//!     \ingroup TaskListView

//! \addtogroup TaskListView_imp
//! \{
class TaskListView : public QObject, IViewPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IViewPlugin)

public:
    TaskListView();
    ~TaskListView();

private:
    ITaskTreeModel *myModel;

    MainForm *mainForm;
    QIdentityProxyModel *proxyModel;
    QAbstractItemModel *taskTree;
    PluginInfo *pluginInfo;

    // IPlugin interface
public:
    void SetPluginInfo(PluginInfo *pluginInfo) override;
    void OnAllSetup() override;
    QString GetLastError() override;
    void AddReferencePlugin(PluginInfo *pluginInfo) override;
public slots:
    void ReferencePluginClosed(PluginInfo *pluginInfo) override;

    // IPluginView interface
public:
    bool Open(IModelPlugin *model) override;
public slots:
    bool Close() override;

public slots:
    void OpenTaskEditor(int id);
signals:
    void OnOpen(QWidget *);
    void OnClose(PluginInfo *pointer);
    void OnClose();
};
//! \}
#endif // TASKLISTVIEW_H
