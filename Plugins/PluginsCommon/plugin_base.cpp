#include "plugin_base.h"

#include <QtCore>
#include <QObject>
#include <QWeakPointer>
#include <QVariant>


void PluginBase::constructorInit()
{
    m_isInited = false;
    m_isAllReferencesSet = false;
}

bool PluginBase::init(const MetaInfo &metaInfo, const QJsonObject &metaInfoJsonObject)
{
    m_metaInfo = metaInfo;

    for(const auto &reference : m_metaInfo.RelatedPluginNames)
    {
        m_referencesMap.insert(reference, nullptr);
    }

    m_isInited = true;

    return true;
}

bool PluginBase::addReferencePlugin(IPlugin *referencePlugin)
{
    const auto &referenceName = referencePlugin->getPluginMetaInfo().InterfaceName;
    auto referenceIter = m_referencesMap.find(referenceName);
    if(referenceIter == m_referencesMap.end())
    {
        raiseError(QString("PluginBase::addReferencePlugin: reference %1 not found in needed references").arg(referenceName));
        return false;
    }

    if(!referenceIter.value())
    {
        m_referencesMap[referenceName] = referencePlugin;
    }
    else
    {
        //        raiseError(QString("PluginBase::addReferencePlugin: reference %1 already set").arg(referenceName));
        return false;
    }

    checkAllReferencesSet();

    return true;
}

bool PluginBase::removeReferencePlugin(IPlugin *referencePlugin)
{
    const auto &referenceName = referencePlugin->getPluginMetaInfo().InterfaceName;
    auto referenceIter = m_referencesMap.find(referenceName);
    if(referenceIter == m_referencesMap.end())
    {
        raiseError(QString("PluginBase::removeReferencePlugin: reference %1 not found in needed references").arg(
                       referenceName));
        return false;
    }

    if(referenceIter.value())
    {
        referenceIter.value() = nullptr;
    }
    else
    {
        raiseError(QString("PluginBase::removeReferencePlugin: reference %1 already set").arg(referenceName));
        return false;
    }

    m_isAllReferencesSet = false;
    return true;
}

QString PluginBase::getLastError() const
{
    return m_lastErrorString;
}

const MetaInfo &PluginBase::getPluginMetaInfo() const
{
    return m_metaInfo;
}

QObject *PluginBase::getObject()
{
    return static_cast<QObject *>(this);
}

QWidget *PluginBase::getWidget()
{
#if defined(PLUGIN_BASE_QOBJECT)
    return nullptr;
#else
    return qobject_cast<QWidget *>(this);
#endif
}

bool PluginBase::open()
{
    emit onOpen();
    return true;
}

bool PluginBase::close()
{
    emit onClose();
    return true;
}

void PluginBase::raiseError(QString errorMessage)
{
    m_lastErrorString = errorMessage;
    qCritical() << QString("[interface: %1, plugin: %2] Error raised: %3\n")
                .arg(m_metaInfo.Name).arg(m_metaInfo.InterfaceName).arg(m_lastErrorString);
}

void PluginBase::checkAllReferencesSet()
{
    bool isAllReferencesSet = true;
    for (const auto &reference : m_referencesMap)
    {
        if(!reference)
        {
            isAllReferencesSet = false;
            break;
        }
    }

    if(isAllReferencesSet)
    {
        m_isAllReferencesSet = true;
        onAllReferencesSetStateChanged();
    }
}

QString PluginBase::getPluginDescription(const MetaInfo &meta)
{
    return QString("[%1 : %2]").arg(meta.InterfaceName).arg(meta.Name);
}

void PluginBase::onAllReferencesSetStateChanged()
{

}
