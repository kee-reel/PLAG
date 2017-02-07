#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QDebug>
#include <QString>
#include <QWidget>
#include <QPluginLoader>
#include <QDir>

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
    QMap<IPluginModel*, QObject*> pluginModelInstancesMap;

    QMap<IPluginView*, MetaInfo*> pluginViewMap;
    QMap<IPluginModel*, MetaInfo*> mainPluginMap;
    QMap<IDBManagerPlugin*, MetaInfo*> DBManagerMap;
    QMap<IDBToolPlugin*, MetaInfo*> DBToolMap;

    QHash<QString, IPluginModel*> pluginModelNameHash;
    QHash<QString, IPluginModel*> pluginModelParentNameHash;
    QHash<QString, IPluginView*> pluginViewParentNameHash;

public slots:
    void SetupPlugins();

signals:
    OnAllSetup(bool isSucced);

private:
    bool SetupPlugin(QString pluginName);
    QPluginLoader* LoadPlugin(QString pluginName);
    QObject* GetPluginInstance(QPluginLoader* loader);
    MetaInfo *GetPluginMeta(QPluginLoader* loader);
    bool BindPluginToSystem(QPluginLoader* loader, QObject* possiblePlugin, MetaInfo *moduleMeta);

    template<class Type>
    static Type *CastToPlugin(QPluginLoader* loader, QObject* possiblePlugin);
    bool CheckPluginWidget(IPluginModel* plugin);

    void SetupPluginsConnections();
};

#endif // PLUGINMANAGER_H
