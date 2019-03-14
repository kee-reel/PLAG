#include "linkeritem.h"

#include "../../PluginsInterfaces/inewarchtestplugin.h"
#include "../../PluginsCommon/iplugin.h"

LinkerItem::LinkerItem(QWeakPointer<IPluginHandler> pluginHandler, QSharedPointer<MetaInfo> metaInfo, int uid) :
    QObject(nullptr),
    m_pluginInstance(nullptr),
    m_pluginQObject(nullptr),
    m_isOpened(false),
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

    connect(m_pluginQObject, SIGNAL(onOpen(const IPlugin *)), this, SLOT(onInstanceOpenSlot(const IPlugin *)));
    connect(m_pluginQObject, SIGNAL(onClose(const IPlugin *)), this, SLOT(onInstanceCloseSlot(const IPlugin *)));

    bool unloadResult = loadReferencePlugins();
    if(!unloadResult)
    {
        qCritical() << QString("Can't load plugin %1: error: %3.")
                    .arg(getPluginDescriptionName())
                    .arg(m_pluginHandler.data()->getLastError());
    }

    return unloadResult;
}

bool LinkerItem::unload()
{
    if(!isLoaded())
    {
        return true;
    }

    disconnect(m_pluginQObject, SIGNAL(onOpen(const IPlugin *)), this, SLOT(onInstanceOpenSlot(const IPlugin *)));
    disconnect(m_pluginQObject, SIGNAL(onClose(const IPlugin *)), this, SLOT(onInstanceCloseSlot(const IPlugin *)));

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
    QList<QWeakPointer<LinkerItem>> loadedItemsList;

    for(const auto &item : m_references)
    {
        if(item.data()->isLoaded())
        {
            continue;
        }

        if(!item.data()->load())
        {
            unloadItems(loadedItemsList);
            return false;
        }
        loadedItemsList.append(item);
        auto pluginInstance = item.data()->getPluginInstance();
        m_pluginInstance->addReferencePlugin(pluginInstance);
    }

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

        !item.data()->unload();
        auto pluginInstance = item.data()->getPluginInstance();
        m_pluginInstance->removeReferencePlugin(pluginInstance);
    }

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

bool LinkerItem::open(const IPlugin *pluginInstance)
{
    if(!pluginInstance)
    {
        pluginInstance = m_pluginInstance;
    }

    if(!loadReferencePlugins())
    {
        return false;
    }

    m_pluginInstance->open(pluginInstance);
    return true;
}

IPlugin *LinkerItem::getPluginInstance() const
{
    return m_pluginInstance;
}

void LinkerItem::onInstanceOpenSlot(const IPlugin *openedByPlugin)
{
    if(isOpened())
    {
        qDebug() << QString("Plugin [%1 : %2] alredy opened")
                 .arg(m_metaInfo.InterfaceName)
                 .arg(m_metaInfo.Name);
        return;
    }

    if(!loadReferencePlugins())
    {
        m_pluginInstance->close(m_pluginInstance);
        return;
    }

    m_isOpened = true;
    emit onItemOpened(getPluginUID());
}

void LinkerItem::onInstanceCloseSlot(const IPlugin *closedByPlugin)
{
    m_isOpened = false;
    emit onItemClosed(getPluginUID());
}

QWidget *LinkerItem::getWidget() const
{
    return m_pluginInstance ? m_pluginInstance->getWidget() : nullptr;
}

const QObject *LinkerItem::getObject() const
{
    return this;
}

QVector<QWeakPointer<IPluginLinker::ILinkerItem> > LinkerItem::getReferences()
{
    QVector<QWeakPointer<IPluginLinker::ILinkerItem> > items;
    for(const auto &item : m_references)
    {
        items.append(item);
    }
    return items;
}

QVector<QWeakPointer<IPluginLinker::ILinkerItem> > LinkerItem::getReferents()
{
    QVector<QWeakPointer<IPluginLinker::ILinkerItem> > items;
    for(const auto &item : m_referents)
    {
        items.append(item);
    }
    return items;
}

bool LinkerItem::open(QWeakPointer<IPluginLinker::ILinkerItem> openedByElement)
{
    if(isOpened())
    {
        qDebug() << QString("Plugin [%1 : %2] alredy opened")
                 .arg(m_metaInfo.InterfaceName)
                 .arg(m_metaInfo.Name);
        return false;
    }

    auto elementQObject = openedByElement.data()->getObject();
    const auto *linkerItem = qobject_cast<const LinkerItem *>(elementQObject);
    auto pluginInstance = linkerItem->getPluginInstance();
    open(pluginInstance);
    return true;
}

bool LinkerItem::close(QWeakPointer<IPluginLinker::ILinkerItem> closedByElement)
{
    return true;
}
