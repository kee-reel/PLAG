#include "plugin_base.h"

void PluginBase::constructorInit()
{
    m_isInited = false;
    m_isAllReferencesSet = false;
    m_isAllReferencesReady = false;
}

bool PluginBase::init(const MetaInfo &metaInfo, const QJsonObject &metaInfoJsonObject)
{
    m_metaInfo = metaInfo;

    if(m_metaInfo.RelatedPluginNames.count())
    {
        for(const auto &reference : m_metaInfo.RelatedPluginNames)
        {
            m_referencesMap.insert(reference, nullptr);
        }

        for(const auto &reference : m_metaInfo.RelatedPluginNames)
        {
            m_referencesReadyMap.insert(reference, false);
        }
    }
    else
    {
        m_isAllReferencesSet = true;
        onAllReferencesSet();
        m_isAllReferencesReady = true;
        onAllReferencesReady();
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
        connect(referencePlugin->getObject(), SIGNAL(onReady(IPlugin*)), this, SLOT(onReferenceReady(IPlugin*)));
        if(referencePlugin->isReady())
        {
            onReferenceReady(referencePlugin);
        }
    }
    else
    {
        //        raiseError(QString("PluginBase::addReferencePlugin: reference %1 already set").arg(referenceName));
        return true;
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
        disconnect(referencePlugin->getObject(), SIGNAL(onReady(IPlugin*)), this, SLOT(onReferenceReady(IPlugin*)));
    }
    else
    {
        raiseError(QString("PluginBase::removeReferencePlugin: reference %1 already set").arg(referenceName));
        return false;
    }

    m_isAllReferencesSet = false;
    m_isAllReferencesReady = false;
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
    return this;
}

QWidget *PluginBase::getWidget()
{
#if defined(PLUGIN_BASE_QOBJECT)
    return nullptr;
#else
    return qobject_cast<QWidget *>(this);
#endif
}

bool PluginBase::isReady()
{
    return m_isAllReferencesReady;
}

bool PluginBase::open()
{
    emit onOpen(this);
    return true;
}

bool PluginBase::close()
{
    emit onClose(this);
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
        onAllReferencesSet();
    }
}

void PluginBase::checkAllReferencesReady()
{
    bool isAllReferencesReady = true;
    for (const auto &reference : m_referencesReadyMap)
    {
        if(!reference)
        {
            isAllReferencesReady = false;
            break;
        }
    }

    if(isAllReferencesReady)
    {
        if(m_isAllReferencesSet && !m_isAllReferencesReady)
        {
            m_isAllReferencesReady = true;
            onAllReferencesReady();
        }
    }
}

QString PluginBase::getPluginDescription(const MetaInfo &meta)
{
    return QString("[%1 : %2]").arg(meta.InterfaceName).arg(meta.Name);
}

void PluginBase::onAllReferencesSet()
{
//    for(auto iter = m_referencesMap.begin(); iter != m_referencesMap.end(); ++iter)
//    {
//        auto&& interfaceName = iter.key();
//        auto&& plugin = iter.value();
//        setProperty(interfaceName.toStdString().c_str(), QVariant());
//    }
    qDebug() << "onAllReferencesSet" << m_metaInfo.Name;
    checkAllReferencesReady();
    emit onReady(this);
}

void PluginBase::onAllReferencesReady()
{
    qDebug() << "onAllReferencesReady" << m_metaInfo.Name;
}

void PluginBase::onReferenceReady(IPlugin *reference)
{
    const auto &referenceName = reference->getPluginMetaInfo().InterfaceName;
    auto referenceIter = m_referencesReadyMap.find(referenceName);
    if(referenceIter == m_referencesReadyMap.end())
    {
        raiseError(QString("PluginBase::onReferenceReady: reference %1 not found in needed references").arg(referenceName));
        return;
    }

    if(!referenceIter.value())
    {
        m_referencesReadyMap[referenceName] = true;
    }
    else
    {
        return;
    }

    checkAllReferencesReady();
}
