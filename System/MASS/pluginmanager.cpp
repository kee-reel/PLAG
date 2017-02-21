#include "pluginmanager.h"

PluginManager::PluginManager(QWidget* parent) : QObject(parent)
{
    this->parent = parent;
    mainPlugin = NULL;

    pluginTypesNames.insert("ROOTMODEL",    ROOTMODEL);
    pluginTypesNames.insert("PLUGINMODEL",  PLUGINMODEL);
    pluginTypesNames.insert("PLUGINVIEW",   PLUGINVIEW);
    pluginTypesNames.insert("DATASOURCE",   DATASOURCE);
    pluginTypesNames.insert("DATAMANAGER",  DATAMANAGER);
}

PluginManager::~PluginManager()
{
    for(QMap<IPluginModel*, MetaInfo*>::Iterator i = pluginModelMap.begin(); i != pluginModelMap.end(); ++i)
    {
        delete i.value();
        delete i.key();
    }

    for(QMap<IDataSourcePlugin*, MetaInfo*>::Iterator i = dataSourceMap.begin(); i != dataSourceMap.end(); ++i)
    {
        delete i.value();
        delete i.key();
    }
}

void PluginManager::LoadPluginsToHome()
{
    qDebug() << QDir::homePath() << "===" << QDir::rootPath() << "===" << QDir::currentPath() << "===" << QDir::tempPath();
    internalPluginsPath = QDir(QDir::currentPath() + "/Modules/");
    //TODO: DT entry
#ifdef Q_OS_ANDROID
    QDir storageDirectoryPath("/storage/emulated/0/Android/data/" + packageName);
    if(!internalPluginsPath.exists())
    {
        internalPluginsPath.mkdir(internalPluginsPath.absolutePath());
    }
    qDebug() << "Paths" << storageDirectoryPath.absolutePath() << internalPluginsPath;
//    foreach (QString file, storageDirectoryPath.entryList(QDir::AllEntries))
//    {
//        qDebug() << file;
//    }

    QFile fileToCopy;
    QFile existingFile;
    foreach (QString file, storageDirectoryPath.entryList(QDir::Files))
    {
        // If internal file already exists - delete it
        existingFile.setFileName(internalPluginsPath.absolutePath() + "/" + file);
        if(existingFile.exists())
        {
            existingFile.remove();
        }

        // Copy storage file to internal storage
        QDir storagePluginPath(storageDirectoryPath.absolutePath() + "/" + file);
        fileToCopy.setFileName(storagePluginPath.absolutePath());
        fileToCopy.open(QIODevice::ReadOnly);
        fileToCopy.copy(internalPluginsPath.absolutePath() + "/" + file);
        fileToCopy.close();
        qDebug() << fileToCopy.remove();
        qDebug() << storagePluginPath.absolutePath() << fileToCopy.isOpen() << fileToCopy.errorString();
        qDebug() << internalPluginsPath.absolutePath() + file << fileToCopy.errorString();
        fileToCopy.close();
    }

    QApplication::addLibraryPath(internalPluginsPath.absolutePath());

    QDir path(internalPluginsPath);
    qDebug() << "Path" << path.absolutePath();
    foreach (QString file, path.entryList(QDir::Files))
    {
        qDebug() << file;
    }
#endif
}

void PluginManager::SetupPlugins()
{
    LoadPluginsToHome();

    QDir libsDir(internalPluginsPath);
    qDebug() << "Path" << libsDir.absolutePath();
    foreach (QString file, libsDir.entryList(QDir::Files))
    {
        SetupPlugin(libsDir.absolutePath() + "/" + file);
    }
    SetupPluginsConnections();
    qDebug() << "Everything done." << endl;
}

bool PluginManager::SetupPlugin(QString pluginName)
{
    qDebug() << endl << "=====" << pluginName << "=====";
    QPluginLoader* loader = LoadPlugin(pluginName);
    if(!loader) return false;

    MetaInfo* pluginType = GetPluginMeta(loader);
    if(!pluginType) return false;

    QObject* possiblePlugin = GetPluginInstance(loader);
    if(!possiblePlugin) return false;

    bool isBinded = BindPluginToSystem(loader, possiblePlugin, pluginType);
    if(!isBinded) return false;
    return true;
}

QPluginLoader *PluginManager::LoadPlugin(QString pluginName)
{
    qDebug() << "Load plugin";
    if(!QLibrary::isLibrary(pluginName))
    {
        qDebug() << "Can't load the plugin" << pluginName << ": not a library file.";
        return NULL;
    }
    QPluginLoader* loader = new QPluginLoader(pluginName);
    if(!loader)
    {
        qDebug() << "Load null.";
    }
    return loader;
}

QObject* PluginManager::GetPluginInstance(QPluginLoader* loader)
{
    qDebug() << "Get instance";
    QObject* possiblePlugin = loader->instance();
    if(!possiblePlugin)
    {
        qDebug() << "Can't load the plugin" << loader->fileName() << ": not a plugin."
                 << "Error:" + loader->errorString();
    }
    return possiblePlugin;
}

MetaInfo* PluginManager::GetPluginMeta(QPluginLoader* loader)
{
    qDebug() << "Get meta";
    const QString FieldName             = "Name";
    const QString FieldModuleType       = "PluginType";
    const QString FieldParentModuleName = "ParentName";
    const QString FieldDataManagerName  = "DataManager";
    QJsonObject metaData = loader->metaData()["MetaData"].toObject();

    // Check if all meta fields exists
    QStringList metaFieldsNames;
    metaFieldsNames << FieldName << FieldModuleType << FieldParentModuleName;
    foreach (QString metaFieldName, metaFieldsNames) {
        if(!metaData.contains(metaFieldName))
        {
            qDebug() << "Meta has no field:" << metaFieldName << "But has fields:";
            for(QJsonObject::Iterator i = metaData.begin(); i != metaData.end(); ++i)
                qDebug() << i.key() << " = " << i.value();
            return NULL;
        }
    }

    MetaInfo* newMetaInfo = new MetaInfo();

    // Set module name
    newMetaInfo->Name = metaData[FieldName].toString();
    if(newMetaInfo->Name == "")
    {
        qDebug() << "Meta error: field" << FieldName << "is empty";
        delete newMetaInfo;
        return NULL;
    }
    qDebug() << "Name:" << newMetaInfo->Name;

    // Set module type
    QString moduleTypeStr = metaData[FieldModuleType].toString().toUpper();
    if(!pluginTypesNames.contains(moduleTypeStr))
    {
        qDebug() << "Meta error: field" << FieldModuleType << "value is incorrect -" << moduleTypeStr;
        delete newMetaInfo;
        return NULL;
    }
    newMetaInfo->Type = pluginTypesNames[moduleTypeStr];
    qDebug() << "Type:" << moduleTypeStr;

    // Set DBTool name
    newMetaInfo->DataManagerlName = metaData[FieldDataManagerName].toString();
    qDebug() << "DataManager:" << newMetaInfo->DataManagerlName;

    // Set module parent name
    newMetaInfo->ParentPluginName = metaData[FieldParentModuleName].toString();
    qDebug() << "Parent:" << newMetaInfo->ParentPluginName;
    return newMetaInfo;
}

bool PluginManager::BindPluginToSystem(QPluginLoader* loader, QObject* instance, MetaInfo* meta)
{
    qDebug() << "Bind plugin to system";
    switch (meta->Type) {
        case ROOTMODEL:
        case PLUGINMODEL:{
            IPluginModel* plugin = CastToPlugin<IPluginModel>(loader, instance);
            if(!plugin) return false;
            SetPluginModelLinks(plugin, instance, meta);
            break;
        }

        case PLUGINVIEW:{
            IPluginView* plugin = CastToPlugin<IPluginView>(loader, instance);
            if(!plugin) return false;
            SetPluginViewLinks(plugin, instance, meta);
            break;
        }

        case DATASOURCE:{
            IDataSourcePlugin* plugin = CastToPlugin<IDataSourcePlugin>(loader, instance);
            if(!plugin) return false;
            SetDataSourceLinks(plugin, instance, meta);
            break;
        }

        case DATAMANAGER:{
            IDataManagerPlugin* plugin = CastToPlugin<IDataManagerPlugin>(loader, instance);
            if(!plugin) return false;
            SetDataManagerLinks(plugin, instance, meta);
            break;
        }

        default:{
            return false;
            break;
        }

    }

    qDebug() << "Module" << meta->Name << "succesfully added to system.";
    return true;
}

void PluginManager::SetupPluginsConnections()
{
    qDebug() << "Setup connections";

    LinkSourceToManagers();

    LinkManagerToModels();

    LinkModelToModels();

    LinkModelToViews();

    qDebug() << "-----Linking finished-----" << endl;

    if(mainPluginMap.count() == 1)
    {
        mainPlugin = mainPluginMap.begin().key();
        qDebug() << "Starting main plugin" << mainPluginMap.begin().value()->Name << endl;
        mainPlugin->Open(NULL, parent, 0);
    }
    else
    {
        qDebug() << "You have several main plugins.";
    }
}

void PluginManager::LinkSourceToManagers()
{
    // Setup DataSource
    if(dataSourceMap.count() == 1)
    {
        mainDataSource = dataSourceMap.begin().key();
        qDebug() << "Current database driver is" << dataSourceMap.begin().value()->Name << endl;
        mainDataSource->Setup();
    }
    else
    {
        qDebug() << "You have several database plugins.";
    }

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

void PluginManager::LinkManagerToModels()
{
    qDebug() << "=====Linking" << dataManagerMap.count() << "IDataManagers";
    // Search for related DataManagers
    QHash<QString, QVector<IPluginModel*>>::Iterator dataManagerIter = managerToModelsLink.begin();
    while(dataManagerIter != managerToModelsLink.end())
    {
        QVector<IPluginModel*> childPlugins = dataManagerIter.value();
        QObject* dataManager = dataManagersLinkInfo[dataManagerIter.key()].instance;
        for(int i = 0; i < childPlugins.count(); i++)
        {
            childPlugins[i]->SetDataManager(dataManager);
            qDebug() << pluginModelMap[childPlugins[i]]->Name << "linked with"
                     << dataManagerIter.key();
        }
        ++dataManagerIter;
    }
}

void PluginManager::LinkModelToModels()
{
    qDebug() << "=====Linking" << pluginModelMap.count() << "IPluginModels";
    QHash<QString, QVector<IPluginModel*>>::Iterator pluginModelIter = modelToModelsLink.begin();
    while(pluginModelIter != modelToModelsLink.end())
    {
        if(modelsLinkInfo.contains(pluginModelIter.key()))
        {
            IPluginModel *parentModel = modelsLinkInfo[pluginModelIter.key()].plugin;
            QVector<IPluginModel*> childPlugins = pluginModelIter.value();
            for(int i = 0; i < childPlugins.count(); i++)
            {
                MetaInfo* meta = pluginModelMap[childPlugins[i]];
                IPluginModel* plugin = modelsLinkInfo[meta->Name].plugin;

                parentModel->AddChildPlugin(plugin, meta);
                qDebug() << "Child plugin" << meta->Name << "binds with" << meta->ParentPluginName;
            }
        }
        ++pluginModelIter;
    }
}

void PluginManager::LinkModelToViews()
{
    qDebug() << "=====Linking" << pluginViewMap.count() << "IPluginViews";
    QHash<QString, QVector<IPluginView*>>::Iterator pluginModelIter = modelToViewsLink.begin();
    while(pluginModelIter != modelToViewsLink.end())
    {
        if(modelsLinkInfo.contains(pluginModelIter.key()))
        {
            QVector<IPluginView*> childPlugins = pluginModelIter.value();
            IPluginModel *parentModel = modelsLinkInfo[pluginModelIter.key()].plugin;
            for(int i = 0; i < childPlugins.count(); i++)
            {
                MetaInfo* meta = pluginViewMap[childPlugins[i]];
                IPluginView* plugin = viewsLinkInfo[meta->Name].plugin;

                parentModel->AddView(plugin, meta);
                qDebug() << "Child plugin" << meta->Name << "binds with" << meta->ParentPluginName;
            }
        }
        ++pluginModelIter;
    }
}

void PluginManager::SetDataSourceLinks(IDataSourcePlugin *plugin, QObject *instance, MetaInfo *meta)
{
    dataSourceMap.insert(plugin, meta);
    LinkInfo<IDataSourcePlugin> info = {plugin, instance};
    dataSourcesLinkInfo[meta->Name] = info;
}

void PluginManager::SetDataManagerLinks(IDataManagerPlugin *plugin, QObject *instance, MetaInfo *meta)
{
    dataManagerMap.insert(plugin, meta);
    LinkInfo<IDataManagerPlugin> info = {plugin, instance};
    dataManagersLinkInfo[meta->Name] = info;

    if(meta->ParentPluginName != "")
        sourceToManagersLink[meta->ParentPluginName].append(plugin);
}

void PluginManager::SetPluginModelLinks(IPluginModel *plugin, QObject* instance, MetaInfo *meta)
{
    pluginModelMap.insert(plugin, meta);
    LinkInfo<IPluginModel> info = {plugin, instance};

    if(meta->Type == ROOTMODEL)
    {
        mainPluginMap.insert(plugin, meta);
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

void PluginManager::SetPluginViewLinks(IPluginView *plugin, QObject *instance, MetaInfo *meta)
{
    pluginViewMap.insert(plugin, meta);
    LinkInfo<IPluginView> info = {plugin, instance};
    viewsLinkInfo[meta->Name] = info;
    modelToViewsLink[meta->ParentPluginName].append(plugin);
}

template <class Type>
Type *PluginManager::CastToPlugin(QPluginLoader* loader, QObject* possiblePlugin)
{
    Type* plugin = qobject_cast<Type*>(possiblePlugin);
    if(!plugin)
    {
        qDebug() << "Can't load the plugin " << possiblePlugin->objectName() << ": not QObject.";
    }
    return plugin;
}

//QFile file(QDir::currentPath() + "/out.txt");
//file.open(QIODevice::WriteOnly | QIODevice::Text);
//if(!file.isOpen())
//{
//    qDebug() << file.errorString();
//}
//else
//{
//    QTextStream out(&file);
//    out << "This file is generated by Qt\n";
//    // optional, as QFile destructor will already do it:
//    file.close();
//}
