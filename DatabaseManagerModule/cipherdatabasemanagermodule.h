#ifndef DATABASEMANAGERMODULE_H
#define DATABASEMANAGERMODULE_H

#include <QString>
#include <QtSql>
#include <QDebug>

#include "idbmanagerplugin.h"

#define CONNECTION_FAILED -1

class CipherDatabaseManagerModule : public QObject, IDBManagerPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.DBModule.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IDBManagerPlugin)
    const QString driverName = "SQLITECIPHER";

public:
    CipherDatabaseManagerModule();
    ~CipherDatabaseManagerModule();

private:
    QSqlDatabase dbconn;

public:
    // IDBManagerPlugin interface
    QSqlDatabase *SetupDatabase() override;
    QSqlQuery *ExecuteQuery(QString queryText) override;
};

#endif // DATABASEMANAGERMODULE_H
