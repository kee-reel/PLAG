#ifndef I_PLUGIN_HANDLER_H
#define I_PLUGIN_HANDLER_H

class QObject;
class QJsonObject;
class QString;

class IPluginHandler
{
    // IPlugin interface
public:
    virtual ~IPluginHandler() = default;
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
    virtual const QJsonObject& getMeta() = 0;
};

#endif // I_PLUGIN_HANDLER_H
