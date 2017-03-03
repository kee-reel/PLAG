#include "pluginloader.h"

PluginLoader::PluginLoader(QWidget* parent) : QObject(parent)
{
    this->parent = parent;
    rootModel = NULL;

    pluginTypesNames.insert("ROOTMODEL",    ROOTMODEL);
    pluginTypesNames.insert("PLUGINMODEL",  PLUGINMODEL);
    pluginTypesNames.insert("PLUGINVIEW",   PLUGINVIEW);
    pluginTypesNames.insert("DATASOURCE",   DATASOURCE);
    pluginTypesNames.insert("DATAMANAGER",  DATAMANAGER);
}

PluginLoader::~PluginLoader()
{
    for(QMap<IModelPlugin*, MetaInfo*>::Iterator i = pluginModelMap.begin(); i != pluginModelMap.end(); ++i)
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

void PluginLoader::LoadPluginsToHome()
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

void PluginLoader::SetupPlugins()
{
    LoadPluginsToHome();

    QDir libsDir(internalPluginsPath);
    qDebug() << "Path" << libsDir.absolutePath();
    QApplication::addLibraryPath(internalPluginsPath.absolutePath());
    foreach (QString file, libsDir.entryList(QDir::Files))
    {
        SetupPlugin(libsDir.absolutePath() + "/" + file);
    }
    SetupPluginsConnections();
    qDebug() << "Everything done." << endl;
}

bool PluginLoader::SetupPlugin(QString pluginName)
{
    qDebug() << endl << "=====" << pluginName << "=====";
    QPluginLoader* loader = LoadPlugin(pluginName);
    if(!loader) return false;

    MetaInfo* pluginMeta = GetPluginMeta(loader);
    if(!pluginMeta) return false;

    QObject* possiblePlugin = GetPluginInstance(loader);
    if(!possiblePlugin) return false;

    bool isBinded = BindPluginToSystem(possiblePlugin, pluginMeta);
    if(!isBinded) return false;
    return true;
}

QPluginLoader *PluginLoader::LoadPlugin(QString pluginName)
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

QObject* PluginLoader::GetPluginInstance(QPluginLoader* loader)
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

MetaInfo* PluginLoader::GetPluginMeta(QPluginLoader* loader)
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

bool PluginLoader::BindPluginToSystem(QObject* instance, MetaInfo* meta)
{
    qDebug() << "Bind plugin to system";
    switch (meta->Type) {
        case ROOTMODEL:{
            IRootModelPlugin* plugin = CastToPlugin<IRootModelPlugin>(instance);
            if(!plugin) return false;
            rootModelMap.insert(plugin, meta);
            break;
        }

        case PLUGINMODEL:{
            IModelPlugin* plugin = CastToPlugin<IModelPlugin>(instance);
            if(!plugin) return false;
            pluginModelMap.insert(plugin, meta);
            break;
        }

        case PLUGINVIEW:{
            IViewPlugin* plugin = CastToPlugin<IViewPlugin>(instance);
            if(!plugin) return false;
            pluginViewMap.insert(plugin, meta);
            break;
        }

        case DATASOURCE:{
            IDataSourcePlugin* plugin = CastToPlugin<IDataSourcePlugin>(instance);
            if(!plugin) return false;
            dataSourceMap.insert(plugin, meta);
            break;
        }

        case DATAMANAGER:{
            IDataManagerPlugin* plugin = CastToPlugin<IDataManagerPlugin>(instance);
            if(!plugin) return false;
            dataManagerMap.insert(plugin, meta);
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

void PluginLoader::SetupPluginsConnections()
{
    qDebug() << "Setup connections";

    if(rootModelMap.count() == 1)
    {
        rootModel = rootModelMap.begin().key();
    }
    else
    {
        qDebug() << "You have" << rootModelMap.count() << "main plugins.";
        return;
    }

    QMap<IDataSourcePlugin*, MetaInfo*>::Iterator sourceIter = dataSourceMap.begin();
    while(sourceIter != dataSourceMap.end()){
        rootModel->AddDataSource(sourceIter.key(), sourceIter.value());
    }

    QMap<IDataManagerPlugin*, MetaInfo*>::Iterator managerIter = dataManagerMap.begin();
    while(managerIter != dataManagerMap.end()){
        rootModel->AddDataManager(managerIter.key(), managerIter.value());
    }

    QMap<IModelPlugin*, MetaInfo*>::Iterator modelIter = pluginModelMap.begin();
    while(modelIter != pluginModelMap.end()){
        rootModel->AddChildModel(modelIter.key(), modelIter.value());
    }

    QMap<IViewPlugin*, MetaInfo*>::Iterator viewIter = pluginViewMap.begin();
    while(viewIter != pluginViewMap.end()){
        rootModel->AddView(viewIter.key(), viewIter.value());
    }

    qDebug() << "-----Linking finished-----" << endl;
}

template <class Type>
Type *PluginLoader::CastToPlugin(QObject* possiblePlugin)
{
    Type* plugin = qobject_cast<Type*>(possiblePlugin);
    if(!plugin)
    {
        qDebug() << "Can't load the plugin " << possiblePlugin->objectName() << ": not QObject.";
    }
    return plugin;
}
