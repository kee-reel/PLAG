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

#include "interfaces.h"

class PluginLoader : QObject
{
    Q_OBJECT
    QString packageName = "com.MASS";
public:
    explicit PluginLoader(QWidget *parent = 0);
    ~PluginLoader();

    QMap<QString, PluginTypes> pluginTypesNames;

private:
    QWidget* parent;
    IRootModelPlugin* rootModel;

    // Link structs
    QMap<IRootModelPlugin*, MetaInfo*> rootModelMap;

    QMap<IModelPlugin*, MetaInfo*>          pluginModelMap;
    QMap<IViewPlugin*, MetaInfo*>           pluginViewMap;
    QMap<IDataSourcePlugin*, MetaInfo*>     dataSourceMap;
    QMap<IDataManagerPlugin*, MetaInfo*>    dataManagerMap;

    QDir internalPluginsPath;

    void LoadPluginsToHome();
    bool SetupPlugin(QString pluginName);
    QPluginLoader* LoadPlugin(QString pluginName);
    QObject* GetPluginInstance(QPluginLoader* loader);
    MetaInfo *GetPluginMeta(QPluginLoader* loader);
    bool BindPluginToSystem(QObject* instance, MetaInfo *meta);

    template<class Type>
    Type *CastToPlugin(QObject* possiblePlugin);

    void SetupPluginsConnections();

public slots:
    void SetupPlugins();

signals:
    void OnAllSetup(bool isSucced);
};

#endif // PLUGINMANAGER_H
