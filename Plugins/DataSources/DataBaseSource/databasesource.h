#ifndef DATABASESOURCEPLUGIN_H
#define DATABASESOURCEPLUGIN_H

#include <QString>
#include <QtSql>
#include <QDebug>
#include <QList>

#include "idatabasesource.h"

#define CONNECTION_FAILED -1

//! \defgroup CipherDataBaseSourcePlugin CipherDataBaseSourcePlugin
//!     \ingroup MainMenuPlugin_rel_ds
//! \defgroup CipherDataBaseSourcePlugin_imp Implementation
//!     \ingroup CipherDataBaseSourcePlugin

//! \addtogroup CipherDataBaseSourcePlugin_imp
//! \{
class DataBaseSourcePlugin : public QObject, IDataBaseSourcePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.DBModule.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IDataSourcePlugin IDataBaseSourcePlugin)

public:
    DataBaseSourcePlugin();
    ~DataBaseSourcePlugin();

    // IPlugin interface
public:
    void SetPluginInfo(PluginInfo *pluginInfo) override;
    void OnAllSetup() override;
    QString GetLastError() override;
    void AddReferencePlugin(PluginInfo *pluginInfo) override;
signals:
    void OnClose(PluginInfo *pointer);
    void OnClose();

public slots:
    void ReferencePluginClosed(PluginInfo *pluginInfo) override;

    // IDataSourcePlugin interface
public:
    void Setup() override;

    // IDataBaseSourcePlugin interface
public:
    QSqlQuery ExecuteQuery(QString &query) override;
    QSqlQuery ExecuteQuery(QString &query, QList<QString> *valuePlaceholders, QList<QVariant> *values) override;
    void SetPassword(QString password) override;

private:
    //!
    //! \brief possibleDriverNames
    //! Stores possible database drivers in list by it's priority - for instance:
    //! "SQLITECIPHER", "QSQLITE", "QPSQL"...
    //!
    QList<QString> possibleDriverNames;
    QString lastError;
    QString password;
    QString connectionName;
    QSqlDatabase dbconn;
    bool ConnectWithDriver(QString driverName);

};
//! \}
#endif // DATABASEMANAGERMODULE_H
