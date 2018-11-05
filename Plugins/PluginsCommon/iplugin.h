#ifndef IPLUGIN_H
#define IPLUGIN_H

#include <QtGlobal>
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

    virtual bool open(const IPlugin *openedByPlugin) = 0;
    virtual bool close(const IPlugin *closedByPlugin) = 0;

signals:
    void onOpen(const IPlugin *openedByPlugin);
    void onClose(const IPlugin *closedByPlugin);

protected:
    virtual ~IPlugin() {}
};
Q_DECLARE_INTERFACE(IPlugin, "IPlugin")
#endif // IPLUGIN_H
