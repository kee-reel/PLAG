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
#include "../../PluginsInterfaces/iuimanager.h"

class LinkerItem :
    public QObject,
    public IUIManager::IUIElement
{
    Q_OBJECT
public:
    LinkerItem(QWeakPointer<IPluginHandler> pluginHandler, QSharedPointer<MetaInfo> metaInfo, int uid);
    virtual ~LinkerItem() override {}

    const QString &getName();
    const QList<QString> &getReferenceNamesList();
    void addReference(QWeakPointer<LinkerItem> linkItem);
    void addReferent(QWeakPointer<LinkerItem> linkItem);
    void removeReference(QWeakPointer<LinkerItem> linkItem);
    bool load();
    bool unload();
    bool open(const IPlugin *pluginInstance);

private:
    IPlugin *getPluginInstance() const;
    bool prepareConnectedPlugins();
    void unloadItems(const QList<QWeakPointer<LinkerItem> > &loadedItemsList);

    // IUIElement interface
public:
    virtual bool isOpened() const override;
    virtual MetaInfo getMeta() const override;
    virtual int getElementId() const override;
    virtual QWidget *getElementWidget() const override;
    virtual const QObject *getElementSignalsLinkObject() const override;
    virtual QVector<QWeakPointer<IUIElement> > getConnectedElements() override;
    virtual bool open(QWeakPointer<IUIManager::IUIElement> openedByElement) override;
    virtual bool close(QWeakPointer<IUIManager::IUIElement> closedByElement) override;

signals:
    void onOpened(int selfId);
    void onClosed(int selfId);
    void onConnectionsChanged(int selfId);

private slots:
    void onOpenSlot(const IPlugin *openedByPlugin);
    void onCloseSlot(const IPlugin *closedByPlugin);

private:
    IPlugin *m_pluginInstance;
    QObject *m_pluginQObject;
    bool m_isOpened;

    QWeakPointer<IPluginHandler> m_pluginHandler;
    MetaInfo m_metaInfo;
    QMap<QString, QWeakPointer<LinkerItem>> m_references;
    QMap<QString, QWeakPointer<LinkerItem>> m_referents;
    ///
    /// \brief All linked items including references and referents.
    ///
    QMap<QString, QWeakPointer<LinkerItem>> m_connectedItems;
    int m_uiElementId;
};

#endif // PLUGINHANDLER_H
