#ifndef DATABASESOURCEPLUGIN_H
#define DATABASESOURCEPLUGIN_H

#include <QString>
#include <QtSql>
#include <QDebug>
#include <QList>

#include "../../Interfaces/idatabasesource.h"
#include "../../Common/plugin_base.h"

#define CONNECTION_FAILED -1

//! \defgroup CipherDataBaseSourcePlugin CipherDataBaseSourcePlugin
//!     \ingroup MainMenuPlugin_rel_ds
//! \defgroup CipherDataBaseSourcePlugin_imp Implementation
//!     \ingroup CipherDataBaseSourcePlugin

//! \addtogroup CipherDataBaseSourcePlugin_imp
//! \{
class DataBaseSourcePlugin : public PluginBase, public IDataBaseSourcePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.DBModule.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IPlugin
        IDataBaseSourcePlugin
    )

public:
    DataBaseSourcePlugin();
    virtual ~DataBaseSourcePlugin() override;

    // IDataBaseSourcePlugin interface
public:
    QSqlQuery ExecuteQuery(QString &query) override;
    QSqlQuery ExecuteQuery(QString &query, QList<QString> *valuePlaceholders, QList<QVariant> *values) override;
    void SetPassword(QString m_password) override;

private:
    bool Setup();
    bool ConnectWithDriver(QString driverName);

private:
    //! \brief possibleDriverNames
    //! Stores possible database drivers in list by it's priority.
    QList<QString> m_possibleDriverNames;
    QString m_password;
    QString m_connectionName;
    QSqlDatabase m_dbconn;

};
//! \}
#endif // DATABASEMANAGERMODULE_H
