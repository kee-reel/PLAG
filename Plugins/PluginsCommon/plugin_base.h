#ifndef PLUGINBASE_H
#define PLUGINBASE_H

#include <QtCore>
#include <QObject>
#include <QWidget>
#include <QJsonObject>
#include <QMap>

#include "iplugin.h"

#if defined(PLUGIN_BASE_QOBJECT)
#define PLUGIN_BASE_PARENT QObject

#elif defined(PLUGIN_BASE_QWIDGET)
#define PLUGIN_BASE_PARENT QWidget

namespace Ui
{
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
    PluginBase(QWidget *parent = nullptr);

#endif

    virtual ~PluginBase() override {}

public:
    virtual bool init(const MetaInfo &metaInfo, const QJsonObject &metaInfoJsonObject) override;
    virtual bool addReferencePlugin(IPlugin *referencePlugin) override;
    virtual bool removeReferencePlugin(IPlugin *referencePlugin) override;

    virtual QString getLastError() const override;
    virtual const MetaInfo &getPluginMetaInfo() const override;
    virtual QObject *getObject() override;
    virtual QWidget *getWidget() override;

    virtual bool open(const IPlugin *openedByPlugin) override;
    virtual bool close(const IPlugin *closedByPlugin) override;

signals:
    void onOpen(const IPlugin *openedByPlugin);
    void onClose(const IPlugin *closedByPlugin);

protected:
    void constructorInit();
    void raiseError(QString errorMessage);
    void checkAllReferencesSet();
    QString getPluginDescription(const MetaInfo &meta);
    virtual void onAllReferencesSetStateChanged();
    template<class T>
    T *castPluginToInterface(IPlugin *possiblePlugin)
    {
        if(!possiblePlugin)
        {
            qCritical() << "PluginBase::castPluginToInterface: possiblePlugin is nullptr.";
            return nullptr;
        }
        QObject *object = possiblePlugin->getObject();
        T *plugin = qobject_cast<T *>(object);

        if(!plugin)
        {
            auto &&meta = possiblePlugin->getPluginMetaInfo();
            qCritical() << QString("Can't cast plugin %1 to interface %2.").arg(meta.Name).arg(meta.InterfaceName);
        }

        return plugin;
    }

protected:
    QMap<QString, IPlugin *> m_referencesMap;
    QString m_lastErrorString;
    MetaInfo m_metaInfo;

    bool m_isInited;
    bool m_isAllReferencesSet;

#if defined(PLUGIN_BASE_QWIDGET)
protected:
    QSharedPointer<Ui::Form> ui;
#endif
};
#endif // PLUGINBASE_H


