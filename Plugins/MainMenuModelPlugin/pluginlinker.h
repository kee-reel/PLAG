#ifndef PLUGINLINKER_H
#define PLUGINLINKER_H

#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

#include <QMap>
#include <QHash>

#include "interfaces.h"
#include "imainmenumodule.h"

//! \ingroup MainMenuPlugin_imp
//! @{
class PluginLinker
{
public:
    PluginLinker();

    void AddNewPlugin(QObject* instance, QJsonObject* meta);
    IMainMenuPluginModel::MenuItem *SetupLinks();

    IModelPlugin *rootModel;
    IMainMenuPluginModel::MenuItem *rootMenuItem;
    QMap<MetaInfo*, IMainMenuPluginModel::MenuItem*> menuItems;

    QMap<IModelPlugin*, MetaInfo*>          modelMap;
    QMap<IViewPlugin*, MetaInfo*>           viewMap;
    QMap<IDataSourcePlugin*, MetaInfo*>     sourceMap;
    QMap<IDataManagerPlugin*, MetaInfo*>    managerMap;

private:
    QMap<QString, PluginTypes> pluginTypesNames;

    QHash<QString, QVector<IDataManagerPlugin*> > sourceToManagersLink;
    QHash<QString, QVector<IModelPlugin*> >       managerToModelsLink;
    QHash<QString, QVector<IModelPlugin*> >       modelToModelsLink;
    QHash<QString, QVector<IViewPlugin*> >        modelToViewsLink;

    template <class T>
    struct LinkInfo
    {
        T *plugin;
        QObject *instance;
    };
    QHash<QString, LinkInfo<IDataSourcePlugin> >  dataSourcesLinkInfo;
    QHash<QString, LinkInfo<IDataManagerPlugin> > dataManagersLinkInfo;
    QHash<QString, LinkInfo<IModelPlugin> >       modelsLinkInfo;
    QHash<QString, LinkInfo<IViewPlugin> >        viewsLinkInfo;

    MetaInfo *GetPluginMeta(QJsonObject* metaData);
    bool BindPluginToSystem(QObject* instance, MetaInfo *meta);
    void CallOnAllSetup();

    void SetLinks(IDataSourcePlugin* plugin, QObject* instance, MetaInfo *meta);
    void SetLinks(IDataManagerPlugin* plugin, QObject* instance, MetaInfo *meta);
    void SetLinks(IModelPlugin* plugin, QObject* instance, MetaInfo *meta);
    void SetLinks(IViewPlugin* plugin, QObject* instance, MetaInfo *meta);

    void LinkSourceToManagers();
    void LinkManagerToModels();
    void LinkModelToModels();
    void LinkModelToViews();

    template<class Type>
    Type *CastToPlugin(QObject* possiblePlugin);
};
//! @}
#endif // PLUGINLINKER_H
