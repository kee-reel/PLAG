#include "linkeritem.h"

#include "../../PluginsInterfaces/inewarchtestplugin.h"

LinkerItem::LinkerItem(QWeakPointer<IPluginHandler> pluginHandler, QSharedPointer<MetaInfo> metaInfo) :
    m_pluginHandler(pluginHandler),
    m_metaInfo(metaInfo)
{
}

void LinkerItem::addReference(QWeakPointer<LinkerItem> linkItem)
{
    m_referencesList.append(linkItem);
}

void LinkerItem::addReferent(QWeakPointer<LinkerItem> linkItem)
{
    m_referentsList.append(linkItem);
}

bool LinkerItem::load()
{
    m_pluginHandler.data()->load();

    auto* instance = m_pluginHandler.data()->getInstance();
    auto* pluginInstance = qobject_cast<INewArchTestPlugin*>(instance);
    int x = 5;
    qDebug() << x << "*" << x << "=" << pluginInstance->someMethod(5);
    return true;
}

QWeakPointer<MetaInfo> LinkerItem::getMeta()
{
    return m_metaInfo;
}

QVector<QWeakPointer<IMainMenuModel::IMenuItem>> LinkerItem::getReferences()
{
    QVector<QWeakPointer<IMainMenuModel::IMenuItem>> referencesVec(m_referentsList.size());
    for(int i = 0; i < m_referentsList.size(); ++i)
    {
        referencesVec[i] = m_referentsList[i];
    }
    return referencesVec;
}
