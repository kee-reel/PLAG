#include "pluginhandler.h"

#include "../Interfaces/icore.h"

#include <QDebug>
#include <utility>

QString CORE_INTERFACE_NAME = qobject_interface_iid<ICore*>();

PluginHandler::PluginHandler(quint32 uid, QSharedPointer<QPluginLoader> pluginLoader) :
	m_uid(uid),
	m_instance(nullptr),
	m_pluginLoader(std::move(pluginLoader)),
	m_meta(new QJsonObject(m_pluginLoader->metaData()))
{
}

QSharedPointer<PluginHandler> PluginHandler::make(quint32 uid, const QString& filename)
{
	if(!QLibrary::isLibrary(filename))
	{
		qDebug() << QStringLiteral("PluginLoader: can't load plugin '%1': not a library.").arg(filename);
		return nullptr;
	}

	QSharedPointer<QPluginLoader> pluginLoader(new QPluginLoader(filename));
	if(pluginLoader->isLoaded())
	{
		qDebug() << QStringLiteral("PluginLoader: can't load plugin '%1': already loaded.").arg(filename);
		return nullptr;
	}
	return QSharedPointer<PluginHandler>(new PluginHandler(uid, pluginLoader));
}

QObject *PluginHandler::getInstance()
{
	return m_instance;
}

QWeakPointer<QJsonObject> PluginHandler::getMeta()
{
	return m_meta;
}

quint32 PluginHandler::getUID()
{
	return m_uid;
}

QString PluginHandler::getFileName()
{
	return m_pluginLoader->fileName();
}

bool PluginHandler::load()
{
	if(m_instance)
	{
		return true;
	}

	if(!m_pluginLoader->load())
	{
		m_lastError = QStringLiteral("Can't load the plugin %1. Error: %2").arg(m_pluginLoader->fileName(), m_pluginLoader->errorString());
		qDebug() << m_lastError;
		return false;
	}

	QObject *possiblePlugin = m_pluginLoader->instance();

	if(!possiblePlugin)
	{
		m_lastError = QStringLiteral("Can't load the plugin %1: not a plugin. Error: %2").arg(m_pluginLoader->fileName(), m_pluginLoader->errorString());
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
		m_lastError = QStringLiteral("Can't unload the plugin %1. Error: %2").arg(m_pluginLoader->fileName(), m_pluginLoader->errorString());
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
	QJsonObject metaData = m_meta->value("MetaData").toObject();
	return metaData.contains(CORE_INTERFACE_NAME);
}
