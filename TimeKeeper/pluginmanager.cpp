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
    QDir path(QDir::currentPath() + "/Modules");
    qDebug() << "Modules path is " << path.absolutePath();

    foreach (QString file, path.entryList(QDir::Files))
    {
        SetupPlugin(path.absolutePath() + "/" + file);
    }
    SetupPluginsConnections();
    qDebug() << "Everything done." << endl;
}

void PluginManager::SetupPluginsConnections()
{
    //TODO: Maybe run in new thread
    QHash<QString, IPluginModel*>::Iterator parentPluginModelIterator = pluginModelNameHash.begin();
    QHash<QString, IPluginModel*>::Iterator childPluginModelIterator;
    QHash<QString, IPluginView*>::Iterator childPluginViewIterator;
    qDebug() << "Linking" << pluginModelParentNameHash.count() << "IModelPlugins and" <<
                pluginViewParentNameHash.count() << "IViewPlugins";
    // For all child plugins
    while(parentPluginModelIterator != pluginModelNameHash.end())
    {
        // Search in all plugins
        childPluginModelIterator = pluginModelParentNameHash.find(parentPluginModelIterator.key());
        if(childPluginModelIterator != pluginModelParentNameHash.end())
        {
            do{
                IPluginModel* childPlugin = childPluginModelIterator.value();
                IPluginModel* parentPlugin = parentPluginModelIterator.value();
                MetaInfo* meta = pluginModelMap[childPlugin];
                parentPlugin->AddChildPlugin(childPlugin, meta);
                qDebug() << "Child plugin" << meta->Name << "binds with" << meta->ParentPluginName;
                ++childPluginModelIterator;
            }while(childPluginModelIterator != pluginModelParentNameHash.end() &&
                   childPluginModelIterator.key() == parentPluginModelIterator.key());
        }
        else
        {
            qDebug() << "Plugin" << parentPluginModelIterator.key() << "has no childs.";
        }

        childPluginViewIterator = pluginViewParentNameHash.find(parentPluginModelIterator.key());
        if(childPluginViewIterator != pluginViewParentNameHash.end())
        {
            do{
                IPluginView* childPlugin = childPluginViewIterator.value();
                IPluginModel* parentPlugin = parentPluginModelIterator.value();
                MetaInfo* meta = pluginViewMap[childPlugin];
                childPlugin->SetModel(pluginModelInstancesMap[parentPlugin]);
                childPlugin->Open(parent);
                qDebug() << "Plugin" << pluginModelMap[parentPlugin]->Name <<
                            "binds with view" << meta->Name;
                ++childPluginViewIterator;
            }while(childPluginViewIterator != pluginViewParentNameHash.end() &&
                   childPluginViewIterator.key() == parentPluginModelIterator.key());
        }
        else
        {
            qDebug() << "Plugin" << parentPluginModelIterator.key() << "has no views.";
        }

        ++parentPluginModelIterator;
    }

    if(mainPluginMap.count() == 1)
    {
        mainPlugin = mainPluginMap.begin().key();
        qDebug() << "Starting main plugin" << mainPluginMap.begin().value()->Name << endl;
    }
    else
    {
        qDebug() << "You have several main plugins.";
    }

    if(DBManagerMap.count() == 1)
    {
        DBManager = DBManagerMap.begin().key();
        qDebug() << "Current database driver is" << DBManagerMap.begin().value()->Name << endl;
    }
    else
    {
        qDebug() << "You have several database plugins.";
    }

    qDebug() << "System contains" << DBToolMap.count() << "DBToolPlugins:";
    foreach(IDBToolPlugin* tool, DBToolMap.keys())
    {
        qDebug() << DBToolMap[tool]->Name;
        tool->SetDBManager(DBManager);
    }
}

bool PluginManager::SetupPlugin(QString pluginName)
{
    qDebug() << "----------";
    QPluginLoader* loader = LoadPlugin(pluginName);
    if(!loader) return false;

    QObject* possiblePlugin = GetPluginInstance(loader);
    if(!possiblePlugin) return false;

    MetaInfo* pluginType = GetPluginMeta(loader);
    if(!pluginType) return false;

    bool isBinded = BindPluginToSystem(loader, possiblePlugin, pluginType);
    if(!isBinded) return false;
    qDebug() << "----------" << endl;
    return true;
}

QPluginLoader *PluginManager::LoadPlugin(QString pluginName)
{
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
    loader->load();
    return loader;
}

QObject* PluginManager::GetPluginInstance(QPluginLoader* loader)
{
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
    const QString FieldName             = "Name";
    const QString FieldModuleType       = "ModuleType";
    const QString FieldParentModuleName = "ParentModuleName";
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
    if(pluginModelNameHash.contains(newMetaInfo->Name))
    {
        qDebug() << "Module with name" << newMetaInfo->Name << "already exists!";
        return NULL;
    }

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

bool PluginManager::BindPluginToSystem(QPluginLoader* loader, QObject* possiblePlugin, MetaInfo* moduleMeta)
{
    switch (moduleMeta->Type) {
    case TOOLMODEL:{
        IPluginModel* plugin = CastToPlugin<IPluginModel>(loader, possiblePlugin);
        if(!plugin) return false;
        pluginModelMap.insert(plugin, moduleMeta);
        pluginModelInstancesMap.insert(plugin, possiblePlugin);
        pluginModelNameHash.insert(moduleMeta->Name, plugin);
        pluginModelParentNameHash.insert(moduleMeta->ParentPluginName, plugin);
        break;
    }

    case TOOLVIEW:{
        IPluginView* plugin = CastToPlugin<IPluginView>(loader, possiblePlugin);
        if(!plugin) return false;
        pluginViewMap.insert(plugin, moduleMeta);
        pluginViewParentNameHash.insert(moduleMeta->ParentPluginName, plugin);
        break;
    }

    case DBMANAGER:{
        IDBManagerPlugin* plugin = CastToPlugin<IDBManagerPlugin>(loader, possiblePlugin);
        if(!plugin) return false;
        DBManagerMap.insert(plugin, moduleMeta);
        break;
    }

    case DBTOOL:{
        IDBToolPlugin* plugin = CastToPlugin<IDBToolPlugin>(loader, possiblePlugin);
        if(!plugin) return false;
        DBToolMap.insert(plugin, moduleMeta);
        break;
    }

    case MAIN:{
        IPluginModel* plugin = CastToPlugin<IPluginModel>(loader, possiblePlugin);
        if(!plugin) return false;
        pluginModelMap.insert(plugin, moduleMeta);
        pluginModelInstancesMap.insert(plugin, possiblePlugin);
        pluginModelNameHash.insert(moduleMeta->Name, plugin);
        pluginModelParentNameHash.insert(moduleMeta->ParentPluginName, plugin);
        mainPluginMap.insert(plugin, moduleMeta);
        break;
    }

    default:{
        return false;
        break;
    }

    }

    qDebug() << "Module" << moduleMeta->Name << "succesfully added to system.";
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
    qDebug() << "Inherits: " <<  possiblePlugin->inherits("IPluginModel");
    return plugin;
}

bool PluginManager::CheckPluginWidget(IPluginModel* plugin)
{
//    QWidget* pluginWidget = plugin->GetWidget();
//    if(!pluginWidget)
//    {
//        qDebug() << "Can't load the plugin: it has no widget.";
//        return false;
//    }
    return true;
}
