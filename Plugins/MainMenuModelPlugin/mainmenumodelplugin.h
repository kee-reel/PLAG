#ifndef MAINMENUMODULE_H
#define MAINMENUMODULE_H

#include <QObject>
#include <QDebug>

#include "imainmenumodule.h"
#include "../../System/TaskDBToolPlugin/itaskdbtoolplugin.h"

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
    QMap<IPluginView*, MetaInfo*> viewPlugins;
    IPluginView* activeView;

    QWidget* parent;

    // IPlugin interface
public:
    void AddChildPlugin(IPluginModel*, MetaInfo*) override;
    void SetDBTool(QObject*) override;
    void AddView(IPluginView *, MetaInfo *) override;

    bool Open(QWidget *parent) override;
    bool Close() override;

    QString GetError() override;

    // IMainMenuPluginModel interface
public:
    QList<MetaInfo *> GetChildPlugins() override;
    void RunPlugin(int pluginId) override;
};

#endif // MAINMENUMODULE_H
