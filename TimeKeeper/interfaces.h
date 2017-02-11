#ifndef INTERFACES_H
#define INTERFACES_H

class QObject;
class QWidget;
class QString;
class QSqlDatabase;
class QSqlQuery;

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
    QString DBToolName;
};

class IPluginView
{
public:
    virtual ~IPluginView() {}
    virtual void SetModel(QObject *) = 0;
    virtual bool Open(QWidget* parent) = 0;
    virtual bool Close() = 0;
};
Q_DECLARE_INTERFACE(IPluginView, "IPluginView v0.1")

class IPluginModel
{
public:
    virtual ~IPluginModel() {}
    virtual void AddChildPlugin(IPluginModel*, MetaInfo*) = 0;
    virtual void AddView(IPluginView *, MetaInfo *) = 0;
    virtual void SetDBTool(QObject*) = 0;
    virtual bool Open(QWidget* parent) = 0;
    virtual bool Close() = 0;

    virtual QString GetError() = 0;
};
Q_DECLARE_INTERFACE(IPluginModel, "IModelPlugin v0.1")

class IDBManagerPlugin
{
public:
    virtual ~IDBManagerPlugin() {}
    virtual void SetupDatabase() = 0;
    virtual QSqlQuery* ExecuteQuery(QString query) = 0;
};
Q_DECLARE_INTERFACE(IDBManagerPlugin, "IDBManagerPlugin v0.1")

class IDBToolPlugin
{
public:
    virtual ~IDBToolPlugin() {}
    virtual bool SetDBManager(IDBManagerPlugin* DBManager) = 0;
};
Q_DECLARE_INTERFACE(IDBToolPlugin, "IDBToolPlugin v0.1")
#endif // INTERFACES_H
