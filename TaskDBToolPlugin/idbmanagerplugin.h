#ifndef IDBMANAGERPLUGIN_H
#define IDBMANAGERPLUGIN_H

#include <QString>
#include <QtSql>

class IDBManagerPlugin
{
public:
    virtual QSqlDatabase *SetupDatabase() = 0;
    virtual QSqlQuery *ExecuteQuery(QString query) = 0;
};
Q_DECLARE_INTERFACE(IDBManagerPlugin, "IDBManagerPlugin v0.1")

#endif // IDBMANAGERPLUGIN_H
