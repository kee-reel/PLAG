#ifndef PLUGIN_H
#define PLUGIN_H

#include <QFile>
#include <QPluginLoader>
#include <QtGlobal>

#include "ipluginhandler.h"

class PluginHandler : public IPluginHandler
{
    const QString META_DATA_CORE_FLAG = "IsCorePlugin";

public:
    PluginHandler(QString m_filename, QObject *m_parent = nullptr);
    virtual ~PluginHandler() override {}

    // IPlugin interface
public:
    /**
       @brief Load plugin and make it available at Instance() method.
       @return Is load succeeed. If not error message became available at GetLastError().
     */
    virtual bool load() override;
    /**
       @brief Unload plugin from system and destroy it's instance.
       @return Is unload succeed. If not error message became available at GetLastError().
     */
    virtual bool unload() override;
    /**
       @brief Last error thrown by this plugin.
       @return Error string.
     */
    virtual QString getLastError() override;
    /**
       @brief Loaded instance of plugin. If plugin not loaded yet returns nullptr.
       @return Instance of plugin.
     */
    virtual QObject *getInstance() override;
    /**
       @brief Returns meta info of plugin. Available even if plugin not loaded.
       @return Meta info of plugin in JSON format.
     */
    virtual const QJsonObject &getMeta() override;
    /**
       @brief Flag that indicates that plugin meta says that it is core plugin.
       @return Is this core plugin.
     */
    bool isCorePlugin();

private:
    QObject *m_instance;
    QSharedPointer<QPluginLoader> m_pluginLoader;
    QJsonObject m_meta;
    QString m_lastError;
};

#endif // PLUGIN_H
