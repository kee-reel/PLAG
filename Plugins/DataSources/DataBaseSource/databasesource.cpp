#include "databasesource.h"

DataBaseSourcePlugin::DataBaseSourcePlugin()
{
    possibleDriverNames
            << "SQLITECIPHER"
            << "QSQLITE";
}

DataBaseSourcePlugin::~DataBaseSourcePlugin()
{
    dbconn.close();
    qDebug() << "Closing data source:" << GetLastError();

}

void DataBaseSourcePlugin::OnAllSetup()
{

}

QString DataBaseSourcePlugin::GetLastError()
{
    if(lastError != "")
        return lastError;
    else
        return dbconn.lastError().text();
}

void DataBaseSourcePlugin::SetPluginInfo(PluginInfo *pluginInfo)
{

}

void DataBaseSourcePlugin::AddReferencePlugin(PluginInfo *pluginInfo)
{

}

void DataBaseSourcePlugin::ReferencePluginClosed(PluginInfo *pluginInfo)
{

}

QSqlQuery DataBaseSourcePlugin::ExecuteQuery(QString &queryText)
{
    QSqlQuery query;
    qDebug() << "Executing" << queryText;
    query.exec(queryText);
    if(query.lastError().text() != "")
        qDebug() << query.lastError();
    return query;
}

QSqlQuery DataBaseSourcePlugin::ExecuteQuery(QString &queryText, QList<QString> *valuePlaceholders, QList<QVariant> *values)
{
    QSqlQuery query;
    if(valuePlaceholders->count() != values->count()) {
        qDebug() << "Values lists count not equal";
        return query;
    }
    query.prepare(queryText);
    for(int i = 0; i < valuePlaceholders->count(); ++i)
    {
        QFlags<QSql::ParamTypeFlag> flag = (values->at(i).type() == QVariant::ByteArray) ? QSql::In|QSql::Binary : QSql::In;
        query.bindValue(valuePlaceholders->at(i), values->at(i), flag);
    }
    query.exec();
    qDebug() << endl << ">Executing" << query.executedQuery();
    if(query.lastError().text() != "")
        qDebug() << query.lastError();
    return query;
}

void DataBaseSourcePlugin::SetPassword(QString password)
{
    this->password = password;
}

void DataBaseSourcePlugin::Setup()
{
    if(dbconn.isOpen())
    {
        qDebug() << "Driver already runs.";
        return;
    }

    qDebug() << "Available drivers are" << QSqlDatabase::drivers();
    foreach (auto driverName, possibleDriverNames)
    {
        qDebug() << "Trying to connect to database with" << driverName << "driver";
        if(ConnectWithDriver(driverName))
        {
            qDebug() << "Connected to database succesfully";
            break;
        }
    }
}

bool DataBaseSourcePlugin::ConnectWithDriver(QString driverName)
{
    if(!QSqlDatabase::isDriverAvailable(driverName))
    {
        qCritical() << "Driver not available";
        return false;
    }

    connectionName = QString("db_%1.db").arg(driverName);
    dbconn = QSqlDatabase::addDatabase(driverName);

    // Create database
    dbconn.setDatabaseName(connectionName);
    dbconn.setPassword(password);
    bool isConnected = dbconn.open();

    if(isConnected)
    {
        password = "";
    }
    else
    {
        qCritical() << "Database connection error:" << dbconn.lastError();
    }

    return isConnected;
}
