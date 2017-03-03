#include "pluginlinker.h"

PluginLinker::PluginLinker()
{

}

void PluginLinker::LinkSourceToManagers()
{
    // Search for related DataSources
    qDebug() << "=====Linking" << dataSourceMap.count() << " IDataSources";
    QHash<QString, QVector<IDataManagerPlugin*>>::Iterator dataSourceIter = sourceToManagersLink.begin();
    while(dataSourceIter != sourceToManagersLink.end())
    {
        qDebug() << "Linking DataSource " << dataSourceIter.key();
        QObject* dataSource = dataSourcesLinkInfo[dataSourceIter.key()].instance;
        QVector<IDataManagerPlugin*> childDataManagers = dataSourceIter.value();
        for(int i = 0; i < childDataManagers.count(); i++)
        {
            childDataManagers[i]->SetDataSource(dataSource);
            qDebug() << dataSourceIter.key() <<
                        "linked with" << dataManagerMap[childDataManagers[i]]->Name;
        }
        ++dataSourceIter;
    }
}

void PluginLinker::LinkManagerToModels()
{
    qDebug() << "=====Linking" << dataManagerMap.count() << "IDataManagers";
    // Search for related DataManagers
    QHash<QString, QVector<IModelPlugin*>>::Iterator dataManagerIter = managerToModelsLink.begin();
    while(dataManagerIter != managerToModelsLink.end())
    {
        QVector<IModelPlugin*> childPlugins = dataManagerIter.value();
        QObject* dataManager = dataManagersLinkInfo[dataManagerIter.key()].instance;
        for(int i = 0; i < childPlugins.count(); i++)
        {
            childPlugins[i]->AddDataManager(dataManager);
            qDebug() << pluginModelMap[childPlugins[i]]->Name << "linked with"
                     << dataManagerIter.key();
        }
        ++dataManagerIter;
    }
}

void PluginLinker::LinkModelToModels()
{
    qDebug() << "=====Linking" << pluginModelMap.count() << "IPluginModels";
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
    qDebug() << "=====Linking" << pluginViewMap.count() << "IPluginViews";
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

void PluginLinker::SetDataSourceLinks(IDataSourcePlugin *plugin, MetaInfo *meta)
{
    dataSourcesLinkInfo[meta->Name] = plugin;
    plugin->Setup();
}

void PluginLinker::SetDataManagerLinks(IDataManagerPlugin *plugin, MetaInfo *meta)
{
    dataManagersLinkInfo[meta->Name] = plugin;

    if(meta->ParentPluginName != "")
        sourceToManagersLink[meta->ParentPluginName].append(plugin);
}

void PluginLinker::SetPluginModelLinks(IModelPlugin *plugin, MetaInfo *meta)
{

    if(meta->Type == ROOTMODEL)
    {
        modelsLinkInfo[""] = plugin;
    }
    else
    {
        modelToModelsLink[meta->ParentPluginName].append(plugin);
        modelsLinkInfo[meta->Name] = plugin;
    }
    if(meta->DataManagerlName != "")
        managerToModelsLink[meta->DataManagerlName].append(plugin);
}

void PluginLinker::SetPluginViewLinks(IViewPlugin *plugin,MetaInfo *meta)
{
    viewsLinkInfo[meta->Name] = plugin;
    modelToViewsLink[meta->ParentPluginName].append(plugin);
}

void PluginLinker::SetupLinks()
{
    LinkSourceToManagers();
    LinkManagerToModels();
    LinkModelToModels();
    LinkModelToViews();
}
