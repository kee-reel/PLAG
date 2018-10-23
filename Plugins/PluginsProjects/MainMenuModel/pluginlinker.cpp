#include "pluginlinker.h"

PluginLinker::PluginLinker()
{
//    rootMenuItem = new IMainMenuModel::MenuItem();
}

bool PluginLinker::addNewPlugin(QWeakPointer<IPluginHandler> pluginHandler)
{
    auto jsonObject = pluginHandler.data()->getMeta();
    auto metaInfo = parseMetaInfo(jsonObject);

    if(metaInfo.isNull())
        return false;

    auto linkerItem = new LinkerItem(pluginHandler, metaInfo);
    auto linkerItemPtr = QSharedPointer<LinkerItem>(linkerItem);
    m_linkerItemsMap.insertMulti(metaInfo->InterfaceName, linkerItemPtr);
}

QSharedPointer<MetaInfo> PluginLinker::parseMetaInfo(const QJsonObject &metaInfoObject) const
{
    QJsonObject metaInfo = metaInfoObject.value("MetaData").toObject();
    // Check if all meta fields exists
    QStringList metaFieldsNames;
    metaFieldsNames << META_FIELD_INTERFACE <<
                       META_FIELD_NAME <<
                       META_FIELD_RELATED_PLUGIN_INTERFACES;

    for(QString metaFieldName : metaFieldsNames)
    {
        if(!metaInfo.contains(metaFieldName))
        {
            qDebug() << "PluginBase::parseMetaInfo: meta has no field:" << metaFieldName << "But has fields:";
            for(auto iter = metaInfo.begin(); iter != metaInfo.end(); ++iter)
            {
                qDebug() << iter.key() << " = " << iter.value();
            }
            return nullptr;
        }
    }

    QSharedPointer<MetaInfo> newMetaInfo(new MetaInfo());

    // Set module type
    newMetaInfo->InterfaceName = metaInfo.value(META_FIELD_INTERFACE).toString().toUpper();
    if(newMetaInfo->InterfaceName == "")
    {
        qDebug() << "PluginBase::parseMetaInfo: parse error: field" << META_FIELD_INTERFACE << "is empty.";
        return nullptr;
    }

    // Set module name
    newMetaInfo->Name = metaInfo.value(META_FIELD_NAME).toString();
    if(newMetaInfo->Name == "")
    {
        qDebug() << "PluginBase::parseMetaInfo: parse error: field" << META_FIELD_NAME << "is empty.";
        return nullptr;
    }

    // Set module parent name
    QJsonArray array = metaInfo.value(META_FIELD_RELATED_PLUGIN_INTERFACES).toArray();
    for(auto iter = array.begin(); iter != array.end(); ++iter)
    {
        newMetaInfo->RelatedPluginNames.append(iter->toString().toUpper());
    }

    qDebug() << "PluginBase::parseMetaInfo: succesfuly parsed:" <<
           META_FIELD_NAME << newMetaInfo->Name << endl <<
           META_FIELD_INTERFACE << newMetaInfo->InterfaceName << endl <<
           META_FIELD_RELATED_PLUGIN_INTERFACES << newMetaInfo->RelatedPluginNames << endl;
    return newMetaInfo;
}

template<class Type>
Type *PluginLinker::castToPlugin(QObject *possiblePlugin) const
{
    Type* plugin = qobject_cast<Type*>(possiblePlugin);

    if(!plugin)
        qDebug() << "Can't load the plugin " << possiblePlugin->objectName() << ": not QObject.";

    return plugin;
}

bool PluginLinker::setupLinks()
{
    bool isLinkageSucceded = true;
    // For all plugins
    for(auto iter = m_linkerItemsMap.begin(); iter != m_linkerItemsMap.end(); ++iter)
    {
        auto& item = iter.value();
        auto& referencesNames = item->getReferenceNamesList();
        // For all references of plugin
        for(auto& referenceName : referencesNames)
        {
            auto referenceIter = m_linkerItemsMap.find(referenceName);
            if(referenceIter != m_linkerItemsMap.end())
            {
                do
                {
                    item->addReference(referenceIter.value());
                    ++referenceIter;
                }
                while(referenceIter != m_linkerItemsMap.end());
            }
            else
            {
                isLinkageSucceded = false;
            }
        }
    }
    return isLinkageSucceded;
}

const QMap<QString, QSharedPointer<LinkerItem> > &PluginLinker::getPluginsMap()
{
    return m_linkerItemsMap;
}
