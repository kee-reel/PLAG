#ifndef INTERFACES_H
#define INTERFACES_H

class QObject;
class QWidget;
class QString;
class QSqlDatabase;
class QSqlQuery;

enum PluginTypes{
    ROOTMODEL,
    TOOLMODEL,
    TOOLVIEW,
    DATASOURCE,
    DATAMANAGER,
};

struct MetaInfo{
    QString Name;
    PluginTypes Type;
    QString ParentPluginName;
    QString DataManagerlName;
};

// TODO: Make realization of interface classes
class IPluginView
{
public:
    virtual ~IPluginView() {}
    virtual void SetModel(QObject *) = 0;
    virtual bool Open(int id, QWidget* parent) = 0;
    virtual bool Close() = 0;
};
Q_DECLARE_INTERFACE(IPluginView, "IPluginView v0.1")

class IPluginModel
{
public:
    virtual ~IPluginModel() {}
    virtual void AddChildPlugin(IPluginModel *model, MetaInfo *meta) = 0;
    virtual void AddView(IPluginView *view, MetaInfo *meta) = 0;
    virtual void SetDataManager(QObject *dataManager) = 0;

    virtual bool Open(IPluginModel* parent, QWidget* parentWidget, int id) = 0;
    virtual bool Close() = 0;
    virtual void ChildSelfClosed(int id) = 0;

    virtual QString GetError() = 0;
};
Q_DECLARE_INTERFACE(IPluginModel, "IModelPlugin v0.1")

class IDataSourcePlugin
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

class IDataManagerPlugin
{
public:
    virtual ~IDataManagerPlugin() {}
    virtual bool SetDataSource(QObject* dataSource) = 0;
    virtual QString GetError() = 0;
};
Q_DECLARE_INTERFACE(IDataManagerPlugin, "IDBToolPlugin v0.1")
#endif // INTERFACES_H
