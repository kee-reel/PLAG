#ifndef MAINMENUMODULE_H
#define MAINMENUMODULE_H

#include <QObject>
#include <QDebug>

#include "imainmenumodule.h"
#include "itaskdbtoolplugin.h"

class MainMenuModelPlugin : public QObject, IMainMenuPluginModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IPluginModel IMainMenuPluginModel)

public:
    MainMenuModelPlugin();
    ~MainMenuModelPlugin();

private:
    QMap<IPluginModel*, MetaInfo*> childPlugins;
    ITaskDBToolPlugin* DBTool;

    // IPlugin interface
public:
    void DoSomething() override;
    void AddChildPlugin(IPluginModel*, MetaInfo*) override;
    void AddDBTool(QObject*) override;

    QString GetError() override;

    // IMainMenuPluginModel interface
public:
    virtual QStringList GetTasks();
};

#endif // MAINMENUMODULE_H
