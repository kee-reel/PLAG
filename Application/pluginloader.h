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
#include "ipluginhandler.h"

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
    explicit PluginLoader(QWidget *m_parent = nullptr);
    ~PluginLoader();

public slots:
    ///
    //! \brief Load plugins from specified folder. In loaded files tries to specify RootModel plugin.
    //! If it exists - set this plugin as rootModel and send to it all unspecified plugins.
    /// \return Is core plugin found
    ///
    bool setupPlugins();
    ///
    /// \brief Calls Run method on selected core plugin.
    ///
    void runCorePlugin();

private:
    void loadPluginsToHome();
    void loadFilesFromDirectory(QDir directory, QDir dstDirectory);
    bool setupPlugin(QString pluginName);

    template<class Type>
    Type *castToPlugin(QObject* possiblePlugin);

private:
    QWidget* m_parent;
    QSharedPointer<ICorePlugin> m_corePlugin;

    QList<QSharedPointer<IPluginHandler>> m_pluginHandlers;
    QList<QSharedPointer<IPluginHandler>> m_corePluginHandlers;

    QDir m_internalPluginsPath;

};
//! @}
#endif // PLUGINMANAGER_H
