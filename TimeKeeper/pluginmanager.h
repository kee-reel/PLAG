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

#include "interfaces.h"
class PluginManager : QObject
{
    Q_OBJECT
public:
    explicit PluginManager(QWidget *parent = 0);
    ~PluginManager();

    QMap<QString, PluginTypes> pluginTypesNames;

private:
    QWidget* parent;
    IPluginModel* mainPlugin;
    IDBManagerPlugin* DBManager;


    QMap<IPluginModel*, MetaInfo*> pluginModelMap;
    //QMap<IPluginModel*, QObject*> pluginModelInstancesMap;

    QMap<IPluginView*, MetaInfo*> pluginViewMap;
    QMap<IPluginModel*, MetaInfo*> mainPluginMap;
    QMap<IDBManagerPlugin*, MetaInfo*> DBManagerMap;
    QMap<IDBToolPlugin*, MetaInfo*> DBToolMap;

    QHash<QString, IPluginModel*> pluginModelNameHash;
    QHash<QString, IPluginModel*> pluginModelParentNameHash;
    QHash<QString, IPluginView*> pluginViewParentNameHash;

    //DBTools
    QHash<QString, QObject*> DBToolNameHash;
    QHash<QString, IPluginModel*> pluginDBToolNameHash;

public slots:
    void SetupPlugins();

signals:
    void OnAllSetup(bool isSucced);

private:
    bool SetupPlugin(QString pluginName);
    QPluginLoader* LoadPlugin(QString pluginName);
    QObject* GetPluginInstance(QPluginLoader* loader);
    MetaInfo *GetPluginMeta(QPluginLoader* loader);
    bool BindPluginToSystem(QPluginLoader* loader, QObject* possiblePlugin, MetaInfo *moduleMeta);

    template<class Type>
    Type *CastToPlugin(QPluginLoader* loader, QObject* possiblePlugin);

    void SetupPluginsConnections();
};

#endif // PLUGINMANAGER_H
