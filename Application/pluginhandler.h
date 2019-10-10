#ifndef PLUGIN_H
#define PLUGIN_H

#include <QFile>
#include <QPluginLoader>
#include <QtGlobal>

#include "ipluginhandler.h"

class PluginHandler : public IPluginHandler
{
    const QString META_DATA_CORE_FLAG = "isCorePlugin";

public:
    PluginHandler(uid_t uid, QString m_filename, QObject *m_parent = nullptr);
    virtual ~PluginHandler() override {}

    // IPlugin interface
public:
    virtual bool load() override;
    virtual bool unload() override;
    virtual QString getLastError() override;
    virtual QObject *getInstance() override;
    virtual QWeakPointer<QJsonObject> getMeta() override;
    virtual uid_t getUID() override;
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
