#ifndef EMPTYMODULE_H
#define EMPTYMODULE_H

#include <QObject>
#include <QDebug>

#include "../TaskListModel/itasktreemodel.h"
#include "mainform.h"

class TaskListView : public QObject, IPluginView
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IPluginView)

public:
    TaskListView();
    ~TaskListView();

    QAbstractItemModel *taskTree;

private:
    ITaskTreeModel *myModel;
    int myId;
    MainForm *mainForm;

    // IPluginView interface
public:
    virtual void SetModel(QObject* model);
    virtual bool Open(int id, QWidget* parent);
    virtual bool Close();

private slots:
    void onClose();
};

#endif // EMPTYMODULE_H
