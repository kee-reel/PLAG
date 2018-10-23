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
    const QList<QString>& getReferenceNamesList();
    void addReference(QWeakPointer<LinkerItem> linkItem);

    bool load();

    // IMenuItem interface
public:
    QWeakPointer<MetaInfo> getMeta();
    QVector<QWeakPointer<IMainMenuModel::IMenuItem> > getReferences();

private:
    void addReferent(QWeakPointer<LinkerItem> linkItem);

private:
    QWeakPointer<IPluginHandler> m_pluginHandler;
    QWeakPointer<MetaInfo> m_metaInfo;
    QList<QWeakPointer<LinkerItem>> m_referencesList;
    QList<QWeakPointer<LinkerItem>> m_referentsList;
};

#endif // PLUGINHANDLER_H
