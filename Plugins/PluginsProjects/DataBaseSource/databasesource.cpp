#include "databasesource.h"

DataBaseSourcePlugin::DataBaseSourcePlugin() :
    PluginBase ()
{
    m_possibleDriverNames
            << "SQLITECIPHER"
            << "QSQLITE";
}

DataBaseSourcePlugin::~DataBaseSourcePlugin()
{
    m_dbconn.close();
}

QSqlQuery DataBaseSourcePlugin::ExecuteQuery(QString &queryText)
{
    if(!Setup())
    {
        return QSqlQuery();
    }

    QSqlQuery query;
    qDebug() << "DataBaseSourcePlugin:: Executing" << queryText;
    if(!query.exec(queryText))
    {
        raiseError(query.lastError().text());
    }
    return query;
}

QSqlQuery DataBaseSourcePlugin::ExecuteQuery(QString &queryText, QList<QString> *valuePlaceholders,
        QList<QVariant> *values)
{
    QSqlQuery query;
    if(valuePlaceholders->count() != values->count())
    {
        qDebug() << "Values lists count not equal";
        return query;
    }
    query.prepare(queryText);
    for(int i = 0; i < valuePlaceholders->count(); ++i)
    {
        QFlags<QSql::ParamTypeFlag> flag = (values->at(i).type() == QVariant::ByteArray) ? QSql::In | QSql::Binary : QSql::In;
        query.bindValue(valuePlaceholders->at(i), values->at(i), flag);
    }
    query.exec();
    qDebug() << endl << ">Executing" << query.executedQuery();
    if(query.lastError().text() != "")
    {
        qDebug() << query.lastError();
    }
    return query;
}

void DataBaseSourcePlugin::SetPassword(QString password)
{
    this->m_password = password;
}

bool DataBaseSourcePlugin::Setup()
{
    if(m_dbconn.isOpen())
    {
        return true;
    }

    qDebug() << "Available drivers are" << QSqlDatabase::drivers();
    foreach (auto driverName, m_possibleDriverNames)
    {
        qDebug() << "Trying to connect to database with" << driverName << "driver";
        if(ConnectWithDriver(driverName))
        {
            qDebug() << "Connected to database succesfully";
            return true;
        }
    }
    return false;
}

bool DataBaseSourcePlugin::ConnectWithDriver(QString driverName)
{
    if(!QSqlDatabase::isDriverAvailable(driverName))
    {
        qCritical() << "Driver not available";
        return false;
    }

    m_connectionName = QString("db_%1.db").arg(driverName);
    m_dbconn = QSqlDatabase::addDatabase(driverName);

    // Create database
    m_dbconn.setDatabaseName(m_connectionName);
    m_dbconn.setPassword(m_password);
    bool isConnected = m_dbconn.open();

    if(isConnected)
    {
        m_password = "";
    }
    else
    {
        qCritical() << "Database connection error:" << m_dbconn.lastError();
    }

    return isConnected;
}
