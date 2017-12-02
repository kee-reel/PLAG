#include "pluginlinker.h"

PluginLinker::PluginLinker()
{
    pluginTypesNames.insert("COREPLUGIN",    COREPLUGIN);
    pluginTypesNames.insert("MODELPLUGIN",  MODELPLUGIN);
    pluginTypesNames.insert("VIEWPLUGIN",   VIEWPLUGIN);
    pluginTypesNames.insert("DATASOURCEPLUGIN",   DATASOURCEPLUGIN);
    pluginTypesNames.insert("DATAMANAGERPLUGIN",  DATAMANAGERPLUGIN);
    PluginHandler::Init(handlersWithReferencesNames, handlersWithSelfNames);
    rootMenuItem = new IMainMenuModel::MenuItem();
}

void PluginLinker::AddNewPlugin(QObject *instance, QJsonObject *meta)
{
    MetaInfo* pluginMeta = GetPluginMeta(meta);

    if(!pluginMeta)
        return;

    bool isBinded = BindPluginToSystem(instance, pluginMeta);

    if(!isBinded)
        return;
}

MetaInfo *PluginLinker::GetPluginMeta(QJsonObject *metaData)
{
    qDebug() << "Get meta";
    QString FieldModuleType         = "Type";
    QString FieldInterface          = "Interface";
    QString FieldName               = "Name";
    QString FieldRelatedPluginNames = "RelatedPluginInterfaces";
    QJsonObject metaInfo = metaData->value("MetaData").toObject();
    // Check if all meta fields exists
    QStringList metaFieldsNames;
    metaFieldsNames << FieldInterface << FieldModuleType << FieldName << FieldRelatedPluginNames;

    foreach (QString metaFieldName, metaFieldsNames)
    {
        if(!metaInfo.contains(metaFieldName))
        {
            qDebug() << "Meta has no field:" << metaFieldName << "But has fields:";

            for(QJsonObject::Iterator i = metaInfo.begin(); i != metaInfo.end(); ++i)
                qDebug() << i.key() << " = " << i.value();

            return NULL;
        }
    }

    MetaInfo* newMetaInfo = new MetaInfo();
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
    // Set module type
    QString moduleInterfaceStr = metaInfo.value(FieldInterface).toString().toUpper();
    newMetaInfo->InterfaceName = moduleInterfaceStr;
    qDebug() << "Interface:" << moduleInterfaceStr;
    // Set module name
    newMetaInfo->Name = metaInfo.value(FieldName).toString();

    if(newMetaInfo->Name == "")
    {
        qDebug() << "Meta error: field" << FieldName << "is empty";
        delete newMetaInfo;
        return NULL;
    }

    qDebug() << "Name:" << newMetaInfo->Name;
    // Set module parent name
    QJsonArray array = metaInfo.value(FieldRelatedPluginNames).toArray();

    for(int i = 0, n = array.size(); i < n; ++i)
        newMetaInfo->RelatedPluginNames.append(array[i].toString().toUpper());

    qDebug() << "Parent:" << newMetaInfo->RelatedPluginNames;
    return newMetaInfo;
}

bool PluginLinker::BindPluginToSystem(QObject *instance, MetaInfo *meta)
{
    qDebug() << "Bind plugin to system";
    PluginInfo *pluginInfo;

    switch (meta->Type)
    {
        case COREPLUGIN:
            rootMenuItem->meta = meta;

        case MODELPLUGIN:
        {
            IModelPlugin* plugin = CastToPlugin<IModelPlugin>(instance);

            if(!plugin)
                return false;

            pluginInfo = new PluginInfo(plugin, instance, meta);
            break;
        }

        case VIEWPLUGIN:
        {
            IViewPlugin* plugin = CastToPlugin<IViewPlugin>(instance);

            if(!plugin)
                return false;

            pluginInfo = new PluginInfo(plugin, instance, meta);
            rootMenuItem->Items.append(meta);
            menuItems.insert(meta, pluginInfo);
            break;
        }

        case DATASOURCEPLUGIN:
        {
            IDataSourcePlugin* plugin = CastToPlugin<IDataSourcePlugin>(instance);

            if(!plugin)
                return false;

            pluginInfo = new PluginInfo(plugin, instance, meta);
            break;
        }

        case DATAMANAGERPLUGIN:
        {
            IDataManagerPlugin* plugin = CastToPlugin<IDataManagerPlugin>(instance);

            if(!plugin)
                return false;

            pluginInfo = new PluginInfo(plugin, instance, meta);
            break;
        }

        default:
        {
            return false;
            break;
        }
    }

    pluginsInfo.append(pluginInfo);
    PluginHandler *handler = new PluginHandler(pluginInfo);
    pluginsHandlers.append(handler);
    qDebug() << "Module" << meta->Name << "succesfully added to system." << endl;
    return true;
}

void PluginLinker::CallOnAllSetup()
{
    for(int i = 0, n = pluginsInfo.size(); i < n; ++i)
        pluginsInfo[i]->Plugin.any->OnAllSetup();
}

template<class Type>
Type *PluginLinker::CastToPlugin(QObject *possiblePlugin)
{
    Type* plugin = qobject_cast<Type*>(possiblePlugin);

    if(!plugin)
        qDebug() << "Can't load the plugin " << possiblePlugin->objectName() << ": not QObject.";

    return plugin;
}

IMainMenuModel::MenuItem* PluginLinker::SetupLinks()
{
    for(int i = 0, n = pluginsHandlers.size(); i < n; ++i)
        pluginsHandlers[i]->SetupRelations();

    CallOnAllSetup();
    return rootMenuItem;
}
