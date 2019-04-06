#ifndef IPLUGIN_H
#define IPLUGIN_H

#include <QtCore>
#include <QObject>
#include <QJsonObject>

//! \brief Holds basic information about plugin.
struct MetaInfo
{
    //! \brief Type of plugin.
    //! \brief Name of plugin interface.
    QString InterfaceName;
    //! \brief Plugin name.
    QString Name;
    //! \brief Name of parent plugin.
    QList<QString> RelatedPluginNames;
};

//! \brief This interface provides basic methods for all plugins.
class IPlugin
{
public:
    virtual bool init(const MetaInfo &metaInfo, const QJsonObject &metaInfoJsonObject) = 0;
    virtual bool addReferencePlugin(IPlugin *referencePlugin) = 0;
    virtual bool removeReferencePlugin(IPlugin *referencePlugin) = 0;

    //! \brief Gets last error message from plugin.
    virtual QString getLastError() const = 0;
    virtual const MetaInfo &getPluginMetaInfo() const = 0;
    virtual QObject *getObject() = 0;
    virtual QWidget *getWidget() = 0;
    virtual bool isReady() = 0;

    virtual bool open() = 0;
    virtual bool close() = 0;

public slots:
    virtual void onReferenceReady(IPlugin* reference) = 0;

signals:
    void onReady(IPlugin*);
    void onOpen(IPlugin*);
    void onClose(IPlugin*);
};
Q_DECLARE_INTERFACE(IPlugin, "IPlugin")
#endif // IPLUGIN_H
