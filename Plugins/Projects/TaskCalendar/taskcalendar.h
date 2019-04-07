#ifndef TASKCALENDAR_H
#define TASKCALENDAR_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "../../Common/plugin_base.h"

#include "../../Interfaces/itaskcalendar.h"
#include "../../Interfaces/iextendabledatamanager.h"
#include "../../Interfaces/iusertaskmanager.h"

//! \addtogroup TaskCalendar_imp
//!  \{
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
    IUserTaskManager *taskTree;
    QWidget* customDataWidget;
};
//!  \}
#endif // TASKCALENDAR_H
