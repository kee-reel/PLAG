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

class PluginManager : QObject
{
    Q_OBJECT
    QString packageName = "com.MASS";
public:
    explicit PluginManager(QWidget *parent = 0);
    ~PluginManager();

    QMap<QString, PluginTypes> pluginTypesNames;

private:
    QWidget* parent;
    IPluginModel* mainPlugin;
    IDataSourcePlugin* mainDataSource;

    // Link structs
    template <class T>
    struct LinkInfo
    {
        T *plugin;
        QObject *instance;
    };

    QMap<IPluginModel*, MetaInfo*> pluginModelMap;
    QMap<IPluginView*, MetaInfo*> pluginViewMap;
    QMap<IPluginModel*, MetaInfo*> mainPluginMap;
    QMap<IDataSourcePlugin*, MetaInfo*> dataSourceMap;
    QMap<IDataManagerPlugin*, MetaInfo*> dataManagerMap;

    QHash<QString, LinkInfo<IDataSourcePlugin>>     dataSourcesLinkInfo;
    QHash<QString, LinkInfo<IDataManagerPlugin>>    dataManagersLinkInfo;
    QHash<QString, LinkInfo<IPluginModel>>          modelsLinkInfo;
    QHash<QString, LinkInfo<IPluginView>>           viewsLinkInfo;

    QHash<QString, QVector<IDataManagerPlugin*>> sourceToManagersLink;
    QHash<QString, QVector<IPluginModel*>>       managerToModelsLink;
    QHash<QString, QVector<IPluginModel*>>       modelToModelsLink;
    QHash<QString, QVector<IPluginView*>>        modelToViewsLink;

    QDir internalPluginsPath;

    void LoadPluginsToHome();
    bool SetupPlugin(QString pluginName);
    QPluginLoader* LoadPlugin(QString pluginName);
    QObject* GetPluginInstance(QPluginLoader* loader);
    MetaInfo *GetPluginMeta(QPluginLoader* loader);
    bool BindPluginToSystem(QPluginLoader* loader, QObject* instance, MetaInfo *meta);

    template<class Type>
    Type *CastToPlugin(QPluginLoader* loader, QObject* possiblePlugin);
    void LinkSourceToManagers();
    void LinkManagerToModels();
    void LinkModelToModels();
    void LinkModelToViews();

    void SetDataSourceLinks(IDataSourcePlugin* plugin, QObject *instance, MetaInfo *meta);
    void SetDataManagerLinks(IDataManagerPlugin* plugin, QObject *instance, MetaInfo *meta);
    void SetPluginModelLinks(IPluginModel* plugin, QObject *instance, MetaInfo *meta);
    void SetPluginViewLinks(IPluginView* plugin, QObject *instance, MetaInfo *meta);

    void SetupPluginsConnections();


public slots:
    void SetupPlugins();

signals:
    void OnAllSetup(bool isSucced);
};

#endif // PLUGINMANAGER_H
