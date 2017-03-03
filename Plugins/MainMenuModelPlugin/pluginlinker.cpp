#include "pluginlinker.h"

PluginLinker::PluginLinker()
{

}

void PluginLinker::LinkSourceToManagers()
{
    // Search for related DataSources
    qDebug() << "=====Linking" << sourceToManagersLink.count() << " IDataSources";
    QHash<QString, QVector<IDataManagerPlugin*>>::Iterator dataSourceIter = sourceToManagersLink.begin();
    while(dataSourceIter != sourceToManagersLink.end())
    {
        qDebug() << "Linking DataSource " << dataSourceIter.key();
        QObject* dataSource = dataSourcesLinkInfo[dataSourceIter.key()].instance;
        QVector<IDataManagerPlugin*> childDataManagers = dataSourceIter.value();
        for(int i = 0; i < childDataManagers.count(); i++)
            childDataManagers[i]->SetDataSource(dataSource);
        ++dataSourceIter;
    }
}

void PluginLinker::LinkManagerToModels()
{
    qDebug() << "=====Linking" << managerToModelsLink.count() << "IDataManagers";
    // Search for related DataManagers
    QHash<QString, QVector<IModelPlugin*>>::Iterator dataManagerIter = managerToModelsLink.begin();
    while(dataManagerIter != managerToModelsLink.end())
    {
        QVector<IModelPlugin*> childPlugins = dataManagerIter.value();
        QObject* dataManager = dataManagersLinkInfo[dataManagerIter.key()].instance;
        for(int i = 0; i < childPlugins.count(); i++)
            childPlugins[i]->AddDataManager(dataManager);
        ++dataManagerIter;
    }
}

void PluginLinker::LinkModelToModels()
{
    qDebug() << "=====Linking" << modelToModelsLink.count() << "IPluginModels";
    QHash<QString, QVector<IModelPlugin*>>::Iterator pluginModelIter = modelToModelsLink.begin();
    while(pluginModelIter != modelToModelsLink.end())
    {
        if(modelsLinkInfo.contains(pluginModelIter.key()))
        {
            IModelPlugin *parentModel = modelsLinkInfo[pluginModelIter.key()].plugin;
            QVector<IModelPlugin*> childPlugins = pluginModelIter.value();
            for(int i = 0; i < childPlugins.count(); i++)
            {
                MetaInfo* meta = pluginModelMap[childPlugins[i]];
                IModelPlugin* plugin = modelsLinkInfo[meta->Name].plugin;

                parentModel->AddChildModel(plugin, meta);
                qDebug() << "Child plugin" << meta->Name << "binds with" << meta->ParentPluginName;
            }
        }
        ++pluginModelIter;
    }
}

void PluginLinker::LinkModelToViews()
{
    qDebug() << "=====Linking" << modelToViewsLink.count() << "IPluginViews";
    QHash<QString, QVector<IViewPlugin*>>::Iterator pluginModelIter = modelToViewsLink.begin();
    while(pluginModelIter != modelToViewsLink.end())
    {
        if(modelsLinkInfo.contains(pluginModelIter.key()))
        {
            QVector<IViewPlugin*> childPlugins = pluginModelIter.value();
            IModelPlugin *parentModel = modelsLinkInfo[pluginModelIter.key()].plugin;
            for(int i = 0; i < childPlugins.count(); i++)
            {
                MetaInfo* meta = pluginViewMap[childPlugins[i]];
                IViewPlugin* plugin = viewsLinkInfo[meta->Name].plugin;

                parentModel->AddView(plugin, meta);
                qDebug() << "Child plugin" << meta->Name << "binds with" << meta->ParentPluginName;
            }
        }
        ++pluginModelIter;
    }
}

void PluginLinker::SetDataSourceLinks(IDataSourcePlugin *plugin, QObject* instance, MetaInfo *meta)
{
    LinkInfo<IDataSourcePlugin> info = {plugin, instance};
    dataSourcesLinkInfo[meta->Name] = info;
    plugin->Setup();
}

void PluginLinker::SetDataManagerLinks(IDataManagerPlugin *plugin, QObject* instance, MetaInfo *meta)
{
    LinkInfo<IDataManagerPlugin> info = {plugin, instance};
    dataManagersLinkInfo[meta->Name] = info;

    if(meta->ParentPluginName != "")
        sourceToManagersLink[meta->ParentPluginName].append(plugin);
}

void PluginLinker::SetPluginModelLinks(IModelPlugin *plugin, QObject* instance, MetaInfo *meta)
{
    LinkInfo<IModelPlugin> info = {plugin, instance};
    if(meta->Type == ROOTMODEL)
    {
        modelsLinkInfo[""] = info;
    }
    else
    {
        modelToModelsLink[meta->ParentPluginName].append(plugin);
        modelsLinkInfo[meta->Name] = info;
    }
    if(meta->DataManagerlName != "")
        managerToModelsLink[meta->DataManagerlName].append(plugin);
}

void PluginLinker::SetPluginViewLinks(IViewPlugin *plugin, QObject* instance, MetaInfo *meta)
{
    LinkInfo<IViewPlugin> info = {plugin, instance};
    viewsLinkInfo[meta->Name] = info;
    modelToViewsLink[meta->ParentPluginName].append(plugin);
}

void PluginLinker::SetupLinks()
{
    LinkSourceToManagers();
    LinkManagerToModels();
    LinkModelToModels();
    LinkModelToViews();
}
