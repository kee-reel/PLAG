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

    bool addNewPlugin(QWeakPointer<IPluginHandler> pluginHandler);
    bool setupLinks();

    const QMap<QString, QSharedPointer<LinkerItem>>& getPluginsMap();

private:
    template<class Type>
    Type *castToPlugin(QObject* possiblePlugin) const;
    QSharedPointer<MetaInfo> parseMetaInfo(const QJsonObject &metaInfoObject) const;

private:
    const QString META_FIELD_INTERFACE                  = "Interface";
    const QString META_FIELD_NAME                       = "Name";
    const QString META_FIELD_RELATED_PLUGIN_INTERFACES  = "RelatedPluginInterfaces";

private:
//    IModelPlugin *rootModel;
//    IMainMenuModel::MenuItem *rootMenuItem;
//    QMap<MetaInfo*, PluginInfo*> menuItems;

    QMap<QString, QSharedPointer<LinkerItem>> m_linkerItemsMap;
};
//! @}
#endif // PLUGINLINKER_H
