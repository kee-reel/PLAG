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
#include "../../Common/plugin_base.h"

#include "../../Interfaces/ipluginlinker.h"

class LinkerItem :
    public QObject,
    public IPluginLinker::ILinkerItem
{
    Q_OBJECT
public:
    LinkerItem(QWeakPointer<IPluginHandler> pluginHandler, QSharedPointer<MetaInfo> metaInfo, int uid);
    virtual ~LinkerItem() override {}

    // ILinkerItem interface
public:
    virtual bool isLoaded() const override;
    virtual bool isOpened() const override;
    virtual MetaInfo getMeta() const override;
    virtual int getPluginUID() const override;

    virtual QWidget *getWidget() const override;
    virtual const QObject *getObject() const override;

    virtual QMap<int, QWeakPointer<IPluginLinker::ILinkerItem> > getReferences() override;
    virtual QMap<int, QWeakPointer<IPluginLinker::ILinkerItem> > getReferents() override;

    virtual bool open() override;
    virtual bool close() override;

    const QString getPluginDescriptionName();

signals:
    void onLoaded(int itemId);
    void onOpened(int itemId);
    void onClosed(int itemId);
    void onConnectionsChanged(int itemId);

public:
    const QString &getInterfaceName();
    const QList<QString> &getReferenceNamesList();
    void addReference(QWeakPointer<LinkerItem> linkItem);
    void removeReference(QWeakPointer<LinkerItem> linkItem);
    void addReferent(QWeakPointer<LinkerItem> linkItem);
    void removeReferent(QWeakPointer<LinkerItem> linkItem);
    bool load();
    bool loadAllConnected();
    bool unload();

private:
    bool initPlugin();
    IPlugin *getPluginInstance() const;
    bool loadReferencePlugins();
    bool unloadReferencePlugins();
    void unloadItems(const QList<QWeakPointer<LinkerItem> > &loadedItemsList);

private slots:
    void onInstanceOpenSlot();
    void onInstanceCloseSlot();
    void onReferenceLoaded(int referenceId);

private:
    IPlugin *m_pluginInstance;
    QObject *m_pluginQObject;
    bool m_isReferencesLoaded;
    bool m_isOpened;

    QWeakPointer<IPluginHandler> m_pluginHandler;
    MetaInfo m_metaInfo;
    QString m_descriptionName;
    QMap<int, QWeakPointer<LinkerItem>> m_references;
    QMap<int, QWeakPointer<LinkerItem>> m_referents;
    int m_pluginUID;
};

#endif // LINKERITEM_H
