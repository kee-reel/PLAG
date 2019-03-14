#ifndef PLUGINLINKER_H
#define PLUGINLINKER_H

#include <QtCore>
#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

#include <QMap>
#include <QHash>

#include "../../PluginsInterfaces/ipluginlinker.h"

#include "../../../Application/icoreplugin.h"
#include "../../PluginsCommon/plugin_base.h"

#include "linkeritem.h"

//! \ingroup MainMenuPlugin_imp
//! @{
class PluginLinker : public
        PluginBase,
        IPluginLinker
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IPlugin
        IPluginLinker
    )

public:
    PluginLinker();
    virtual ~PluginLinker() override;

    // IPluginLinker interface
public:
    virtual bool addCorePlugin(QWeakPointer<IPluginHandler> pluginHandler) override;
    virtual bool addPlugin(QWeakPointer<IPluginHandler> pluginHandler) override;
    virtual bool setupLinks() override;

    virtual int getCorePluginUID() override;
    virtual QMap<int, QWeakPointer<ILinkerItem> > getPluginsMap() override;

    QWeakPointer<LinkerItem> getCorePlugin();
    QMap<QString, QWeakPointer<LinkerItem> > &getClildPluginsMap();
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
