#pragma once

#include <QtCore>

class IPluginHandler
{
public:
	/**
	   @brief Load plugin and make it available at Instance() method.
	   @return Is load succeeed. If not error message became available at GetLastError().
	 */
	virtual bool load() = 0;
	/**
	   @brief Unload plugin from system and destroy it's instance.
	   @return Is unload succeed. If not error message became available at GetLastError().
	 */
	virtual bool unload() = 0;
	/**
	   @brief Last error thrown by this plugin.
	   @return Error string.
	 */
	virtual QString getLastError() = 0;
	/**
	   @brief Loaded instance of plugin. If plugin not loaded yet returns nullptr.
	   @return Instance of plugin.
	 */
	virtual QObject *getInstance() = 0;
	/**
	   @brief Returns meta info of plugin. Available even if plugin not loaded.
	   @return Meta info of plugin in JSON format.
	 */
	virtual QWeakPointer<QJsonObject> getMeta() = 0;
	/**
	   @brief Returns unique id of plugin that could be used to identify plugin inside system.
	   @return unique id.
	 */
	virtual quint32 getUID() = 0;
	/**
	   @brief Returns file name of this plugin.
	   @return file name.
	 */
	virtual QString getFileName() = 0;

protected:
	virtual ~IPluginHandler() = default;
};
using IPluginHandlerPtr = QWeakPointer<IPluginHandler>;



