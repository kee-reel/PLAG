#ifndef EMPTYMODULE_H
#define EMPTYMODULE_H

#include <QObject>
#include <QDebug>

#include "../TaskListModel/itasklistmodel.h"

class TaskListView : public QObject, IPluginView
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IPluginView)

public:
    TaskListView();
    ~TaskListView();

private:
    ITaskListModel* model;

    // IPluginView interface
public:
    virtual void SetModel(QObject* model);
    virtual bool Open(QWidget *parent);
    virtual bool Close();
};

#endif // EMPTYMODULE_H
