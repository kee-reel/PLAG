#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QApplication>
#include <QDebug>
#include <QString>
#include <QWidget>
#include <QObject>
#include <QPluginLoader>
#include <QDir>
#include <QStandardPaths>
#include <QtSql>

#include "icoreplugin.h"

//! \addtogroup MASS MASS
//! @{

//! \brief Loads all files from directory and tries to specify
//! between them plugin with interface RootModel and initialize it.
class PluginLoader : QObject
{
    Q_OBJECT
    QString packageName = "com.mass";
    QString pluginsSubdirName = "Plugins";
public:
    //!
    //! \param parent QWidget which will be parent for all application windows.
    //!
    explicit PluginLoader(QWidget *parent = 0);
    ~PluginLoader();

private:
    QWidget* parent;
    ICorePlugin* corePlugin;

    QMap<QString, ICorePlugin*> corePlugins;
    QMap<QObject*, QJsonObject> pluginInstances;

    QDir internalPluginsPath;

    void LoadPluginsToHome();
    void LoadFilesFromDirectory(QDir directory, QDir dstDirectory);
    bool SetupPlugin(QString pluginName);
    QPluginLoader* LoadPlugin(QString pluginName);
    QObject* GetPluginInstance(QPluginLoader* loader);
    void BindPluginToSystem(QObject* instance, QPluginLoader* loader);

    template<class Type>
    Type *CastToPlugin(QObject* possiblePlugin);

    bool SetupPluginsConnections();

public slots:
    ///
    //! \brief Load plugins from specified folder. In loaded files tries to specify RootModel plugin.
    //! If it exists - set this plugin as rootModel and send to it all unspecified plugins.
    /// \return Is core plugin found
    ///
    bool SetupPlugins();
    ///
    /// \brief Calls Run method on selected core plugin.
    ///
    void RunCorePlugin();
};
//! @}
#endif // PLUGINMANAGER_H
