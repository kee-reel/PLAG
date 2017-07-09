#include "pluginhandler.h"

QHash<QString, QList<PluginHandler*>> *PluginHandler::handlersWithReferencesNames = NULL;
QHash<QString, QList<PluginHandler*>> *PluginHandler::handlersWithSelfNames = NULL;

PluginHandler::PluginHandler(PluginInfo<IDataSourcePlugin> *dataSource)
{
    unionType = DATASOURCE;
    pluginInfo.dataSource = dataSource;
    InsertIntoHashes();
}

PluginHandler::PluginHandler(PluginInfo<IDataManagerPlugin> *dataManager)
{
    unionType = DATAMANAGER;
    pluginInfo.dataManager = dataManager;
    InsertIntoHashes();
}

PluginHandler::PluginHandler(PluginInfo<IModelPlugin> *model)
{
    unionType = PLUGINMODEL;
    pluginInfo.model = model;
    InsertIntoHashes();
}

PluginHandler::PluginHandler(PluginInfo<IViewPlugin> *view)
{
    unionType = PLUGINVIEW;
    pluginInfo.view = view;
    InsertIntoHashes();
}

void PluginHandler::Init(QHash<QString, QList<PluginHandler *> > *handlersWithParentNames,
                         QHash<QString, QList<PluginHandler *> > *handlersWithSelfNames)
{
    PluginHandler::handlersWithReferencesNames = handlersWithParentNames;
    PluginHandler::handlersWithSelfNames = handlersWithSelfNames;
}

void PluginHandler::SetupRelations()
{
    auto name = pluginInfo.dataManager->meta->Name;
    if(handlersWithReferencesNames->contains(name))
    {
        auto referenceNamesList = handlersWithReferencesNames->value(name);
        for(int i = 0, size = referenceNamesList.size(); i < size; ++i)
            referenceNamesList.at(i)->pluginInfo.model->plugin->
                    AddReferencePlugin(pluginInfo.model->instance, pluginInfo.model->meta);
    }
}

void PluginHandler::InsertIntoHashes()
{
    auto name = pluginInfo.dataManager->meta->Name;
    auto relatedPluginNamesList = &(pluginInfo.dataSource->meta->RelatedPluginNames);
    auto selfNamesList = handlersWithSelfNames->value(name);
    auto referenceNamesList = handlersWithReferencesNames->value(name);

    selfNamesList.append(this);
    for(int i = 0, size = relatedPluginNamesList->size(); i < size; ++i)
        referenceNamesList.append(this);
}
