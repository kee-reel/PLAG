#ifndef TASKLISTVIEW_H
#define TASKLISTVIEW_H

#include <QApplication>
#include <QDebug>
#include <QLayout>

#include "../TaskListModel/itasktreemodel.h"
#include "mainform.h"

class TaskListView : public QObject, IViewPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IViewPlugin)

public:
    TaskListView();
    ~TaskListView();

    QAbstractItemModel *taskTree;

private:
    ITreeModel *myModel;
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
    bool Close() override;

private slots:
    void onClose();
};

#endif // TASKLISTVIEW_H
