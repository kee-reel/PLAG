#ifndef DATABASEMANAGERMODULE_H
#define DATABASEMANAGERMODULE_H

#include <QString>
#include <QtSql>
#include <QDebug>

#include "../../Plugins/MainMenuModelPlugin/interfaces.h"

#define CONNECTION_FAILED -1

class CipherDataBaseSourcePlugin : public QObject, IDataBaseSourcePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.DBModule.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IDataSourcePlugin IDataBaseSourcePlugin)
    const QString driverName = "SQLITECIPHER";

public:
    CipherDataBaseSourcePlugin();
    ~CipherDataBaseSourcePlugin();
    void OnAllSetup() override;
    QString GetLastError() override;

    void Setup() override;

    QSqlQuery ExecuteQuery(QString &queryText) override;
    QSqlQuery ExecuteQuery(QString &queryText, QList<QString> *valuePlaceholders, QList<QVariant> *values) override;

private:
    QString lastError;

    QSqlDatabase dbconn;
};

#endif // DATABASEMANAGERMODULE_H
