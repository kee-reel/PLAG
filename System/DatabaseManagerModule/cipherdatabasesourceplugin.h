#ifndef DATABASEMANAGERMODULE_H
#define DATABASEMANAGERMODULE_H

#include <QString>
#include <QtSql>
#include <QDebug>

#include "../../System/TimeKeeper/interfaces.h"

#define CONNECTION_FAILED -1

class CipherDatabaseSourcePlugin : public QObject, IDataBaseSourcePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.DBModule.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IDataSourcePlugin IDataBaseSourcePlugin)
    const QString driverName = "SQLITECIPHER";

public:
    CipherDatabaseSourcePlugin();
    ~CipherDatabaseSourcePlugin();

private:
    QSqlDatabase dbconn;

    // IDataSourcePlugin interface
public:
    virtual void Setup();

    // IDataBaseSourcePlugin interface
public:
    virtual QSqlQuery ExecuteQuery(QString query);
};

#endif // DATABASEMANAGERMODULE_H
