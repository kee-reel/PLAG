#ifndef TABLEHANDLER_H
#define TABLEHANDLER_H

#include <QMap>
#include <QtSql>
#include <QDebug>
#include <QVariant>

#include "iextendabledatabasemanagerplugin.h"
#include "extendableitemmodel.h"

//! \addtogroup ExtendableDataBaseManagerPlugin_imp
//! \{
class TableHandler
{
    typedef IExtendableDataBaseManager::ManagerDataItem ManagerItemInfo;
    typedef QMap<QString, QVariant::Type> TableStructMap;

private:
    IDataBaseSourcePlugin *dataSource;
    IExtendableDataBaseManager *dataManager;
    ExtendableItemModel *itemModel;
    QString tableName;
    bool isCreated;

public:
    inline QString TableName() {return tableName;}
    QMap<QVariant::Type, QString> dataBaseTypesNames;
    TableStructMap coreTableStruct;
    TableStructMap wholeTableStruct;
    QMap<QString, TableStructMap> relationTableStructs;
    QMap<QString, QVector<QVariant>> relationsDefaultData;

    TableHandler(IDataBaseSourcePlugin *dataSource, IExtendableDataBaseManager *dataManager, QString tableName = "");
    ~TableHandler();

    bool CreateTable();
    bool SetRelation(QString relationName, TableStructMap fields, QVector<QVariant> defaultData);
    void SetActiveRelation(QString relationName);
    bool DeleteRelation(QString relationName);

    QList<ManagerItemInfo> GetData();
    ManagerItemInfo GetItem(int id);
    QAbstractItemModel *GetModel();

    int AddItem(ManagerItemInfo item);
    bool EditItem(ManagerItemInfo item);
    bool DeleteItem(int id);

    TableStructMap GetHeader();
    QVector<QVariant> GetRelationDefaultData(QString relationName);

    QString GetHeaderString(TableStructMap &tableStruct, bool createRelation = false);
    QString GetFieldsNames(QString tableName, TableStructMap &tableStruct, bool includeId = false);

private:
    QString GetInsertValuesString(TableStructMap &tableStruct, int id, QVector<QVariant> &itemData);
    QString GetUpdateValuesString(TableStructMap &tableStruct, int id);
    QString GetUpdateValuesString(TableStructMap &tableStruct, int id, QVector<QVariant> &itemData);

    bool IsDataSourceExists();
    bool IsTableExists(QString tableName);
    //bool IsTableRightStructure(QString tableName);
    void CombineWholeTableStruct();
};
//! \}
#endif // TABLEHANDLER_H
