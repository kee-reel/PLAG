#include "linkeritem.h"

#include "../../Common/iplugin.h"

LinkerItem::LinkerItem(QWeakPointer<IPluginHandler> pluginHandler, QSharedPointer<MetaInfo> metaInfo, int uid) :
    QObject(nullptr),
    m_pluginInstance(nullptr),
    m_pluginQObject(nullptr),
    m_isReferencesLoaded(false),
    m_isOpened(false),
    m_pluginHandler(pluginHandler),
    m_metaInfo(*metaInfo.data()),
    m_pluginUID(uid)
{
    m_descriptionName = QString("[%1 : %2]").arg(m_metaInfo.InterfaceName).arg(m_metaInfo.Name);

    if(m_pluginHandler.data()->getInstance())
    {
        initPlugin();
    }
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
    connect(linkItem.data(), SIGNAL(onLoaded(int)), this, SLOT(onReferenceLoaded(int)));
}

void LinkerItem::removeReference(QWeakPointer<LinkerItem> linkItem)
{
    auto &&uid = linkItem.data()->getPluginUID();
    m_references.remove(uid);
    disconnect(linkItem.data(), SIGNAL(onLoaded(int)), this, SLOT(onReferenceLoaded(int)));
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
//        qDebug() << "Plugin" << m_metaInfo.Name << "already loaded";
        return true;
    }

    qDebug() << "Loading plugin:" << m_metaInfo.Name;

    if(!m_pluginHandler.data()->load())
    {
        qCritical() << QString("Can't load plugin [%1 : %2]: error: %3.")
                    .arg(m_metaInfo.InterfaceName)
                    .arg(m_metaInfo.Name)
                    .arg(m_pluginHandler.data()->getLastError());
        return false;
    }

    if(!initPlugin())
    {
        return false;
    }

    emit onLoaded(m_pluginUID);
    return true;
}

bool LinkerItem::loadAllConnected()
{
    for(auto referent : m_references)
    {
        referent.data()->load();
    }
    for(auto referent : m_referents)
    {
        referent.data()->load();
    }
    return true;
}

bool LinkerItem::initPlugin()
{
    m_pluginQObject = m_pluginHandler.data()->getInstance();
    m_pluginInstance = qobject_cast<IPlugin *>(m_pluginQObject);

    if(!m_pluginInstance)
    {
        qCritical() << QString("Can't load plugin [%1 : %2]: error: can't cast plugin to IPlugin interface.")
                    .arg(m_metaInfo.InterfaceName)
                    .arg(m_metaInfo.Name);
        return false;
    }

    m_pluginInstance->init(m_metaInfo, m_pluginHandler.data()->getMeta());

    connect(m_pluginQObject, SIGNAL(onOpen(IPlugin *)), this, SLOT(onInstanceOpenSlot()));
    connect(m_pluginQObject, SIGNAL(onClose(IPlugin *)), this, SLOT(onInstanceCloseSlot()));

    loadReferencePlugins();

    return true;
}

bool LinkerItem::unload()
{
    if(!isLoaded())
    {
        return true;
    }

    disconnect(m_pluginQObject, SIGNAL(onOpen(IPlugin*)), this, SLOT(onInstanceOpenSlot()));
    disconnect(m_pluginQObject, SIGNAL(onClose(IPlugin*)), this, SLOT(onInstanceCloseSlot()));

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

    m_isReferencesLoaded = true;

    for(const auto &item : m_references)
    {
//        qDebug() << "Load reference" << item.data()->getMeta().InterfaceName << item.data()->getMeta().Name << item.data()->getMeta().RelatedPluginNames;
        auto referenceInstance = item.data()->getPluginInstance();
        if(referenceInstance)
        {
            m_pluginInstance->addReferencePlugin(referenceInstance);
        }
        else
        {
            m_isReferencesLoaded = false;
        }
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

void LinkerItem::onReferenceLoaded(int referenceId)
{
    if(!m_pluginInstance)
    {
        return;
    }
    auto reference = m_references[referenceId];
    auto pluginInstance = reference.data()->getPluginInstance();
    m_pluginInstance->addReferencePlugin(pluginInstance);
    qDebug() << "Add referenc" << reference.data()->getPluginDescriptionName() << "to" << getPluginDescriptionName();
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
