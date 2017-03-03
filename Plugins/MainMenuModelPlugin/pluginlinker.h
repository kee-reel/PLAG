#ifndef PLUGINLINKER_H
#define PLUGINLINKER_H

#include "mainmenumodelplugin.h"

class PluginLinker
{
public:
    PluginLinker();

    void SetDataSourceLinks(IDataSourcePlugin* plugin, MetaInfo *meta);
    void SetDataManagerLinks(IDataManagerPlugin* plugin, MetaInfo *meta);
    void SetPluginModelLinks(IModelPlugin* plugin, MetaInfo *meta);
    void SetPluginViewLinks(IViewPlugin* plugin, MetaInfo *meta);

    void SetupLinks();

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
    QHash<QString, LinkInfo<IDataManagerPlugin>>    dataManagersLinkInfo;
    QHash<QString, LinkInfo<IModelPlugin>>          modelsLinkInfo;
    QHash<QString, LinkInfo<IViewPlugin>>           viewsLinkInfo;
};

#endif // PLUGINLINKER_H
