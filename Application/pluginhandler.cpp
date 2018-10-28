#include "pluginhandler.h"

#include <QDebug>

PluginHandler::PluginHandler(QString filename, QObject *parent)
{
    m_instance = nullptr;
    m_pluginLoader.reset(new QPluginLoader(filename, parent));
    m_meta = m_pluginLoader->metaData();
    m_file.setFileName(filename);
}

QObject *PluginHandler::getInstance()
{
    qDebug() << "Load plugin:" << m_pluginLoader->fileName();

    if(!m_instance)
    {
        load();
        m_instance = ResolvePluginInstance();
    }

    return m_instance;
}

const QJsonObject &PluginHandler::getMeta()
{
    return m_meta;
}

bool PluginHandler::load()
{
    if(m_instance)
        return true;

    bool result = m_pluginLoader->load();

    if(!result)
    {
        m_lastError = QString("Can't load the plugin %1. Error: %2")
                    .arg(m_pluginLoader->fileName()).arg(m_pluginLoader->errorString());
        qDebug() << m_lastError;
    }

    m_instance = m_pluginLoader->instance();
    return result;
}

bool PluginHandler::unload()
{
    bool result = m_pluginLoader->unload();

    if(!result)
    {
        m_lastError = QString("Can't unload the plugin %1. Error: %2")
                    .arg(m_pluginLoader->fileName()).arg(m_pluginLoader->errorString());
        qCritical() << m_lastError;
    }

    return result;
}

QString PluginHandler::getLastError()
{
    return m_lastError;
}

bool PluginHandler::isCorePlugin()
{
    QJsonObject metaData = m_meta.value("MetaData").toObject();

    if(!metaData.contains(META_DATA_CORE_FLAG))
        return false;

    return metaData.value(META_DATA_CORE_FLAG).toBool(false);
}

QObject* PluginHandler::ResolvePluginInstance()
{
    if(!m_pluginLoader->isLoaded())
    {
        qCritical() << "Plugin not loaded yet.";
        return nullptr;
    }

    qDebug() << "Get instance";
    QObject* possiblePlugin = m_pluginLoader->instance();

    if(!possiblePlugin)
    {
        m_lastError = QString("Can't load the plugin %1: not a plugin. Error: %2")
                    .arg(m_pluginLoader->fileName()).arg(m_pluginLoader->errorString());
        qCritical() << m_lastError;
    }

    return possiblePlugin;
}
