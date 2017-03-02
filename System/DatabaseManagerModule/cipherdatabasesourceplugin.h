#ifndef DATABASEMANAGERMODULE_H
#define DATABASEMANAGERMODULE_H

#include <QString>
#include <QtSql>
#include <QDebug>

#include "../../System/MASS/interfaces.h"

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
    virtual void OnAllSetup();
    virtual QString GetLastError();

    virtual void Setup();

    virtual QSqlQuery ExecuteQuery(QString query);

private:
    QString lastError;

    QSqlDatabase dbconn;
};

#endif // DATABASEMANAGERMODULE_H
