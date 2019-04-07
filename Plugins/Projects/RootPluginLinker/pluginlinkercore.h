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
#include "../../Common/plugin_base.h"

#include "../../Interfaces/ipluginlinker.h"
#include "../../Interfaces/iuimanager.h"

#include "linkeritem.h"

//! \ingroup MainMenuPlugin_imp
//! @{
class PluginLinkerCore : public
        PluginBase,
        ICorePlugin,
        IPluginLinker
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IPlugin
        ICorePlugin
        IPluginLinker
    )

public:
    PluginLinkerCore();
    virtual ~PluginLinkerCore() override;

    // ICorePlugin interface
public:
    virtual void addPlugins(const QVector<QWeakPointer<IPluginHandler> > &pluginHandlers) override;
    virtual void start(QWeakPointer<IPluginHandler> selfHandler, QWidget *parentWidget) override;
    virtual bool close() override;

    // IPlugin interface
public:
    virtual QWidget *getWidget() override;

    // IPluginLinker interface
public:
    virtual bool addCorePlugin(QWeakPointer<IPluginHandler> pluginHandler) override;
    virtual bool addPlugin(QWeakPointer<IPluginHandler> pluginHandler) override;
    virtual bool setupLinks() override;

    virtual int getCorePluginUID() override;
    virtual QMap<int, QWeakPointer<ILinkerItem> > getPluginsMap() override;

signals:
    void onLinkageFinished();

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

    QWidget *m_parentWidget;
    QSharedPointer<LinkerItem> m_corePlugin;
    QMap<QString, QSharedPointer<LinkerItem>> m_interfacesMap;
    QMap<int, QSharedPointer<LinkerItem>> m_linkerItemsMap;
    int m_pluginUidCounter;
};
//! @}
#endif // PLUGINLINKER_H
