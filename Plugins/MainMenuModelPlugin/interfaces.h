#ifndef INTERFACES_H
#define INTERFACES_H

#include "../../System/MASS/rootinterface.h"

class QWidget;
class QString;
class QSqlDatabase;
class QSqlQuery;

enum PluginTypes{
    ROOTMODEL,
    PLUGINMODEL,
    PLUGINVIEW,
    DATASOURCE,
    DATAMANAGER,
};

struct MetaInfo{
    QString Name;
    PluginTypes Type;
    QString ParentPluginName;
    QString DataManagerlName;
};

template <class T>
struct PluginInfo
{
    T *plugin;
    MetaInfo *meta;
};

class IPlugin
{
public:
    virtual ~IPlugin() {}
    virtual void OnAllSetup() = 0;
    virtual QString GetLastError() = 0;
};

class IDataSourcePlugin : public IPlugin
{
public:
    virtual ~IDataSourcePlugin() {}
    virtual void Setup() = 0;
};
Q_DECLARE_INTERFACE(IDataSourcePlugin, "IDataSourcePlugin v0.1")

class IDataBaseSourcePlugin : public IDataSourcePlugin
{
public:
    virtual ~IDataBaseSourcePlugin() {}
    virtual QSqlQuery ExecuteQuery(QString query) = 0;
};
Q_DECLARE_INTERFACE(IDataBaseSourcePlugin, "IDataBaseSourcePlugin v0.1")

class IDataManagerPlugin : public IPlugin
{
public:
    virtual ~IDataManagerPlugin() {}
    virtual bool SetDataSource(QObject* dataSource) = 0;
};
Q_DECLARE_INTERFACE(IDataManagerPlugin, "IDBToolPlugin v0.1")

class IViewPlugin : public IPlugin
{
public:
    virtual ~IViewPlugin() {}
    virtual void SetModel(QObject *) = 0;
    virtual bool Open(int id, QWidget* parent) = 0;
    virtual bool Close() = 0;
};
Q_DECLARE_INTERFACE(IViewPlugin, "IViewPlugin v0.1")

class IModelPlugin : public IPlugin
{
public:
    virtual ~IModelPlugin() {}
    virtual void AddChildModel(IModelPlugin *model, MetaInfo *meta) = 0;
    virtual void AddView(IViewPlugin *view, MetaInfo *meta) = 0;
    virtual void AddDataManager(QObject *dataManager) = 0;

    virtual bool Open(IModelPlugin* parent, QWidget* parentWidget, int id) = 0;
    virtual bool Close() = 0;
    virtual void ChildSelfClosed(int id) = 0;
};
Q_DECLARE_INTERFACE(IModelPlugin, "IModelPlugin v0.1")

#endif // INTERFACES_H
