#ifndef TASKCALENDAR_H
#define TASKCALENDAR_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "../../PluginsCommon/plugin_base.h"

#include "../../PluginsInterfaces/itaskcalendar.h"
#include "../../PluginsInterfaces/iextendabledatamanager.h"
#include "../../PluginsInterfaces/itasktreemodel.h"

//! addtogroup TaskCalendar_imp
//! {
class TaskCalendar :
        public PluginBase,
        public ITaskCalendar
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IPlugin
        ITaskCalendar
    )

public:
    TaskCalendar();
    virtual ~TaskCalendar() override;

    // PluginBase interface
public:
    virtual void onAllReferencesSet() override;
    virtual void onAllReferencesReady() override;

    // ITaskCalendar interface
public:
    virtual void LinkEditorWidget(QWidget *) override;

private:
    IExtendableDataManager *dataManager;
    ITaskTreeModel *taskTree;
    QWidget* customDataWidget;
};
//! }
#endif // TASKCALENDAR_H
