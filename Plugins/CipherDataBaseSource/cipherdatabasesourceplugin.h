#ifndef DATABASESOURCEPLUGIN_H
#define DATABASESOURCEPLUGIN_H

#include <QString>
#include <QtSql>
#include <QDebug>

#include "../../Plugins/MainMenuModelPlugin/interfaces.h"

#define CONNECTION_FAILED -1

//! \defgroup CipherDataBaseSourcePlugin CipherDataBaseSourcePlugin
//!     \ingroup MainMenuPlugin_rel_ds
//! \defgroup CipherDataBaseSourcePlugin_imp Implementation
//!     \ingroup CipherDataBaseSourcePlugin

//! \addtogroup CipherDataBaseSourcePlugin_imp
//! \{
class CipherDataBaseSourcePlugin : public QObject, IDataBaseSourcePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.DBModule.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IDataSourcePlugin IDataBaseSourcePlugin)
    const QString driverName = "SQLITECIPHER";

public:
    CipherDataBaseSourcePlugin();
    ~CipherDataBaseSourcePlugin();

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

private:
    QString lastError;
    QSqlDatabase dbconn;
};
//! \}
#endif // DATABASEMANAGERMODULE_H
