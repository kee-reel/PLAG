#ifndef INTERFACES_H
#define INTERFACES_H

#include "../../System/MASS/rootinterface.h"
class QString;
class QVariant;
class QSqlDatabase;
class QSqlQuery;
template <class A> class QList;

//! \addtogroup MainMenuPlugin_int
//! @{

//! Enumeration of MASS system modules types.
enum PluginTypes
{
    ROOTMODEL,      //!< Module type that implements IRootModelPlugin
    PLUGINMODEL,    //!< Module type that implements IModelPlugin
    PLUGINVIEW,     //!< Module type that implements IViewPlugin
    DATASOURCE,     //!< Module type that implements IDataSourcePlugin
    DATAMANAGER,    //!< Module type that implements IDataManagerPlugin
};

//! \brief Holds information about plugin.
struct MetaInfo{
    //! \brief Plugin name.
    QString Name;
    //! \brief Type of plugin.
    PluginTypes Type;
    //! \brief Name of parent plugin (in tree structure).
    QString ParentPluginName;
    //! \brief Name of data manager that plugin will be using
    QString DataManagerName;
};

template <class T>
//! \brief Structure for internal needs. Pair of type of plugin and it's meta information.
struct PluginInfo
{
    //! \brief Class instance of plugin.
    T *plugin;
    //! \brief QObject instance of plugin.
    QObject *instance;
    //! \brief Meta information of plugin.
    MetaInfo *meta;
};

//! \brief This interface provides basic methods for all plugins.
class IPlugin
{
public:
    virtual ~IPlugin() {}
    //! \brief Method which calls when system setup all connections between plugins.
    virtual void OnAllSetup() = 0;
    //! \brief Gets last error message from plugin.
    virtual QString GetLastError() = 0;
};

//! \brief This interface describes DataSource plugin.
//!
//! DataSource plugin implements interaction with data source. In place of
//! data source could be data base, network connection, some device and etc.
class IDataSourcePlugin : public IPlugin
{
public:
    virtual ~IDataSourcePlugin() {}
    //! \brief Install connection with source.
    virtual void Setup() = 0;
};
Q_DECLARE_INTERFACE(IDataSourcePlugin, "IDataSourcePlugin v0.1")

//! \brief This interface determine data source as data base.
//!
//! Provides methods for interaction with data base with usage of SQL queries.
class IDataBaseSourcePlugin : public IDataSourcePlugin
{
public:
    virtual ~IDataBaseSourcePlugin() {}
    //! \brief Execute query whithin connected data base using given string.
    //! \param Query string.
    //! \return Query result.
    //!
    virtual QSqlQuery ExecuteQuery(QString &query) = 0;
    //! \brief Execute query whithin connected data base using given string and parameters.
    //! \param Query string.
    //! \param Placeholders contained in string.
    //! \param Values that will be inserted in given placeholders.
    //! \return Query result.
    //!
    virtual QSqlQuery ExecuteQuery(QString &query, QList<QString> *valuePlaceholders, QList<QVariant> *values) = 0;
};
Q_DECLARE_INTERFACE(IDataBaseSourcePlugin, "IDataBaseSourcePlugin v0.1")

//! \brief This interface describes DataManager plugn.
//!
//! DataManager plugin implements interaction with DataSource plugin.
class IDataManagerPlugin : public IPlugin
{
public:
    virtual ~IDataManagerPlugin() {}
    //!
    //! \brief SetDataSource
    //! \param dataSource
    //! \return
    //!
    virtual bool AddDataSource(QObject* dataSource) = 0;
};
Q_DECLARE_INTERFACE(IDataManagerPlugin, "IDBToolPlugin v0.1")

class IModelPlugin;
//! \brief This interface describes DataManager plugn.
//!
//!
class IViewPlugin : public IPlugin
{
public:
    virtual ~IViewPlugin() {}
    virtual void AddModel(QObject *model) = 0;
public slots:
    virtual bool Open(IModelPlugin* model, QWidget* parent) = 0;
    virtual bool Close() = 0;
signals:
    void OnClose(IViewPlugin *pointer);
};
Q_DECLARE_INTERFACE(IViewPlugin, "IViewPlugin v0.1")

//!
//! \brief The IModelPlugin class
//!
class IModelPlugin : public IPlugin
{
public:
    virtual ~IModelPlugin() {}
    virtual void AddDataManager(QObject *dataManager) = 0;
    virtual void AddModel(QObject *model, MetaInfo *meta) = 0;
    virtual void AddView(QObject *model, MetaInfo *meta) = 0;
public slots:
    virtual bool Open(IModelPlugin* model, QWidget* modelWidget) = 0;
    virtual void Close() = 0;
signals:
    void OnClose(IModelPlugin *pointer);
};
Q_DECLARE_INTERFACE(IModelPlugin, "IModelPlugin v0.1")

//! @}
#endif // INTERFACES_H
