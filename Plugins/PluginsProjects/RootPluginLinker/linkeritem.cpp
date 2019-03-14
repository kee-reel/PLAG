#include "linkeritem.h"

#include "../../PluginsInterfaces/inewarchtestplugin.h"
#include "../../PluginsCommon/iplugin.h"

LinkerItem::LinkerItem(QWeakPointer<IPluginHandler> pluginHandler, QSharedPointer<MetaInfo> metaInfo, int uid) :
    QObject(nullptr),
    m_pluginInstance(nullptr),
    m_pluginQObject(nullptr),
    m_isOpened(false),
    m_isReferencesLoaded(false),
    m_pluginHandler(pluginHandler),
    m_metaInfo(*metaInfo.data()),
    m_pluginUID(uid)
{
    m_descriptionName = QString("[%1 : %2]").arg(m_metaInfo.InterfaceName).arg(m_metaInfo.Name);
}

const QString LinkerItem::getPluginDescriptionName()
{
    return m_descriptionName;
}

const QString &LinkerItem::getInterfaceName()
{
    return m_metaInfo.InterfaceName;
}

const QList<QString> &LinkerItem::getReferenceNamesList()
{
    return m_metaInfo.RelatedPluginNames;
}

void LinkerItem::addReference(QWeakPointer<LinkerItem> linkItem)
{
    auto &&uid = linkItem.data()->getPluginUID();
    m_references.insert(uid, linkItem);
}

void LinkerItem::removeReference(QWeakPointer<LinkerItem> linkItem)
{
    auto &&uid = linkItem.data()->getPluginUID();
    m_references.remove(uid);
}

void LinkerItem::addReferent(QWeakPointer<LinkerItem> linkItem)
{
    auto &&uid = linkItem.data()->getPluginUID();
    m_referents.insert(uid, linkItem);
}

void LinkerItem::removeReferent(QWeakPointer<LinkerItem> linkItem)
{
    auto &&uid = linkItem.data()->getPluginUID();
    m_referents.remove(uid);
}

bool LinkerItem::load()
{
    if(isLoaded())
    {
        qDebug() << "Plugin" << m_metaInfo.Name << "already loaded";
        return true;
    }

    if(!m_pluginHandler.data()->load())
    {
        qCritical() << QString("Can't load plugin [%1 : %2]: error: %3.")
                    .arg(m_metaInfo.InterfaceName)
                    .arg(m_metaInfo.Name)
                    .arg(m_pluginHandler.data()->getLastError());
        return false;
    }

    m_pluginQObject = m_pluginHandler.data()->getInstance();

    m_pluginInstance = qobject_cast<IPlugin *>(m_pluginQObject);
    m_pluginInstance->init(m_metaInfo, m_pluginHandler.data()->getMeta());

    connect(m_pluginQObject, SIGNAL(onOpen()), this, SLOT(onInstanceOpenSlot()));
    connect(m_pluginQObject, SIGNAL(onClose()), this, SLOT(onInstanceCloseSlot()));

    qDebug() << "Plugin" << m_metaInfo.Name << "loaded";

    bool loadResult = loadReferencePlugins();
    if(!loadResult)
    {
        qCritical() << QString("Can't load plugin %1: error: %3.")
                    .arg(getPluginDescriptionName())
                    .arg(m_pluginHandler.data()->getLastError());
    }

    return loadResult;
}

bool LinkerItem::loadWithReferents()
{
    load();
    for(auto referent : m_referents)
    {
        referent.data()->load();
    }
    return true;
}

bool LinkerItem::unload()
{
    if(!isLoaded())
    {
        return true;
    }

    disconnect(m_pluginQObject, SIGNAL(onOpen()), this, SLOT(onInstanceOpenSlot()));
    disconnect(m_pluginQObject, SIGNAL(onClose()), this, SLOT(onInstanceCloseSlot()));

    m_pluginQObject = nullptr;
    m_pluginInstance = nullptr;

    bool unloadResult = m_pluginHandler.data()->unload();
    if(!unloadResult)
    {
        qCritical() << QString("Error raised during unloading of plugin %1: error: %3.")
                    .arg(getPluginDescriptionName())
                    .arg(m_pluginHandler.data()->getLastError());
    }

    return unloadResult;
}

bool LinkerItem::loadReferencePlugins()
{
    if(m_isReferencesLoaded)
    {
        return true;
    }

    qDebug() << "Len:" << m_references.count();

    QList<QWeakPointer<LinkerItem>> loadedItemsList;
    for(const auto &item : m_references)
    {
        qDebug() << "Load reference" << item.data()->getMeta().InterfaceName << item.data()->getMeta().Name << item.data()->getMeta().RelatedPluginNames;
        if(!item.data()->load())
        {
            unloadItems(loadedItemsList);
            m_isReferencesLoaded = false;
            return false;
        }
        loadedItemsList.append(item);
        auto pluginInstance = item.data()->getPluginInstance();
        m_pluginInstance->addReferencePlugin(pluginInstance);
    }

    m_isReferencesLoaded = true;
    return true;
}

bool LinkerItem::unloadReferencePlugins()
{
    for(const auto &item : m_references)
    {
        if(!item.data()->isLoaded())
        {
            continue;
        }

        item.data()->unload();
        auto pluginInstance = item.data()->getPluginInstance();
        m_pluginInstance->removeReferencePlugin(pluginInstance);
    }

    m_isReferencesLoaded = false;
    return true;
}

void LinkerItem::unloadItems(const QList<QWeakPointer<LinkerItem>> &loadedItemsList)
{
    for(const auto &item : loadedItemsList)
    {
        item.data()->unload();
    }
}

bool LinkerItem::isLoaded() const
{
    return m_pluginInstance != nullptr;
}

bool LinkerItem::isOpened() const
{
    return m_isOpened;
}

MetaInfo LinkerItem::getMeta() const
{
    return m_metaInfo;
}

int LinkerItem::getPluginUID() const
{
    return m_pluginUID;
}

IPlugin *LinkerItem::getPluginInstance() const
{
    return m_pluginInstance;
}

void LinkerItem::onInstanceOpenSlot()
{
    if(!loadReferencePlugins())
    {
        m_pluginInstance->close();
        return;
    }

    m_isOpened = true;
    emit onOpened(getPluginUID());
}

void LinkerItem::onInstanceCloseSlot()
{
    m_isOpened = false;
    emit onClosed(getPluginUID());
}

QWidget *LinkerItem::getWidget() const
{
    return m_pluginInstance ? m_pluginInstance->getWidget() : nullptr;
}

const QObject *LinkerItem::getObject() const
{
    return this;
}

QMap<int, QWeakPointer<IPluginLinker::ILinkerItem>> LinkerItem::getReferences()
{
    QMap<int, QWeakPointer<IPluginLinker::ILinkerItem>> references;
    for(auto iter = m_references.begin(); iter != m_references.end(); ++iter)
    {
        references.insert(iter.key(), iter.value());
    }
    return references;
}

QMap<int, QWeakPointer<IPluginLinker::ILinkerItem>> LinkerItem::getReferents()
{
    QMap<int, QWeakPointer<IPluginLinker::ILinkerItem>> referents;
    for(auto iter = m_referents.begin(); iter != m_referents.end(); ++iter)
    {
        referents.insert(iter.key(), iter.value());
    }
    return referents;
}

bool LinkerItem::open()
{
    if(!loadReferencePlugins())
    {
        return false;
    }

    m_pluginInstance->open();
    return true;
}

bool LinkerItem::close()
{
    return true;
}
