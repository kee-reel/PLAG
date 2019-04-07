#ifndef POMODOROVIEW_H
#define POMODOROVIEW_H

#include <QApplication>
#include <QDebug>
#include <QLayout>
#include <QWidget>

#include "../../Common/plugin_base.h"

#include "../../Interfaces/ipomodoromanager.h"
#include "pomodorobutton.h"
#include "mytreeview.h"
#include "designproxymodel.h"

//! \addtogroup PomodoroManager_dep
//!  \{
class PomodoroManagerView : public PluginBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IPlugin)

public:
    explicit PomodoroManagerView(QWidget *parent = nullptr);
    virtual ~PomodoroManagerView() override;

    // PluginBase interface
public:
    virtual void onAllReferencesSet() override;
    virtual void onAllReferencesReady() override;

private:
    IPomodoroManager *myModel;
    QAbstractItemModel *proxyModel;

    QModelIndex currentTask;
    IPomodoroManager::WorkSetup workSetup;

    void UpdateSelectedTask();

private slots:
    void PomodoroFinished();
    void on_buttonProjects_clicked();
    void on_buttonEdit_clicked();

    // QWidget interface
    void on_buttonDelete_clicked();

    void on_buttonAdd_clicked();
    void on_buttonExit_clicked();
    void on_treeView_pressed(const QModelIndex &index);

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event) override;
};
//!  \}
#endif // TASKLISTVIEW_H
