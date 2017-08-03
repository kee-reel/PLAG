#include "cipherdatabasesourceplugin.h"

CipherDataBaseSourcePlugin::CipherDataBaseSourcePlugin()
{
    Setup();
}

CipherDataBaseSourcePlugin::~CipherDataBaseSourcePlugin()
{
    dbconn.close();
}

void CipherDataBaseSourcePlugin::OnAllSetup()
{

}

QString CipherDataBaseSourcePlugin::GetLastError()
{
    if(lastError!="")
        return lastError;
    else
        return dbconn.lastError().text();
}

void CipherDataBaseSourcePlugin::SetPluginInfo(PluginInfo *pluginInfo)
{

}

void CipherDataBaseSourcePlugin::AddReferencePlugin(PluginInfo *pluginInfo)
{

}

void CipherDataBaseSourcePlugin::ReferencePluginClosed(PluginInfo *pluginInfo)
{

}

QSqlQuery CipherDataBaseSourcePlugin::ExecuteQuery(QString &queryText)
{
    QSqlQuery query;
    qDebug() << "Executing" << queryText;
    query.exec(queryText);
    if(query.lastError().text() != "")
        qDebug() << query.lastError();
    return query;
}

QSqlQuery CipherDataBaseSourcePlugin::ExecuteQuery(QString &queryText, QList<QString> *valuePlaceholders, QList<QVariant> *values)
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

void CipherDataBaseSourcePlugin::Setup()
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
