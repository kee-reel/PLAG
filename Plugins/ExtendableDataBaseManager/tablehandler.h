#ifndef TABLEHANDLER_H
#define TABLEHANDLER_H

#include <QMap>
#include <QtSql>
#include <QDebug>
#include <QVariant>

#include "iextendabledatabasemanagerplugin.h"

class TableHandler
{
    typedef IExtendableDataBaseManagerPlugin::ManagerItemInfo ManagerItemInfo;
    typedef QMap<QString, QVariant::Type> TableStructMap;

private:
    IDataBaseSourcePlugin *dataSource;
    QString tableName;
    bool isCreated;

public:
    inline QString TableName() {return tableName;}
    QMap<QVariant::Type, QString> dataBaseTypesNames;
    QStringList relations;
    TableStructMap coreTableStruct;
    TableStructMap wholeTableStruct;
    QMap<QString, TableStructMap> relationTableStructs;

    TableHandler(IDataBaseSourcePlugin *dataSource, QString tableName = "");

    bool CreateTable();
    bool SetRelation(QString relationName, TableStructMap fields);
    bool DeleteRelation(QString relationName);

    QList<ManagerItemInfo> GetData();
    int AddItem(ManagerItemInfo item);
    bool EditItem(ManagerItemInfo item);
    bool DeleteItem(int id);

    TableStructMap GetHeader();
    QString GetHeaderString(TableStructMap &tableStruct, bool createRelation = false);
    QString GetInsertValuesString(TableStructMap &tableStruct, int id, QVector<QVariant> &itemData);
    QString GetUpdateValuesString(TableStructMap &tableStruct, int id, QVector<QVariant> &itemData);

    bool IsTableExists(QString tableName);
    //bool IsTableRightStructure(QString tableName);
    void CombineWholeTableStruct();
};

#endif // TABLEHANDLER_H
