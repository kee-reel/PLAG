#include "pluginhandler.h"

QHash<QString, QList<PluginHandler*>> *PluginHandler::handlersWithReferencesNames = nullptr;
QHash<QString, QList<PluginHandler*>> *PluginHandler::handlersWithSelfNames = nullptr;

PluginHandler::PluginHandler(PluginInfo *pluginInfo)
{
    PluginHandler::pluginInfo = pluginInfo;
    pluginInfo->Plugin.any->SetPluginInfo(pluginInfo);
    InsertIntoHashes();
}

void PluginHandler::Init(QHash<QString, QList<PluginHandler *> > &handlersWithParentNames,
                         QHash<QString, QList<PluginHandler *> > &handlersWithSelfNames)
{
    PluginHandler::handlersWithReferencesNames = &handlersWithParentNames;
    PluginHandler::handlersWithSelfNames = &handlersWithSelfNames;
}

void PluginHandler::SetupRelations()
{
    auto interfaceName = pluginInfo->Meta->InterfaceName;
    if(interfaceName == "") return;
    qDebug() << "Setup references for" << interfaceName;
    if(handlersWithReferencesNames->contains(interfaceName))
    {
        auto referenceNamesList = &(*handlersWithReferencesNames)[interfaceName];
        for(int i = 0, size = referenceNamesList->size(); i < size; ++i)
        {
            qDebug() << "Set reference" << referenceNamesList->at(i)->pluginInfo->Meta->Name;
            referenceNamesList->at(i)->pluginInfo->Plugin.any->AddReferencePlugin(pluginInfo);
        }
    }
}

void PluginHandler::InsertIntoHashes()
{
    auto interfaceName = pluginInfo->Meta->InterfaceName;
    auto relatedPluginsInterfacesList = &(pluginInfo->Meta->RelatedPluginNames);
    for(int i = 0, size = relatedPluginsInterfacesList->size(); i < size; ++i)
    {
        auto list = &(*handlersWithReferencesNames)[relatedPluginsInterfacesList->at(i)];
        list->append(this);
    }

    if(interfaceName == "") return;
    auto selfNamesList = &(*handlersWithSelfNames)[interfaceName];
    selfNamesList->append(this);

}
