#include "linkeritem.h"

#include "../../PluginsInterfaces/inewarchtestplugin.h"
#include "../../PluginsCommon/iplugin.h"

LinkerItem::LinkerItem(QWeakPointer<IPluginHandler> pluginHandler, QSharedPointer<MetaInfo> metaInfo) :
    m_plugin(nullptr),
    m_pluginHandler(pluginHandler),
    m_metaInfo(*metaInfo.data())
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
    auto&& name = linkItem.data()->getName();
    qDebug() << "Plugin" << m_metaInfo.InterfaceName << "get reference" << name;
    m_references.insert(name, linkItem);
}

void LinkerItem::removeReference(QWeakPointer<LinkerItem> linkItem)
{

}

bool LinkerItem::load()
{
    if(m_plugin)
        return true;

    m_pluginHandler.data()->load();
    auto* instance = m_pluginHandler.data()->getInstance();
    m_plugin = qobject_cast<IPlugin*>(instance);
    m_plugin->init(m_metaInfo, m_pluginHandler.data()->getMeta());

    return true;
}

bool LinkerItem::open(const QWidget* parent)
{
    for(const auto& reference : m_references)
    {
        reference.data()->load();
        auto pluginInstance = reference.data()->getPluginInstance();
        m_plugin->addReferencePlugin(pluginInstance);
    }

    m_plugin->open(m_plugin);
}

const MetaInfo &LinkerItem::getMeta()
{
    return m_metaInfo;
}

QVector<QWeakPointer<IMainMenuModel::IMenuItem>> LinkerItem::getReferences()
{
    QVector<QWeakPointer<IMainMenuModel::IMenuItem>> referencesVec;
    referencesVec.reserve(m_references.size());
    for(const auto &key : m_references)
    {
        referencesVec.append(key);
    }
    return referencesVec;
}

void LinkerItem::addReferent(QWeakPointer<LinkerItem> linkItem)
{
    m_referents.insert(linkItem.data()->getName(), linkItem);
}

const IPlugin* LinkerItem::getPluginInstance()
{
    return m_plugin;
}
