#ifndef INTERFACES_H
#define INTERFACES_H

#include "../../System/MASS/rootinterface.h"
class QString;
class QVariant;
class QSqlDatabase;
class QSqlQuery;
template <class A> class QList;

//! \addtogroup MainMenuModule MainMenuModule
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

//!
//! \brief The MetaInfo struct
//!
struct MetaInfo{
    QString Name;
    PluginTypes Type;
    QString ParentPluginName;
    QString DataManagerlName;
};

template <class T>
//!
//! \brief The PluginInfo struct
//!
struct PluginInfo
{
    T *plugin;
    MetaInfo *meta;
};

//!
//! \brief The IPlugin class
//!
class IPlugin
{
public:
    virtual ~IPlugin() {}
    virtual void OnAllSetup() = 0;
    virtual QString GetLastError() = 0;
};

//!
//! \brief The IDataSourcePlugin class
//!
class IDataSourcePlugin : public IPlugin
{
public:
    virtual ~IDataSourcePlugin() {}
    virtual void Setup() = 0;
};
Q_DECLARE_INTERFACE(IDataSourcePlugin, "IDataSourcePlugin v0.1")

//!
//! \brief The IDataBaseSourcePlugin class
//!
class IDataBaseSourcePlugin : public IDataSourcePlugin
{
public:
    virtual ~IDataBaseSourcePlugin() {}
    virtual QSqlQuery ExecuteQuery(QString &query) = 0;
    virtual QSqlQuery ExecuteQuery(QString &query, QList<QString> *valuePlaceholders, QList<QVariant> *values) = 0;
};
Q_DECLARE_INTERFACE(IDataBaseSourcePlugin, "IDataBaseSourcePlugin v0.1")

//!
//! \brief The IDataManagerPlugin class
//!
class IDataManagerPlugin : public IPlugin
{
public:
    virtual ~IDataManagerPlugin() {}
    virtual bool SetDataSource(QObject* dataSource) = 0;
};
Q_DECLARE_INTERFACE(IDataManagerPlugin, "IDBToolPlugin v0.1")

//!
//! \brief The IViewPlugin class
//!
class IViewPlugin : public IPlugin
{
public:
    virtual ~IViewPlugin() {}
    virtual void SetModel(QObject *) = 0;
    virtual bool Open(QWidget* parent) = 0;
    virtual bool Close() = 0;
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
    virtual void AddParentModel(QObject *model, MetaInfo *meta) = 0;
    virtual void AddChildModel(IModelPlugin *model, MetaInfo *meta) = 0;
    virtual void AddView(IViewPlugin *view, MetaInfo *meta) = 0;

    virtual bool Open(IModelPlugin* parent, QWidget* parentWidget) = 0;
    virtual bool CloseFromView(IViewPlugin *view) = 0;
    virtual void ChildSelfClosed(IModelPlugin *child) = 0;
};
Q_DECLARE_INTERFACE(IModelPlugin, "IModelPlugin v0.1")

//! @}
#endif // INTERFACES_H
