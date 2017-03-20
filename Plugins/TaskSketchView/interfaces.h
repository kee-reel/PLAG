#ifndef INTERFACES_H
#define INTERFACES_H

enum PluginTypes{
    TOOLMODEL,
    TOOLVIEW,
    DBMANAGER,
    DBTOOL,
    MAIN
};

struct MetaInfo{
    QString Name;
    PluginTypes Type;
    QString ParentPluginName;
};

class QObject;
class QWidget;
class QString;
class QSqlDatabase;
class QSqlQuery;

class IPluginModel
{
public:
    virtual void DoSomething() = 0;
    virtual void AddChildPlugin(IPluginModel*, MetaInfo*) = 0;
    virtual void AddDBTool(QObject*) = 0;

    virtual bool Open(QWidget*) = 0;
    virtual bool Close() = 0;
    virtual QString GetError() = 0;
};
Q_DECLARE_INTERFACE(IPluginModel, "IModelPlugin v0.1")

class IPluginView
{
public:
    virtual void SetModel(QObject*) = 0;
};
Q_DECLARE_INTERFACE(IPluginView, "IPluginView v0.1")

class IDBManagerPlugin
{
public:
    virtual QSqlDatabase *SetupDatabase() = 0;
    virtual QSqlQuery *ExecuteQuery(QString query) = 0;
};
Q_DECLARE_INTERFACE(IDBManagerPlugin, "IDBManagerPlugin v0.1")

class IDBToolPlugin
{
public:
    virtual bool SetDBManager(IDBManagerPlugin* DBManager) = 0;
};
Q_DECLARE_INTERFACE(IDBToolPlugin, "IDBToolPlugin v0.1")
#endif // INTERFACES_H
