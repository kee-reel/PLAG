#include "cipherdatabasemanagermodule.h"

CipherDatabaseManagerModule::CipherDatabaseManagerModule()
{
}

CipherDatabaseManagerModule::~CipherDatabaseManagerModule()
{
    dbconn.close();
}

QSqlQuery* CipherDatabaseManagerModule::ExecuteQuery(QString queryText)
{
    QSqlQuery* query = new QSqlQuery(queryText);
    return query;
}

void CipherDatabaseManagerModule::SetupDatabase()
{
    if(dbconn.isOpen())
    {
        qDebug() << "Driver already runs.";
        return;
    }

    qDebug() << "My driver is" << driverName <<
                "Existing drivers are" << QSqlDatabase::drivers();

    // Connect to database
    qDebug() << QSqlDatabase::isDriverAvailable(driverName);
    dbconn = QSqlDatabase::addDatabase(driverName);
    // Create database
    dbconn.setDatabaseName("test_c.db");
    // Add password
    dbconn.setPassword("test");
    if (!dbconn.open()) {
        qDebug() << "Can not open connection: " << dbconn.lastError().driverText();
    }
}
