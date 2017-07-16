#ifndef PLUGINHANDLER_H
#define PLUGINHANDLER_H

#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

#include <QList>
#include <QMap>
#include <QHash>

#include "interfaces.h"

class PluginHandler
{
public:
    PluginHandler(PluginInfo *pluginInfo);

    static void Init(QHash<QString, QList<PluginHandler *>> &handlersWithReferencesNames,
            QHash<QString, QList<PluginHandler *>> &handlersWithSelfNames);
    void SetupRelations();
    static QHash<QString, QList<PluginHandler*>> *handlersWithReferencesNames;
    static QHash<QString, QList<PluginHandler*>> *handlersWithSelfNames;

private:
    void InsertIntoHashes();

    PluginInfo *pluginInfo;
};

#endif // PLUGINHANDLER_H
