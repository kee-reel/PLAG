#ifndef ITASKDBTOOLPLUGIN_H
#define ITASKDBTOOLPLUGIN_H

#include <QtGlobal>
#include <QVariant>


class QAbstractItemModel;

//!  \defgroup ExtendableDataManager ExtendableDataManager
//!      \ingroup Plugins
//! \defgroup ExtendableDataBaseManager_int Interfaces
//!     \ingroup ExtendableDataBaseManager
//! \defgroup ExtendableDataBaseManager_imp Implementation
//!     \ingroup ExtendableDataBaseManager
//!  \defgroup ExtendableDataBaseManager_dep Dependent plugins
//!      \ingroup ExtendableDataBaseManager

//! \addtogroup ExtendableDataBaseManager_int
//!  \{
//! \brief
class IExtendableDataManager
{
public:
    struct ManagerDataItem
    {
        int id;
        QMap<QString, QVector<QVariant> > dataChunks;
    };

    virtual bool RegisterExtentionFieldEditor(QString relation, QString field, QWidget *widget) = 0;
    virtual QWidget *GetExtentionFieldEditor(QString relation, QString field) = 0;

    virtual QList<ManagerDataItem> GetDataList(QString treeName) = 0;
    virtual ManagerDataItem GetDataItem(QString treeName, int id) = 0;
    virtual QMap<QString, QVariant::Type> GetTableHeader(QString treeName) = 0;

    virtual QAbstractItemModel *GetDataModel(QString treeName) = 0;
    virtual QAbstractItemModel *GetDataModel(QVector<QPair<QString, QString> > dataModelFields) = 0;

    virtual bool AddExtention(QString mainName, QString relationName,
                              QMap<QString, QVariant::Type> fields,
                              QVector<QVariant> defaultData) = 0;
    virtual bool DeleteExtention(QString mainName, QString relationName) = 0;
    virtual bool SetActiveExtention(QString mainName, QString relationName) = 0;

    virtual int AddItem(QString treeName, ManagerDataItem task) = 0;
    virtual bool UpdateItem(QString treeName, ManagerDataItem task) = 0;
    virtual bool DeleteItem(QString treeName, int id) = 0;
};
Q_DECLARE_INTERFACE(IExtendableDataManager, "IExtendableDataManager v0.1")
//! @}
#endif // ITASKDBTOOLPLUGIN_H
