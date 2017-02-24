#include "cipherdatabasesourceplugin.h"

CipherDatabaseSourcePlugin::CipherDatabaseSourcePlugin()
{
}

CipherDatabaseSourcePlugin::~CipherDatabaseSourcePlugin()
{
    dbconn.close();
}

QSqlQuery CipherDatabaseSourcePlugin::ExecuteQuery(QString queryText)
{
    QSqlQuery query;
    query.exec(queryText);
    return query;
}

void CipherDatabaseSourcePlugin::Setup()
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
    dbconn.setDatabaseName("cipherdb.db");
    // Add password
    dbconn.setPassword("test");
    if (!dbconn.open()) {
        qDebug() << "Can not open connection: " << dbconn.lastError().driverText();
    }
}