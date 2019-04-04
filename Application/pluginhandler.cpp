#include "pluginhandler.h"

#include <QDebug>

PluginHandler::PluginHandler(QString filename, QObject *parent) :
    m_instance(nullptr),
    m_pluginLoader(new QPluginLoader(filename, parent)),
    m_meta(m_pluginLoader->metaData())
{
}

QObject *PluginHandler::getInstance()
{
    return m_instance;
}

const QJsonObject &PluginHandler::getMeta()
{
    return m_meta;
}

bool PluginHandler::load()
{
    if(m_instance)
    {
        return true;
    }

    if(!m_pluginLoader->load())
    {
        m_lastError = QString("Can't load the plugin %1. Error: %2")
                      .arg(m_pluginLoader->fileName()).arg(m_pluginLoader->errorString());
        qDebug() << m_lastError;
        return false;
    }

    QObject *possiblePlugin = m_pluginLoader->instance();

    if(!possiblePlugin)
    {
        m_lastError = QString("Can't load the plugin %1: not a plugin. Error: %2")
                      .arg(m_pluginLoader->fileName()).arg(m_pluginLoader->errorString());
        qCritical() << m_lastError;

        unload();
        return false;
    }

    m_instance = possiblePlugin;
    return true;
}

bool PluginHandler::unload()
{
    if(!m_pluginLoader->unload())
    {
        m_lastError = QString("Can't unload the plugin %1. Error: %2")
                      .arg(m_pluginLoader->fileName()).arg(m_pluginLoader->errorString());
        qCritical() << m_lastError;
        return false;
    }

    m_instance = nullptr;
    return true;
}

QString PluginHandler::getLastError()
{
    return m_lastError;
}

bool PluginHandler::isCorePlugin()
{
    QJsonObject metaData = m_meta.value("MetaData").toObject();

    if(!metaData.contains(META_DATA_CORE_FLAG))
    {
        return false;
    }

    return metaData.value(META_DATA_CORE_FLAG).toBool(false);
}
