#ifndef TASKLISTVIEW_H
#define TASKLISTVIEW_H

#include <QApplication>
#include <QDebug>
#include <QLayout>
#include <QAbstractProxyModel>

#include "../TaskSketchModel/itasksketchmodel.h"
#include "mainform.h"

class TaskListView : public QObject, IViewPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IViewPlugin)

public:
    TaskListView();
    ~TaskListView();

private:
    ITaskSketchModel *myModel;
    int myId;

    MainForm *mainForm;

    // IPlugin interface
public:
    void OnAllSetup() override;
    QString GetLastError() override;

    // IPluginView interface
public:
    void SetModel(QObject* model) override;
    bool Open(int id, QWidget* parent) override;
public slots:
    bool Close() override;
};

#endif // TASKLISTVIEW_H
