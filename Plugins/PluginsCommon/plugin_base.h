#ifndef PLUGINBASE_H
#define PLUGINBASE_H

#include <QtGlobal>
#include <QObject>
#include <QJsonObject>
#include <QMap>

#include "iplugin.h"

//! \brief This interface provides basic methods for all plugins.
class PluginBase : public QObject, public IPlugin
{
    Q_OBJECT
public:
    PluginBase() {}
    virtual ~PluginBase() override {}

public:
    virtual bool init(const MetaInfo &metaInfo, const QJsonObject &metaInfoJsonObject) override;

    virtual bool addReferencePlugin(const IPlugin *referencePlugin) override;
    virtual bool removeReferencePlugin(const IPlugin *referencePlugin) override;

    virtual bool open(const IPlugin *openedByPlugin) override;
    virtual bool close(const IPlugin *closedByPlugin) override;

    virtual QString getLastError() const override;
    virtual const MetaInfo &getPluginMetaInfo() const override;

protected:

public slots:
    virtual void referencePluginClosed(const PluginBase *closedReference);

signals:
    void onClose(const PluginBase *plugin);

private:
    void raiseError(QString errorMessage);

private:
    QMap<QString, bool> m_installedReferencesMap;
    QString m_lastErrorString;
    MetaInfo m_metaInfo;
};
#endif // PLUGINBASE_H


