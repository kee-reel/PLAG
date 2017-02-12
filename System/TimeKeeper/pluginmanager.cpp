#include "pluginmanager.h"

PluginManager::PluginManager(QWidget* parent) : QObject(parent)
{
    this->parent = parent;
    mainPlugin = NULL;
    pluginTypesNames.insert("TOOLMODEL",    TOOLMODEL);
    pluginTypesNames.insert("TOOLVIEW",     TOOLVIEW);
    pluginTypesNames.insert("DBMANAGER",    DBMANAGER);
    pluginTypesNames.insert("DBTOOL",       DBTOOL);
    pluginTypesNames.insert("MAIN",         MAIN);
}

PluginManager::~PluginManager()
{
    for(QMap<IPluginModel*, MetaInfo*>::Iterator i = pluginModelMap.begin(); i != pluginModelMap.end(); ++i)
    {
        delete i.value();
        delete i.key();
    }

    for(QMap<IDBManagerPlugin*, MetaInfo*>::Iterator i = DBManagerMap.begin(); i != DBManagerMap.end(); ++i)
    {
        delete i.value();
        delete i.key();
    }
}

void PluginManager::SetupPlugins()
{
    foreach (QString libPath, QApplication::libraryPaths())
    {
        QDir path = libPath;
        qDebug() << "Path" << path;
        foreach (QString file, path.entryList(QDir::Files))
        {
            SetupPlugin(path.absolutePath() + "/" + file);
        }
    }
    SetupPluginsConnections();
    qDebug() << "Everything done." << endl;
    //QSqlQuery query = DBManager->ExecuteQuery("pragma database_list");
    //qDebug() << query.
}

void PluginManager::SetupPluginsConnections()
{
    qDebug() << "Setup connections";
    // Setup DBManager
    if(DBManagerMap.count() == 1)
    {
        DBManager = DBManagerMap.begin().key();
        qDebug() << "Current database driver is" << DBManagerMap.begin().value()->Name << endl;
        DBManager->SetupDatabase();
    }
    else
    {
        qDebug() << "You have several database plugins.";
    }

    // Setup DBTools
    qDebug() << "System contains" << DBToolMap.count() << "DBToolPlugins:";
    foreach(IDBToolPlugin* tool, DBToolMap.keys())
    {
        qDebug() << DBToolMap[tool]->Name;
        tool->SetDBManager(DBManager);
    }

    //TODO: Maybe run in new thread
    QHash<QString, IPluginModel*>::Iterator parentPluginModelIterator = pluginModelNameHash.begin();
    QHash<QString, QVector<IPluginModel*>>::Iterator childPluginModelIterator;
    QHash<QString, QVector<IPluginView*>>::Iterator childPluginViewIterator;
    qDebug() << "=====Linking" << pluginModelNameHash.count() << "IModelPlugins and" <<
                pluginViewParentNameHash.count() << "IViewPlugins=====";
    // For all child plugins
    while(parentPluginModelIterator != pluginModelNameHash.end())
    {
        qDebug() << endl << "Search relations for" << parentPluginModelIterator.key();

        // Search for related models
        childPluginModelIterator = pluginModelParentNameHash.find(parentPluginModelIterator.key());
        if(childPluginModelIterator != pluginModelParentNameHash.end())
        {
            QVector<IPluginModel*> childPlugins = childPluginModelIterator.value();
            IPluginModel* parentPlugin = parentPluginModelIterator.value();
            for(int i = 0; i < childPlugins.count(); i++)
            {
                MetaInfo* meta = pluginModelMap[childPlugins[i]];
                parentPlugin->AddChildPlugin(childPlugins[i], meta);
                qDebug() << "Child plugin" << meta->Name << "binds with" << meta->ParentPluginName;
            }
        }
        else
        {
            qDebug() << "Plugin" << parentPluginModelIterator.key() << "has no childs.";
        }

        // Search for related views
        childPluginViewIterator = pluginViewParentNameHash.find(parentPluginModelIterator.key());
        if(childPluginViewIterator != pluginViewParentNameHash.end())
        {
            QVector<IPluginView*> childPlugins = childPluginViewIterator.value();
            IPluginModel* parentPlugin = parentPluginModelIterator.value();
            for(int i = 0; i < childPlugins.count(); i++)
            {
                MetaInfo* meta = pluginViewMap[childPlugins[i]];
                parentPlugin->AddView(childPlugins[i], meta);
                qDebug() << "Plugin model" << pluginModelMap[parentPlugin]->Name <<
                            "binds with view" << meta->Name;
            }
        }
        else
        {
            qDebug() << "Plugin" << parentPluginModelIterator.key() << "has no views.";
        }
        ++parentPluginModelIterator;
    }

    // Search for related DBTools
    QHash<QString, IPluginModel*>::Iterator pluginModelWithDBToolIterator = pluginDBToolNameHash.begin();
    while(pluginModelWithDBToolIterator != pluginDBToolNameHash.end())
    {
        qDebug() << "Linking DBTool for" << pluginModelMap[pluginModelWithDBToolIterator.value()]->Name;
        QObject* DBTool = DBToolNameHash[pluginModelWithDBToolIterator.key()];
        pluginModelWithDBToolIterator.value()->SetDBTool(DBTool);
        qDebug() << pluginModelMap[pluginModelWithDBToolIterator.value()]->Name << "linked with"
                 << pluginModelWithDBToolIterator.key();
        ++pluginModelWithDBToolIterator;
    }

    qDebug() << "-----Linking finished-----" << endl;

    if(mainPluginMap.count() == 1)
    {
        mainPlugin = mainPluginMap.begin().key();
        qDebug() << "Starting main plugin" << mainPluginMap.begin().value()->Name << endl;
        mainPlugin->Open(parent);
    }
    else
    {
        qDebug() << "You have several main plugins.";
    }

}

bool PluginManager::SetupPlugin(QString pluginName)
{
    qDebug() << "=====" << pluginName << "=====";
    QPluginLoader* loader = LoadPlugin(pluginName);
    if(!loader) return false;

    MetaInfo* pluginType = GetPluginMeta(loader);
    if(!pluginType) return false;

    QObject* possiblePlugin = GetPluginInstance(loader);
    if(!possiblePlugin) return false;

    bool isBinded = BindPluginToSystem(loader, possiblePlugin, pluginType);
    if(!isBinded) return false;
    qDebug() << "=====" << pluginName << "=====";
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
    const QString FieldModuleType       = "ModuleType";
    const QString FieldParentModuleName = "ParentModuleName";
    const QString FieldDBToolName       = "DBTool";
    QJsonObject metaData = loader->metaData()["MetaData"].toObject();

    // Check if all meta fields exists
    QStringList metaFieldsNames;
    metaFieldsNames << FieldName << FieldModuleType << FieldParentModuleName;
    foreach (QString metaFieldName, metaFieldsNames) {
        QString typeStr = metaData[metaFieldName].toString();
        if(typeStr == "")
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
        qDebug() << "Meta error: field" << FieldName << "is empty.";
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
    if(newMetaInfo->Type == MAIN || newMetaInfo->Type == TOOLMODEL)
    {
        newMetaInfo->DBToolName = metaData[FieldDBToolName].toString();
        if(newMetaInfo->DBToolName != "")
            qDebug() << "DBTool:" << newMetaInfo->DBToolName;
    }

    // Set module parent name
    newMetaInfo->ParentPluginName = metaData[FieldParentModuleName].toString();
    if(newMetaInfo->ParentPluginName == "")
    {
        qDebug() << "Meta error: field" << FieldParentModuleName << "is empty.";
        delete newMetaInfo;
        return NULL;
    }
    qDebug() << "Parent:" << newMetaInfo->ParentPluginName;
    return newMetaInfo;
}

bool PluginManager::BindPluginToSystem(QPluginLoader* loader, QObject* possiblePlugin, MetaInfo* meta)
{
    qDebug() << "Bind plugin to system";
    switch (meta->Type) {
    case TOOLMODEL:{
        IPluginModel* plugin = CastToPlugin<IPluginModel>(loader, possiblePlugin);
        if(!plugin) return false;
        pluginModelMap.insert(plugin, meta);
        //pluginModelInstancesMap.insert(plugin, possiblePlugin);
        pluginModelNameHash.insert(meta->Name, plugin);
        pluginModelParentNameHash[meta->ParentPluginName].append(plugin);
        if(meta->DBToolName != "")
            pluginDBToolNameHash.insert(meta->DBToolName, plugin);
        break;
    }

    case TOOLVIEW:{
        IPluginView* plugin = CastToPlugin<IPluginView>(loader, possiblePlugin);
        if(!plugin) return false;
        pluginViewMap.insert(plugin, meta);
        pluginViewParentNameHash[meta->ParentPluginName].append(plugin);
        break;
    }

    case DBMANAGER:{
        IDBManagerPlugin* plugin = CastToPlugin<IDBManagerPlugin>(loader, possiblePlugin);
        if(!plugin) return false;
        DBManagerMap.insert(plugin, meta);
        break;
    }

    case DBTOOL:{
        IDBToolPlugin* plugin = CastToPlugin<IDBToolPlugin>(loader, possiblePlugin);
        if(!plugin) return false;
        DBToolMap.insert(plugin, meta);
        DBToolNameHash.insert(meta->Name, possiblePlugin);
        break;
    }

    case MAIN:{
        IPluginModel* plugin = CastToPlugin<IPluginModel>(loader, possiblePlugin);
        if(!plugin) return false;
        pluginModelMap.insert(plugin, meta);
        //pluginModelInstancesMap.insert(plugin, possiblePlugin);
        pluginModelNameHash.insert(meta->Name, plugin);
        pluginModelParentNameHash[meta->ParentPluginName].append(plugin);
        if(meta->DBToolName != "")
            pluginDBToolNameHash.insert(meta->DBToolName, plugin);
        mainPluginMap.insert(plugin, meta);
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


//        // Create a new file
//        qDebug() << path.absolutePath() + "/out.txt";
//        QFile file("/out.txt");
//        file.open(QIODevice::WriteOnly | QIODevice::Text);
//        if(!file.isOpen())
//        {
//            qDebug() << file.errorString();
//        }
//        else
//        {
//            QTextStream out(&file);
//            out << "This file is generated by Qt\n";
//            // optional, as QFile destructor will already do it:
//            file.close();
//        }
