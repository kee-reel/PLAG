#ifndef DataBasePLUGIN_H
#define DataBasePLUGIN_H

#include <QString>
#include <QtSql>
#include <QDebug>
#include <QList>

#include "../../Interfaces/idatabase.h"
#include "../../Common/plugin_base.h"

#define CONNECTION_FAILED -1

//! \addtogroup DataBase_imp
//! \{
class DataBase : public PluginBase, public IDataBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.DBModule.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IPlugin
        IDataBase
    )

public:
    DataBase();
    virtual ~DataBase() override;

    // IDataBase interface
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
