#ifndef PLUGINHANDLER_H
#define PLUGINHANDLER_H

#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

#include <QMap>
#include <QHash>

#include "interfaces.h"

class PluginHandler
{
public:
    PluginHandler(PluginInfo<IDataSourcePlugin> *dataSource);
    PluginHandler(PluginInfo<IDataManagerPlugin> *dataManager);
    PluginHandler(PluginInfo<IModelPlugin> *model);
    PluginHandler(PluginInfo<IViewPlugin> *view);

    static void Init(QHash<QString, QList<PluginHandler *>> *handlersWithReferencesNames,
            QHash<QString, QList<PluginHandler *>> *handlersWithSelfNames);
    void SetupRelations();
    static QHash<QString, QList<PluginHandler*>> *handlersWithReferencesNames;
    static QHash<QString, QList<PluginHandler*>> *handlersWithSelfNames;

private:
    PluginTypes unionType;
    union PluginInfoUnion{
        PluginInfo<IDataSourcePlugin> *dataSource;
        PluginInfo<IDataManagerPlugin> *dataManager;
        PluginInfo<IModelPlugin> *model;
        PluginInfo<IViewPlugin> *view;
    } pluginInfo;

    void InsertIntoHashes();
};

#endif // PLUGINHANDLER_H
