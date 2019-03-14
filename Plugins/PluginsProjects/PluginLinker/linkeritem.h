#ifndef LINKERITEM_H
#define LINKERITEM_H

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
#include "../../PluginsInterfaces/ipluginlinker.h"

class LinkerItem :
    public QObject,
    public IPluginLinker::ILinkerItem
{
    Q_OBJECT
public:
    LinkerItem(QWeakPointer<IPluginHandler> pluginHandler, QSharedPointer<MetaInfo> metaInfo, int uid);
    virtual ~LinkerItem() override {}

    const QString &getInterfaceName();
    const QList<QString> &getReferenceNamesList();
    void addReference(QWeakPointer<LinkerItem> linkItem);
    void removeReference(QWeakPointer<LinkerItem> linkItem);
    void addReferent(QWeakPointer<LinkerItem> linkItem);
    void removeReferent(QWeakPointer<LinkerItem> linkItem);
    bool load();
    bool unload();
    bool open(const IPlugin *pluginInstance);

private:
    IPlugin *getPluginInstance() const;
    bool loadReferencePlugins();
    bool unloadReferencePlugins();
    void unloadItems(const QList<QWeakPointer<LinkerItem> > &loadedItemsList);

private slots:
    void onInstanceOpenSlot(const IPlugin *openedByPlugin);
    void onInstanceCloseSlot(const IPlugin *closedByPlugin);

    // ILinkerItem interface
public:
    virtual bool isLoaded() const override;
    virtual bool isOpened() const override;
    virtual MetaInfo getMeta() const override;
    virtual int getPluginUID() const override;

    virtual QWidget *getWidget() const override;
    virtual const QObject *getObject() const override;

    virtual QVector<QWeakPointer<ILinkerItem>> getReferences() override;
    virtual QVector<QWeakPointer<ILinkerItem>> getReferents() override;

    virtual bool open(QWeakPointer<ILinkerItem> openedByElement) override;
    virtual bool close(QWeakPointer<ILinkerItem> closedByElement) override;

    const QString getPluginDescriptionName();
signals:
    void onItemOpened(int selfId);
    void onItemClosed(int selfId);
    void onItemConnectionsChanged(int selfId);

private:
    IPlugin *m_pluginInstance;
    QObject *m_pluginQObject;
    bool m_isOpened;

    QWeakPointer<IPluginHandler> m_pluginHandler;
    MetaInfo m_metaInfo;
    QString m_descriptionName;
    QMap<int, QWeakPointer<LinkerItem>> m_references;
    QMap<int, QWeakPointer<LinkerItem>> m_referents;
    int m_pluginUID;
};

#endif // LINKERITEM_H
