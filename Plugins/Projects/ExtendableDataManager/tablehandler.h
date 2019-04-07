#ifndef TABLEHANDLER_H
#define TABLEHANDLER_H

#include <QMap>
#include <QtSql>
#include <QDebug>
#include <QVariant>

#include "../../Interfaces/iextendabledatamanager.h"
#include "../../Interfaces/idatabase.h"
#include "extendableitemmodel.h"

//! \addtogroup ExtendableDataManager_imp
//!  \{
class TableHandler
{
    typedef IExtendableDataManager::ManagerDataItem ManagerDataItem;
    typedef QMap<QString, QVariant::Type> TableStructMap;
public:
    QMap<QVariant::Type, QString> dataBaseTypesNames =
    {
        {QVariant::Int,        "INTEGER"},
        {QVariant::String,     "VARCHAR"},
        {QVariant::DateTime,   "VARCHAR"},
        {QVariant::ByteArray,  "BLOB"}
    };

    TableHandler(IDataBase *dataSource, IExtendableDataManager *dataManager, QString tableName = "");
    ~TableHandler();

    inline QString TableName() { return tableName; }
    bool HasRelation(QString relation);

    bool CreateTable();
    bool SetRelation(QString relationName, TableStructMap fields, QVector<QVariant> defaultData);
    void SetActiveRelation(QString relationName);
    void SetDataTypeEditor(QString dataChunk, QString fieldName, QWidget *widget);
    bool DeleteRelation(QString relationName);

    int AddItem(ManagerDataItem item);
    bool UpdateItem(ManagerDataItem item);
    bool DeleteItem(int id);

    QList<ManagerDataItem> GetData();
    ManagerDataItem GetItem(int id);
    QAbstractItemModel *GetModel();
    TableStructMap GetHeader();
    QVector<QVariant> GetRelationDefaultData(QString relationName);


private:
    IDataBase *dataSource;
    IExtendableDataManager *dataManager;
    ExtendableItemModel *itemModel;
    QString tableName;
    bool isCreated;

    TableStructMap wholeTableStruct;
    TableStructMap coreTableStruct;
    QMap<QString, TableStructMap> relationTablesStructs;
    QMap<QString, QVector<QVariant>> relationsDefaultData;

    QString GetInsertValuesString(TableStructMap &tableStruct, int id, QVector<QVariant> &itemData);
    QString GetUpdateValuesString(TableStructMap &tableStruct, int id);
    QString GetUpdateValuesString(TableStructMap &tableStruct, int id, QVector<QVariant> &itemData);

    bool IsDataSourceExists();
    bool IsTableExists(QString tableName);
    bool IsTableHasRightStructure(QString tableName, TableStructMap &tableStruct);
    void CombineWholeTableStruct();
    QString GetHeaderString(TableStructMap &tableStruct, bool createRelation = false);
    QString GetFieldsNames(QString tableName, TableStructMap &tableStruct, bool includeId = false);
    void InstallModel();
};
//!  \}
#endif // TABLEHANDLER_H
