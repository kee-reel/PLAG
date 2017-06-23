#ifndef TASKLISTVIEW_H
#define TASKLISTVIEW_H

#include <QApplication>
#include <QDebug>
#include <QLayout>
#include <QAbstractProxyModel>

#include "../TaskListModel/itasktreemodel.h"
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
    DesignProxyModel *proxyModel;
    QAbstractItemModel *taskTree;

    // IPlugin interface
public:
    void OnAllSetup() override;
    QString GetLastError() override;

    // IPluginView interface
public:
    void AddModel(QObject* model) override;
    bool Open(QWidget* parent) override;
public slots:
    bool Close() override;
    void OpenTaskEditor(int id);
};
//! \}
#endif // TASKLISTVIEW_H
