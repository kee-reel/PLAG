#include "pluginlinker.h"

PluginLinker::PluginLinker()
{
    pluginTypesNames.insert("ROOTMODEL",    ROOTMODEL);
    pluginTypesNames.insert("PLUGINMODEL",  PLUGINMODEL);
    pluginTypesNames.insert("PLUGINVIEW",   PLUGINVIEW);
    pluginTypesNames.insert("DATASOURCE",   DATASOURCE);
    pluginTypesNames.insert("DATAMANAGER",  DATAMANAGER);
}

void PluginLinker::AddNewPlugin(QObject *instance, QJsonObject *meta)
{
    MetaInfo* pluginMeta = GetPluginMeta(meta);
    if(!pluginMeta) return;

    bool isBinded = BindPluginToSystem(instance, pluginMeta);
    if(!isBinded) return;
}

MetaInfo *PluginLinker::GetPluginMeta(QJsonObject *metaData)
{
    qDebug() << "Get meta";
    QString FieldName             = "Name";
    QString FieldModuleType       = "PluginType";
    QString FieldParentModuleName = "ParentName";
    QString FieldDataManagerName  = "DataManager";

    QJsonObject metaInfo = metaData->value("MetaData").toObject();
    // Check if all meta fields exists
    QStringList metaFieldsNames;
    metaFieldsNames << FieldName << FieldModuleType << FieldParentModuleName;
    foreach (QString metaFieldName, metaFieldsNames) {
        if(!metaInfo.contains(metaFieldName))
        {
            qDebug() << "Meta has no field:" << metaFieldName << "But has fields:";
            for(QJsonObject::Iterator i = metaInfo.begin(); i != metaInfo.end(); ++i)
                qDebug() << i.key() << " = " << i.value();
            return NULL;
        }
    }

    MetaInfo* newMetaInfo = new MetaInfo();
    // Set module name
    newMetaInfo->Name = metaInfo.value(FieldName).toString();
    if(newMetaInfo->Name == "")
    {
        qDebug() << "Meta error: field" << FieldName << "is empty";
        delete newMetaInfo;
        return NULL;
    }
    qDebug() << "Name:" << newMetaInfo->Name;

    // Set module type
    QString moduleTypeStr = metaInfo.value(FieldModuleType).toString().toUpper();
    if(!pluginTypesNames.contains(moduleTypeStr))
    {
        qDebug() << "Meta error: field" << FieldModuleType << "value is incorrect -" << moduleTypeStr;
        delete newMetaInfo;
        return NULL;
    }
    newMetaInfo->Type = pluginTypesNames[moduleTypeStr];
    qDebug() << "Type:" << moduleTypeStr;

    // Set DBTool name
    newMetaInfo->DataManagerName = metaInfo.value(FieldDataManagerName).toString();
    qDebug() << "DataManager:" << newMetaInfo->DataManagerName;

    // Set module parent name
    newMetaInfo->ParentPluginName = metaInfo.value(FieldParentModuleName).toString();
    qDebug() << "Parent:" << newMetaInfo->ParentPluginName;
    return newMetaInfo;
}

bool PluginLinker::BindPluginToSystem(QObject *instance, MetaInfo *meta)
{
    qDebug() << "Bind plugin to system";
    switch (meta->Type) {
        case ROOTMODEL:
        case PLUGINMODEL:{
            IModelPlugin* plugin = CastToPlugin<IModelPlugin>(instance);
            if(!plugin) return false;
            SetLinks(plugin, instance, meta);
            break;
        }

        case PLUGINVIEW:{
            IViewPlugin* plugin = CastToPlugin<IViewPlugin>(instance);
            if(!plugin) return false;
            viewMap.insert(plugin, meta);
            SetLinks(plugin, instance, meta);
            break;
        }

        case DATASOURCE:{
            IDataSourcePlugin* plugin = CastToPlugin<IDataSourcePlugin>(instance);
            if(!plugin) return false;
            sourceMap.insert(plugin, meta);
            SetLinks(plugin, instance, meta);
            break;
        }

        case DATAMANAGER:{
            IDataManagerPlugin* plugin = CastToPlugin<IDataManagerPlugin>(instance);
            if(!plugin) return false;
            managerMap.insert(plugin, meta);
            SetLinks(plugin, instance, meta);
            break;
        }

        default:{
            return false;
            break;
        }

    }

    qDebug() << "Module" << meta->Name << "succesfully added to system." << endl;
    return true;
}

void PluginLinker::CallOnAllSetup()
{
    QList<IDataSourcePlugin*> sources = sourceMap.keys();
    for(int i = 0; i < sources.length(); ++i)
        sources[i]->OnAllSetup();
    QList<IDataManagerPlugin*> managers = managerMap.keys();
    for(int i = 0; i < managers.length(); ++i)
        managers[i]->OnAllSetup();
    QList<IModelPlugin*> models = modelMap.keys();
    for(int i = 0; i < models.length(); ++i)
        models[i]->OnAllSetup();
    QList<IViewPlugin*> views = viewMap.keys();
    for(int i = 0; i < views.length(); ++i)
        views[i]->OnAllSetup();
}

template<class Type>
Type *PluginLinker::CastToPlugin(QObject *possiblePlugin)
{
    Type* plugin = qobject_cast<Type*>(possiblePlugin);
    if(!plugin)
    {
        qDebug() << "Can't load the plugin " << possiblePlugin->objectName() << ": not QObject.";
    }
    return plugin;
}


void PluginLinker::SetLinks(IDataSourcePlugin *plugin, QObject* instance, MetaInfo *meta)
{
    LinkInfo<IDataSourcePlugin> info = {plugin, instance};
    dataSourcesLinkInfo[meta->Name] = info;
    plugin->Setup();
}

void PluginLinker::SetLinks(IDataManagerPlugin *plugin, QObject* instance, MetaInfo *meta)
{
    LinkInfo<IDataManagerPlugin> info = {plugin, instance};
    dataManagersLinkInfo[meta->Name] = info;

    if(meta->ParentPluginName != "")
        sourceToManagersLink[meta->ParentPluginName].append(plugin);
}

void PluginLinker::SetLinks(IModelPlugin *plugin, QObject* instance, MetaInfo *meta)
{
    modelMap.insert(plugin, meta);
    LinkInfo<IModelPlugin> info = {plugin, instance};

    IMainMenuPluginModel::MenuItem *item = new IMainMenuPluginModel::MenuItem();
    item->meta = meta;
    menuItems.insert(meta, item);

    if(meta->Type == ROOTMODEL)
    {
        modelsLinkInfo[""] = info;
        rootModel = plugin;
        rootMenuItem = menuItems[meta];
    }
    else
        modelToModelsLink[meta->ParentPluginName].append(plugin);
    modelsLinkInfo[meta->Name] = info;

    if(meta->DataManagerName != "")
        managerToModelsLink[meta->DataManagerName].append(plugin);
}

void PluginLinker::SetLinks(IViewPlugin *plugin, QObject* instance, MetaInfo *meta)
{
    qDebug() << "View";
    LinkInfo<IViewPlugin> info = {plugin, instance};
    viewsLinkInfo[meta->Name] = info;
    modelToViewsLink[meta->ParentPluginName].append(plugin);
}

IMainMenuPluginModel::MenuItem* PluginLinker::SetupLinks()
{
    LinkSourceToManagers();
    LinkManagerToModels();
    LinkModelToModels();
    LinkModelToViews();
    CallOnAllSetup();
    qDebug() << "DONE";
    return rootMenuItem;
}

void PluginLinker::LinkSourceToManagers()
{
    // Search for related DataSources
    qDebug() << "=====Linking" << sourceToManagersLink.count() << " IDataSources";
    QHash<QString, QVector<IDataManagerPlugin*> >::Iterator dataSourceIter = sourceToManagersLink.begin();
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
    QHash<QString, QVector<IModelPlugin*> >::Iterator dataManagerIter = managerToModelsLink.begin();
    while(dataManagerIter != managerToModelsLink.end())
    {
        if(dataManagersLinkInfo.contains(dataManagerIter.key()))
        {
            QObject* dataManager = dataManagersLinkInfo[dataManagerIter.key()].instance;
            QVector<IModelPlugin*> childPlugins = dataManagerIter.value();
            for(int i = 0; i < childPlugins.count(); i++)
                childPlugins[i]->AddDataManager(dataManager);
        }
        ++dataManagerIter;
    }
}

void PluginLinker::LinkModelToModels()
{
    qDebug() << "=====Linking" << modelToModelsLink.count() << "IPluginModels";
    QHash<QString, QVector<IModelPlugin*> >::Iterator pluginModelIter = modelToModelsLink.begin();
    while(pluginModelIter != modelToModelsLink.end())
    {
        if(modelsLinkInfo.contains(pluginModelIter.key()))
        {
            LinkInfo<IModelPlugin> *parentModel = &modelsLinkInfo[pluginModelIter.key()];
            MetaInfo *parentMeta = modelMap[parentModel->plugin];
            QVector<IModelPlugin*> childPlugins = pluginModelIter.value();
            for(int i = 0; i < childPlugins.count(); i++)
            {
                MetaInfo* meta = modelMap[childPlugins[i]];
                IModelPlugin* plugin = modelsLinkInfo[meta->Name].plugin;

                parentModel->plugin->AddChildModel(plugin, meta);
                plugin->AddParentModel(parentModel->instance, parentMeta);
                menuItems[parentMeta]->SubItems.append(menuItems[meta]);
                qDebug() << "Child plugin" << meta->Name << "binds with" << meta->ParentPluginName;
            }
        }
        ++pluginModelIter;
    }
}

void PluginLinker::LinkModelToViews()
{
    qDebug() << "=====Linking" << modelToViewsLink.count() << "IPluginViews" << modelsLinkInfo.count();
    QHash<QString, QVector<IViewPlugin*> >::Iterator pluginModelIter = modelToViewsLink.begin();
    while(pluginModelIter != modelToViewsLink.end())
    {
        qDebug() << "?" << pluginModelIter.key();
        if(modelsLinkInfo.contains(pluginModelIter.key()))
        {
            qDebug() << "+" << pluginModelIter.key();
            QVector<IViewPlugin*> childPlugins = pluginModelIter.value();
            LinkInfo<IModelPlugin> parentModel = modelsLinkInfo.value(pluginModelIter.key());
            MetaInfo *parentMeta = modelMap[parentModel.plugin];
            for(int i = 0; i < childPlugins.count(); i++)
            {
                MetaInfo* meta = viewMap[childPlugins[i]];
                IViewPlugin* plugin = viewsLinkInfo[meta->Name].plugin;

                parentModel.plugin->AddView(plugin, meta);
                plugin->SetModel(parentModel.instance);
                menuItems[parentMeta]->ViewItems.append(meta);
                qDebug() << "Child plugin" << meta->Name << "binds with" << meta->ParentPluginName;
            }
        }
        ++pluginModelIter;
    }
}
