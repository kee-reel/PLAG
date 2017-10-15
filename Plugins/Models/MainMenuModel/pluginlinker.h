#ifndef PLUGINLINKER_H
#define PLUGINLINKER_H

#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

#include <QMap>
#include <QHash>

#include "imainmenumodule.h"
#include "pluginhandler.h"

//! \ingroup MainMenuPlugin_imp
//! @{
class PluginLinker
{
public:
    PluginLinker();

    void AddNewPlugin(QObject* instance, QJsonObject* meta);
    IMainMenuModel::MenuItem *SetupLinks();

    IModelPlugin *rootModel;
    IMainMenuModel::MenuItem *rootMenuItem;
    QMap<MetaInfo*, PluginInfo*> menuItems;

    QList<PluginHandler*> pluginsHandlers;
    QList<PluginInfo*> pluginsInfo;

private:
    QHash<QString, QList<PluginHandler*> > handlersWithReferencesNames;
    QHash<QString, QList<PluginHandler*> > handlersWithSelfNames;

    QMap<QString, PluginTypes> pluginTypesNames;

    MetaInfo *GetPluginMeta(QJsonObject* metaData);
    bool BindPluginToSystem(QObject* instance, MetaInfo *meta);
    void CallOnAllSetup();

    template<class Type>
    Type *CastToPlugin(QObject* possiblePlugin);
};
//! @}
#endif // PLUGINLINKER_H
