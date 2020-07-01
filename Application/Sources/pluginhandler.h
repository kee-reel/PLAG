#pragma once


#include <QFile>
#include <QPluginLoader>
#include <QtGlobal>

#include "../Interfaces/ipluginhandler.h"

class PluginHandler : public IPluginHandler
{
	Q_DISABLE_COPY(PluginHandler)
private:
	PluginHandler(quint32 uid, QSharedPointer<QPluginLoader> pluginLoader);

public:
	~PluginHandler() override = default;
	static QSharedPointer<PluginHandler> make(quint32 uid, const QString& m_filename);

	// IPlugin interface
public:
	bool load() override;
	bool unload() override;
	QString getLastError() override;
	QObject *getInstance() override;
	QWeakPointer<QJsonObject> getMeta() override;
	quint32 getUID() override;
	QString getFileName() override;

public:
	/**
	   @brief Flag that indicates that plugin meta says that it is core plugin.
	   @return Is this core plugin.
	 */
	bool isCorePlugin();

private:
	quint32 m_uid;
	QObject *m_instance;
	QSharedPointer<QPluginLoader> m_pluginLoader;
	QSharedPointer<QJsonObject> m_meta;
	QString m_lastError;
};


