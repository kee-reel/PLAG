#ifndef VIEWPLUGINBASE_H
#define VIEWPLUGINBASE_H

#include <QtGlobal>
#include <QObject>
#include <QJsonObject>

#include "plugin_base.h"

//! \brief This interface provides basic methods for all plugins.
class ViewPluginBase : public PluginBase
{
    Q_OBJECT
public:
    PluginBase() {}
    virtual ~PluginBase() override {}

    virtual bool setupMetaInfo(const MetaInfo& metaInfo, const QJsonObject& metaInfoJsonObject) override;

    //! \brief Gets last error message from plugin.
    virtual QString getLastError() override;
    virtual const MetaInfo& getPluginMetaInfo() override;

    virtual bool addReferencePlugin(const IPlugin *referencePlugin) override;
    virtual bool open(const IPlugin *openedByPlugin) override;
    virtual bool close(const IPlugin *closedByPlugin) override;

public slots:
    virtual void referencePluginClosed(const PluginBase *closedReference);

signals:
    void onClose(const PluginBase *plugin);

private:
    QString m_lastErrorString;
    MetaInfo m_metaInfo;
};

#endif // VIEWPLUGINBASE_H


