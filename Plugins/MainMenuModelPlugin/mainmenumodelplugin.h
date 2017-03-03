#ifndef MAINMENUMODULE_H
#define MAINMENUMODULE_H

#include <QObject>
#include <QDebug>
#include <QApplication>

#include "imainmenumodule.h"
#include "../../System/ExtendableDataBaseManager/iextendabledatabasemanagerplugin.h"

class MainMenuModelPlugin : public QObject, IMainMenuPluginModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IModelPlugin IRootModelPlugin IMainMenuPluginModel)

public:
    MainMenuModelPlugin();
    ~MainMenuModelPlugin();

    void OnAllSetup() override;
    QString GetLastError() override;

    void AddDataSource(IDataSourcePlugin *model, MetaInfo *meta) override;
    void AddDataManager(IDataManagerPlugin *model, MetaInfo *meta) override;
    void AddChildModel(IModelPlugin *model, MetaInfo *meta) override;
    void AddView(IViewPlugin *, MetaInfo *) override;

    bool Open(IModelPlugin *myParent, QWidget *parentWidget, int id) override;
    bool Close() override;
    void ChildSelfClosed(int id) override;

    QList<MetaInfo *> GetChildPlugins() override;
    void RunPlugin(int pluginId) override;

private:

    IModelPlugin *myParent;
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

    QMap<IModelPlugin*, MetaInfo*>          modelMap;
    QMap<IViewPlugin*, MetaInfo*>           viewMap;
    QMap<IDataSourcePlugin*, MetaInfo*>     dataSourceMap;
    QMap<IDataManagerPlugin*, MetaInfo*>    dataManagerMap;
};

#endif // MAINMENUMODULE_H
