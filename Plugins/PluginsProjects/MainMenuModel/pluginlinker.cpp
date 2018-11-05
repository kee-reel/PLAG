#include "pluginlinker.h"
#include "pluginlinker.h"

PluginLinker::PluginLinker() :
    m_pluginUidCounter(0)
{
    //    rootMenuItem = new IMainMenuModel::MenuItem();
}

bool PluginLinker::addCorePlugin(QWeakPointer<IPluginHandler> pluginHandler)
{
    auto linkerItem = createLinkerItem(pluginHandler);
    if(linkerItem.isNull())
    {
        qCritical() << "PluginLinker::addNewPlugin: core plugin adding failed";
        return false;
    }
    m_corePlugin = linkerItem;
    return true;
}

bool PluginLinker::addNewPlugin(QWeakPointer<IPluginHandler> pluginHandler)
{
    auto linkerItem = createLinkerItem(pluginHandler);
    if(linkerItem.isNull())
    {
        qCritical() << "PluginLinker::addNewPlugin: plugin adding failed";
        return false;
    }

    return true;
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

    // Set module name
    newMetaInfo->Name = metaInfo.value(META_FIELD_NAME).toString();
    if(newMetaInfo->Name == "")
    {
        qCritical() << QString("PluginBase::parseMetaInfo: parse error: field %1 is empty.").arg(META_FIELD_NAME);
        return nullptr;
    }

    // Set module type
    newMetaInfo->InterfaceName = metaInfo.value(META_FIELD_INTERFACE).toString().toUpper();
    if(newMetaInfo->InterfaceName == "")
    {
        qWarning() << QString("PluginBase::parseMetaInfo: plugin %1 field %2 is empty; "
                              "this item won't be referenced by other plugins.")
                   .arg(newMetaInfo->Name)
                   .arg(META_FIELD_INTERFACE);
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

QSharedPointer<LinkerItem> PluginLinker::createLinkerItem(QWeakPointer<IPluginHandler> pluginHandler)
{
    auto jsonObject = pluginHandler.data()->getMeta();
    auto metaInfo = parseMetaInfo(jsonObject);

    if(metaInfo.isNull())
    {
        qCritical() << "PluginLinker::createLinkerItem: can't load plugin";
        return QWeakPointer<LinkerItem>();
    }

    auto &&linkerItem = new LinkerItem(pluginHandler, metaInfo, m_pluginUidCounter);
    auto &&linkerItemPtr = QSharedPointer<LinkerItem>(linkerItem);
    m_linkerItemsMap.insertMulti(linkerItemPtr->getName(), linkerItemPtr);
    ++m_pluginUidCounter;

    return linkerItemPtr;
}

template<class Type>
Type *PluginLinker::castToPlugin(QObject *possiblePlugin) const
{
    Type *plugin = qobject_cast<Type *>(possiblePlugin);

    if(!plugin)
    {
        qDebug() << "Can't load the plugin " << possiblePlugin->objectName() << ": not QObject.";
    }

    return plugin;
}

bool PluginLinker::setupLinks()
{
    bool isLinkageSucceded = true;
    // For all plugins.
    for(auto iter = m_linkerItemsMap.begin(); iter != m_linkerItemsMap.end(); ++iter)
    {
        auto &item = iter.value();
        auto &referencesNames = item->getReferenceNamesList();
        // For all references of plugin.
        for(auto &referenceName : referencesNames)
        {
            auto referenceIter = m_linkerItemsMap.find(referenceName);
            if(referenceIter != m_linkerItemsMap.end())
            {
                // For references with same interface.
                do
                {
                    item->addReference(referenceIter.value());
                    referenceIter.value()->addReferent(item);
                    ++referenceIter;
                }
                while(referenceIter.key() == referenceName && referenceIter != m_linkerItemsMap.end());
            }
            else
            {
                isLinkageSucceded = false;
            }
        }
    }
    return isLinkageSucceded;
}

const QWeakPointer<LinkerItem> PluginLinker::getCorePlugin()
{
    return m_corePlugin;
}

const QMap<QString, QWeakPointer<LinkerItem> > PluginLinker::getClildPluginsMap()
{
    QMap<QString, QWeakPointer<LinkerItem> > linkerItemsMapCopy;
    for(auto iter = m_linkerItemsMap.begin(); iter != m_linkerItemsMap.end(); ++iter)
    {
        linkerItemsMapCopy.insert(iter.key(), iter.value());
    }
    linkerItemsMapCopy.remove(m_corePlugin->getName());
    return linkerItemsMapCopy;
}

const QMap<QString, QWeakPointer<LinkerItem> > PluginLinker::getAllPluginsMap()
{
    QMap<QString, QWeakPointer<LinkerItem> > linkerItemsMapCopy;
    for(auto iter = m_linkerItemsMap.begin(); iter != m_linkerItemsMap.end(); ++iter)
    {
        linkerItemsMapCopy.insert(iter.key(), iter.value());
    }
    return linkerItemsMapCopy;
}
