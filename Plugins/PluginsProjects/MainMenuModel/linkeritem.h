#ifndef PLUGINHANDLER_H
#define PLUGINHANDLER_H

#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

#include <QList>
#include <QMap>
#include <QHash>

#include "../../../Application/icoreplugin.h"
#include "../../PluginsCommon/plugin_base.h"
#include "../../PluginsInterfaces/imainmenumodule.h"

class LinkerItem : public IMainMenuModel::IMenuItem
{
public:
    LinkerItem(QWeakPointer<IPluginHandler> pluginHandler, QSharedPointer<MetaInfo> metaInfo);
    virtual ~LinkerItem() {}

    const QString& getName();
    const QList<QString> &getReferenceNamesList();
    void addReference(QWeakPointer<LinkerItem> linkItem);
    void removeReference(QWeakPointer<LinkerItem> linkItem);

    bool load();
    bool unload();

    bool open(const QWidget *parent);

    // IMenuItem interface
public:
    const MetaInfo &getMeta();
    QVector<QWeakPointer<IMainMenuModel::IMenuItem> > getReferences();

private:
    void addReferent(QWeakPointer<LinkerItem> linkItem);
    const IPlugin *getPluginInstance();

private:
    IPlugin* m_plugin;
    QWeakPointer<IPluginHandler> m_pluginHandler;
    MetaInfo m_metaInfo;
    QMap<QString, QWeakPointer<LinkerItem>> m_references;
    QMap<QString, QWeakPointer<LinkerItem>> m_referents;
};

#endif // PLUGINHANDLER_H
