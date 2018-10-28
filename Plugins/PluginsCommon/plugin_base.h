#ifndef PLUGINBASE_H
#define PLUGINBASE_H

#include <QtGlobal>
#include <QObject>
#include <QWidget>
#include <QJsonObject>
#include <QMap>

#include "iplugin.h"


#if defined(PLUGIN_BASE_QOBJECT)
#define PLUGIN_BASE_PARENT QObject

#elif defined(PLUGIN_BASE_QWIDGET)
#define PLUGIN_BASE_PARENT QWidget

namespace Ui {
    class Form;
}

#elif defined(PLUGIN_BASE_QWIDGET_QML)
#define PLUGIN_BASE_PARENT QObject

#endif

//! \brief This interface provides basic methods for all plugins.
class PluginBase : public PLUGIN_BASE_PARENT, public IPlugin
{
    Q_OBJECT
public:
#if defined(PLUGIN_BASE_QOBJECT)
    explicit PluginBase(QObject *parent = nullptr);

#elif defined(PLUGIN_BASE_QWIDGET)
    explicit PluginBase(QWidget *parent = nullptr);

#elif defined(PLUGIN_BASE_QWIDGET_QML)
    PluginBase();

#endif

    virtual ~PluginBase() override {}

public:
    virtual bool init(const MetaInfo &metaInfo, const QJsonObject &metaInfoJsonObject) override;
    virtual bool addReferencePlugin(const IPlugin *referencePlugin) override;
    virtual bool removeReferencePlugin(const IPlugin *referencePlugin) override;

    virtual QString getLastError() const override;
    virtual const MetaInfo &getPluginMetaInfo() const override;
    virtual QWidget *getWidget() override;

    virtual bool open(const IPlugin *openedByPlugin) override;
    virtual bool close(const IPlugin *closedByPlugin) override;

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

#if defined(PLUGIN_BASE_QWIDGET)
    QSharedPointer<Ui::Form> ui;
#endif
};
#endif // PLUGINBASE_H


