#ifndef MAINMENUMODULE_H
#define MAINMENUMODULE_H

#include <QObject>
#include <QDebug>
#include <QApplication>

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
    IPluginModel *myParent;
    QWidget *myParentWidget;
    int myModelId;
    int activeViewId;
    int activeModelId;

    template <class T>
    struct PluginInfo
    {
        T *plugin;
        MetaInfo *meta;
    };

    QList< PluginInfo<IPluginModel> > childModelPlugins;
    QList< PluginInfo<IPluginView> > viewPlugins;

    // IPlugin interface
public:
    void AddChildPlugin(IPluginModel *, MetaInfo*) override;
    void SetDataManager(QObject*) override;
    void AddView(IPluginView *, MetaInfo *) override;

    bool Open(IPluginModel *myParent, QWidget *parentWidget, int id) override;
    bool Close() override;
    void ChildSelfClosed(int id) override;
    QString GetError() override;

    // IMainMenuPluginModel interface
public:
    QList<MetaInfo *> GetChildPlugins() override;
    void RunPlugin(int pluginId) override;
};

#endif // MAINMENUMODULE_H
