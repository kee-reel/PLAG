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

#include "iapplication.h"
#include "icoreplugin.h"
#include "ipluginhandler.h"

class PluginHandler;

//! \brief Loads all files from directory and tries to specify
//! between them plugin with interface RootModel and initialize it.
class PluginLoader : public QObject, public IApplication
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
    ///
    /// \brief Calls Run method on selected core plugin.
    ///
    bool closePlugins();

    // IApplication interface
public:
    virtual QWidget *getParentWidget() override;
    virtual QVector<IPluginHandlerPtr > getPlugins() override;
    virtual IPluginHandlerPtr makePluginHandler(QString path) override;

private:
    void loadPluginsToHome();
    void loadFilesFromDirectory(QDir directory, QDir dstDirectory);
    void registerPlugin(QSharedPointer<PluginHandler> handler);
    QSharedPointer<PluginHandler> makePluginHandlerPrivate(QString path);

    template<class Type>
    Type *castToPlugin(QObject *possiblePlugin);

private:
    QWidget *m_parent;
    QSharedPointer<PluginHandler> m_corePluginHandler;
    ICore* m_corePluginInstance;
    uid_t m_uidGeneratorCounter;

    QList<QSharedPointer<PluginHandler>> m_pluginHandlers;
    QList<QSharedPointer<PluginHandler>> m_corePluginHandlers;

    QDir m_internalPluginsPath;
};
#endif // PLUGINMANAGER_H
