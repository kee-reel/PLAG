#ifndef PLUGINLINKER_H
#define PLUGINLINKER_H

#include "mainmenumodelplugin.h"

class PluginLinker
{
public:
    PluginLinker();

    void SetDataSourceLinks(IDataSourcePlugin* plugin, QObject* instance, MetaInfo *meta);
    void SetDataManagerLinks(IDataManagerPlugin* plugin, QObject* instance, MetaInfo *meta);
    void SetPluginModelLinks(IModelPlugin* plugin, QObject* instance, MetaInfo *meta);
    void SetPluginViewLinks(IViewPlugin* plugin, QObject* instance, MetaInfo *meta);

    void SetupLinks();

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

private:
    void LinkSourceToManagers();
    void LinkManagerToModels();
    void LinkModelToModels();
    void LinkModelToViews();

    QHash<QString, QVector<IDataManagerPlugin*>> sourceToManagersLink;
    QHash<QString, QVector<IModelPlugin*>>       managerToModelsLink;
    QHash<QString, QVector<IModelPlugin*>>       modelToModelsLink;
    QHash<QString, QVector<IViewPlugin*>>        modelToViewsLink;

    template <class T>
    struct LinkInfo
    {
        T *plugin;
        QObject *instance;
    };
    QHash<QString, LinkInfo<IDataSourcePlugin>>  dataSourcesLinkInfo;
    QHash<QString, LinkInfo<IDataManagerPlugin>> dataManagersLinkInfo;
    QHash<QString, LinkInfo<IModelPlugin>>       modelsLinkInfo;
    QHash<QString, LinkInfo<IViewPlugin>>        viewsLinkInfo;
};

#endif // PLUGINLINKER_H
