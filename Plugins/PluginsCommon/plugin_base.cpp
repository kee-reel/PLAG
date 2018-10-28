#include "plugin_base.h"

#include <QtCore>
#include <QObject>
#include <QWeakPointer>

bool PluginBase::init(const MetaInfo &metaInfo, const QJsonObject &metaInfoJsonObject)
{
    m_metaInfo = metaInfo;
    qDebug() << QString("Plugin [interface: %1, plugin: %2] inited\n")
                   .arg(m_metaInfo.Name).arg(m_metaInfo.InterfaceName);

    return true;
}

bool PluginBase::addReferencePlugin(const IPlugin *referencePlugin)
{
    const auto& referenceName = referencePlugin->getPluginMetaInfo().Name;
    auto referenceIter = m_installedReferencesMap.find(referenceName);
    if(referenceIter == m_installedReferencesMap.end())
    {
        raiseError(QString("PluginBase::addReferencePlugin: reference %1 not found in needed references").arg(referenceName));
        return false;
    }

    if(!referenceIter.value())
    {
        referenceIter.value() = true;
        connect(this, &PluginBase::onClose, static_cast<const PluginBase*>(referencePlugin), &PluginBase::referencePluginClosed);
    }
    else
    {
        raiseError(QString("PluginBase::addReferencePlugin: reference %1 already set").arg(referenceName));
        return false;
    }
    return true;
}

bool PluginBase::removeReferencePlugin(const IPlugin *referencePlugin)
{
    const auto& referenceName = referencePlugin->getPluginMetaInfo().Name;
    auto referenceIter = m_installedReferencesMap.find(referenceName);
    if(referenceIter == m_installedReferencesMap.end())
    {
        raiseError(QString("PluginBase::removeReferencePlugin: reference %1 not found in needed references").arg(referenceName));
        return false;
    }

    if(referenceIter.value())
    {
        referenceIter.value() = false;
        disconnect(this, &PluginBase::onClose, static_cast<const PluginBase*>(referencePlugin), &PluginBase::referencePluginClosed);
    }
    else
    {
        raiseError(QString("PluginBase::removeReferencePlugin: reference %1 already set").arg(referenceName));
        return false;
    }
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

QWidget *PluginBase::getWidget()
{
    return qobject_cast<QWidget*>(this);
}

bool PluginBase::open(const IPlugin *openedByPlugin)
{
    return true;
}

bool PluginBase::close(const IPlugin *closedByPlugin)
{
    emit onClose(this);
    return true;
}

void PluginBase::referencePluginClosed(const PluginBase *closedReference)
{
}

void PluginBase::raiseError(QString errorMessage)
{
    m_lastErrorString = errorMessage;
    qCritical() << QString("[interface: %1, plugin: %2] Error raised: %3\n")
                   .arg(m_metaInfo.Name).arg(m_metaInfo.InterfaceName).arg(m_lastErrorString);
}
