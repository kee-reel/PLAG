#include "pluginlinkercore.h"

PluginLinkerCore::PluginLinkerCore() :
    PluginBase(nullptr),
    m_parentWidget(nullptr),
    m_pluginUidCounter(0)
{
    //    rootMenuItem = new IMainMenuModel::MenuItem();
}

PluginLinkerCore::~PluginLinkerCore()
{
}

int PluginLinkerCore::getCorePluginUID()
{
    return m_corePlugin.data()->getPluginUID();
}

void PluginLinkerCore::addPlugins(const QVector<QWeakPointer<IPluginHandler> > &pluginHandlers)
{
    for(auto& plugin : pluginHandlers)
    {
        addPlugin(plugin);
    }
}

void PluginLinkerCore::start(QWeakPointer<IPluginHandler> selfHandler, QWidget *parentWidget)
{
    if(!addCorePlugin(selfHandler))
    {
        raiseError("Can't add core plugin.");
        return;
    }

    m_parentWidget = parentWidget;

    if(!setupLinks())
    {
        raiseError("Can't link plugins.");
    }

    m_corePlugin->open();
}

bool PluginLinkerCore::close()
{
    for (auto iter = m_linkerItemsMap.begin(); iter != m_linkerItemsMap.end(); ++iter)
    {
        if(iter.key() != m_corePlugin.data()->getPluginUID())
        {
            iter.value().data()->unload();
        }
    }
    return true;
}

QWidget *PluginLinkerCore::getWidget()
{
    return m_parentWidget;
}

QMap<int, QWeakPointer<IPluginLinker::ILinkerItem> > PluginLinkerCore::getPluginsMap()
{
    QMap<int, QWeakPointer<IPluginLinker::ILinkerItem> > mapCopy;
    for(auto iter = m_linkerItemsMap.begin(); iter != m_linkerItemsMap.end(); ++iter)
    {
        mapCopy.insert(iter.key(), iter.value());
    }
    return mapCopy;
}

bool PluginLinkerCore::addCorePlugin(QWeakPointer<IPluginHandler> pluginHandler)
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

bool PluginLinkerCore::addPlugin(QWeakPointer<IPluginHandler> pluginHandler)
{
    auto linkerItem = createLinkerItem(pluginHandler);
    if(linkerItem.isNull())
    {
        qCritical() << "PluginLinker::addNewPlugin: plugin adding failed";
        return false;
    }

    return true;
}

QSharedPointer<MetaInfo> PluginLinkerCore::parseMetaInfo(const QJsonObject &metaInfoObject) const
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

    //    qDebug() << "PluginBase::parseMetaInfo: succesfuly parsed:" <<
    //             META_FIELD_NAME << newMetaInfo->Name << endl <<
    //             META_FIELD_INTERFACE << newMetaInfo->InterfaceName << endl <<
    //             META_FIELD_RELATED_PLUGIN_INTERFACES << newMetaInfo->RelatedPluginNames << endl;
    return newMetaInfo;
}

QSharedPointer<LinkerItem> PluginLinkerCore::createLinkerItem(QWeakPointer<IPluginHandler> pluginHandler)
{
    auto jsonObject = pluginHandler.data()->getMeta();
    auto metaInfo = parseMetaInfo(jsonObject);

    if(metaInfo.isNull())
    {
        qCritical() << "PluginLinker::createLinkerItem: can't load plugin" << m_metaInfo.Name;
        return QWeakPointer<LinkerItem>();
    }

    auto &&linkerItem = new LinkerItem(pluginHandler, metaInfo, m_pluginUidCounter);
    auto linkerItemPtr = QSharedPointer<LinkerItem>(linkerItem);
    m_linkerItemsMap.insert(linkerItemPtr->getPluginUID(), linkerItemPtr);
    m_interfacesMap.insertMulti(metaInfo->InterfaceName, linkerItemPtr);
    ++m_pluginUidCounter;
    qDebug() << "Plugin" << metaInfo->Name << "added";
    return linkerItemPtr;
}

template<class Type>
Type *PluginLinkerCore::castToPlugin(QObject *possiblePlugin) const
{
    Type *plugin = qobject_cast<Type *>(possiblePlugin);

    if(!plugin)
    {
        qDebug() << "Can't load the plugin " << possiblePlugin->objectName() << ": not QObject.";
    }

    return plugin;
}

bool PluginLinkerCore::setupLinks()
{
    bool isLinkageSucceded = true;
    QStringList troubledPlugins;
    // For all plugins.
    for(auto iter = m_interfacesMap.begin(); iter != m_interfacesMap.end(); ++iter)
    {
        auto &item = iter.value();
        auto &referencesNames = item->getReferenceNamesList();
//        qDebug() << "Setup" << item.get()->getMeta().Name;
        // For all references of plugin.
        for(auto &referenceName : referencesNames)
        {
//            qDebug() << "Link to reference" << referenceName;
            auto referenceIter = m_interfacesMap.find(referenceName);
            if(referenceIter != m_interfacesMap.end())
            {
                // For references with same interface.
                do
                {
                    item->addReference(referenceIter.value());
                    referenceIter.value()->addReferent(item);
                    ++referenceIter;
                }
                while(referenceIter.key() == referenceName && referenceIter != m_interfacesMap.end());
            }
            else
            {
                if(!troubledPlugins.contains(referenceName))
                {
                    troubledPlugins.append(referenceName);
                }
                isLinkageSucceded = false;
            }
        }
    }

    if(isLinkageSucceded)
    {
        qDebug() << "Linkage suceeded";
    }
    else
    {
        qWarning() << "Linkage failed, next referenced plugins not found:" << troubledPlugins;
    }

    for (auto iter = m_linkerItemsMap.begin(); iter != m_linkerItemsMap.end(); ++iter)
    {
        iter.value().data()->load();
    }

    onLinkageFinished();
    return isLinkageSucceded;
}
