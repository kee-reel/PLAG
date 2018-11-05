#ifndef PLUGINLINKER_H
#define PLUGINLINKER_H

#include <QtCore>
#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

#include <QMap>
#include <QHash>

#include "../../../Application/icoreplugin.h"
#include "../../PluginsCommon/plugin_base.h"

#include "linkeritem.h"

//! \ingroup MainMenuPlugin_imp
//! @{
class PluginLinker
{
public:
    PluginLinker();

    bool addCorePlugin(QWeakPointer<IPluginHandler> pluginHandler);
    bool addNewPlugin(QWeakPointer<IPluginHandler> pluginHandler);
    bool setupLinks();

    const QWeakPointer<LinkerItem> getCorePlugin();
    const QMap<QString, QWeakPointer<LinkerItem> > getClildPluginsMap();
    const QMap<QString, QWeakPointer<LinkerItem> > getAllPluginsMap();

private:
    template<class Type>
    Type *castToPlugin(QObject *possiblePlugin) const;
    QSharedPointer<MetaInfo> parseMetaInfo(const QJsonObject &metaInfoObject) const;
    QSharedPointer<LinkerItem> createLinkerItem(QWeakPointer<IPluginHandler>);

private:
    const QString META_FIELD_INTERFACE                  = "Interface";
    const QString META_FIELD_NAME                       = "Name";
    const QString META_FIELD_RELATED_PLUGIN_INTERFACES  = "RelatedPluginInterfaces";

private:
    //    IModelPlugin *rootModel;
    //    IMainMenuModel::MenuItem *rootMenuItem;
    //    QMap<MetaInfo*, PluginInfo*> menuItems;

    QSharedPointer<LinkerItem> m_corePlugin;
    QMap<QString, QSharedPointer<LinkerItem>> m_linkerItemsMap;
    int m_pluginUidCounter;
};
//! @}
#endif // PLUGINLINKER_H
