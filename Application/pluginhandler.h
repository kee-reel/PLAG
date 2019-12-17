#ifndef PLUGIN_H
#define PLUGIN_H

#include <QFile>
#include <QPluginLoader>
#include <QtGlobal>

#include "ipluginhandler.h"

const QString META_DATA_CORE_FLAG = QStringLiteral("isCorePlugin");

class PluginHandler : public IPluginHandler
{
	Q_DISABLE_COPY(PluginHandler)
private:
	PluginHandler(uid_t uid, QSharedPointer<QPluginLoader> pluginLoader);

public:
	~PluginHandler() override = default;
	static QSharedPointer<PluginHandler> make(uid_t uid, const QString& m_filename);

	// IPlugin interface
	public:
	bool load() override;
	bool unload() override;
	QString getLastError() override;
	QObject *getInstance() override;
	QWeakPointer<QJsonObject> getMeta() override;
	uid_t getUID() override;
	/**
	   @brief Flag that indicates that plugin meta says that it is core plugin.
	   @return Is this core plugin.
	 */
	bool isCorePlugin();
	
private:
	uid_t m_uid;
	QObject *m_instance;
	QSharedPointer<QPluginLoader> m_pluginLoader;
	QSharedPointer<QJsonObject> m_meta;
	QString m_lastError;
};

#endif // PLUGIN_H
