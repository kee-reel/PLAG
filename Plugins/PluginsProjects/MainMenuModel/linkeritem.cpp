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
    m_uiElementId(uid)
{
}

const QString &LinkerItem::getName()
{
    return m_metaInfo.InterfaceName;
}

const QList<QString> &LinkerItem::getReferenceNamesList()
{
    return m_metaInfo.RelatedPluginNames;
}

void LinkerItem::addReference(QWeakPointer<LinkerItem> linkItem)
{
    auto &&name = linkItem.data()->getName();
    qDebug() << "Plugin" << m_metaInfo.InterfaceName << "get reference" << name;
    m_references.insert(name, linkItem);
    m_connectedItems.insert(name, linkItem);
}

void LinkerItem::addReferent(QWeakPointer<LinkerItem> linkItem)
{
    const auto &name = linkItem.data()->getName();
    m_referents.insert(name, linkItem);
    m_connectedItems.insert(name, linkItem);
}

void LinkerItem::removeReference(QWeakPointer<LinkerItem> linkItem)
{

}

bool LinkerItem::load()
{
    if(m_pluginInstance)
    {
        return true;
    }

    if(!m_pluginHandler.data()->load())
    {
        qCritical() << QString("Can't load plugin [%1 : %2]; aborting")
                    .arg(m_metaInfo.InterfaceName)
                    .arg(m_metaInfo.Name);
        return false;
    }

    m_pluginQObject = m_pluginHandler.data()->getInstance();

    m_pluginInstance = qobject_cast<IPlugin *>(m_pluginQObject);
    m_pluginInstance->init(m_metaInfo, m_pluginHandler.data()->getMeta());

    auto result = connect(m_pluginQObject, SIGNAL(onOpen(const IPlugin *)), this, SLOT(onOpenSlot(const IPlugin *)));
    connect(m_pluginQObject, SIGNAL(onClose(const IPlugin *)), this, SLOT(onCloseSlot(const IPlugin *)));

    if(!prepareConnectedPlugins())
    {
        return false;
    }

    return true;
}

bool LinkerItem::prepareConnectedPlugins()
{
    QList<QWeakPointer<LinkerItem>> loadedItemsList;

    for(const auto &item : m_references)
    {
        if(!item.data()->load())
        {
            unloadItems(loadedItemsList);
            return false;
        }
        loadedItemsList.append(item);
        auto pluginInstance = item.data()->getPluginInstance();
        m_pluginInstance->addReferencePlugin(pluginInstance);
    }

    for(const auto &item : m_referents)
    {
        if(!item.data()->load())
        {
            unloadItems(loadedItemsList);
            return false;
        }
        loadedItemsList.append(item);
        item.data()->getPluginInstance()->addReferencePlugin(m_pluginInstance);
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

bool LinkerItem::isOpened() const
{
    return m_isOpened;
}

MetaInfo LinkerItem::getMeta() const
{
    return m_metaInfo;
}

bool LinkerItem::open(const IPlugin *pluginInstance)
{
    if(!pluginInstance)
    {
        pluginInstance = m_pluginInstance;
    }

    if(!prepareConnectedPlugins())
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

void LinkerItem::onOpenSlot(const IPlugin *openedByPlugin)
{
    qDebug() << QString("LinkerItem::onOpenSlot: open plugin [%1 : %2]")
             .arg(m_metaInfo.InterfaceName)
             .arg(m_metaInfo.Name);
    if(isOpened())
    {
        qDebug() << QString("Plugin [%1 : %2] alredy opened")
                 .arg(m_metaInfo.InterfaceName)
                 .arg(m_metaInfo.Name);
        return;
    }

    if(!prepareConnectedPlugins())
    {
        m_pluginInstance->close(m_pluginInstance);
        return;
    }

    m_isOpened = true;
    emit onOpened(getElementId());
}

void LinkerItem::onCloseSlot(const IPlugin *closedByPlugin)
{
    m_isOpened = false;
    emit onClosed(getElementId());
}

int LinkerItem::getElementId() const
{
    return m_uiElementId;
}

QWidget *LinkerItem::getElementWidget() const
{
    return m_pluginInstance ? m_pluginInstance->getWidget() : nullptr;
}

const QObject *LinkerItem::getElementSignalsLinkObject() const
{
    return this;
}

QVector<QWeakPointer<IUIManager::IUIElement> > LinkerItem::getConnectedElements()
{
    QVector<QWeakPointer<IUIManager::IUIElement>> connectedItemsVec;
    connectedItemsVec.reserve(m_connectedItems.size());
    for(const auto &item : m_connectedItems)
    {
        connectedItemsVec.append(item);
    }
    return connectedItemsVec;
}

bool LinkerItem::open(QWeakPointer<IUIManager::IUIElement> openedByElement)
{
    qDebug() << QString("LinkerItem::open: open plugin [%1 : %2]")
             .arg(m_metaInfo.InterfaceName)
             .arg(m_metaInfo.Name);
    if(isOpened())
    {
        qDebug() << QString("Plugin [%1 : %2] alredy opened")
                 .arg(m_metaInfo.InterfaceName)
                 .arg(m_metaInfo.Name);
        return false;
    }

    auto elementQObject = openedByElement.data()->getElementSignalsLinkObject();
    const auto *linkerItem = qobject_cast<const LinkerItem *>(elementQObject);
    auto pluginInstance = linkerItem->getPluginInstance();
    open(pluginInstance);
    return true;
}

bool LinkerItem::close(QWeakPointer<IUIManager::IUIElement> closedByElement)
{
    return true;
}
