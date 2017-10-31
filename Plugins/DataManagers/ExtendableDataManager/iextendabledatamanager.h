#ifndef ITASKDBTOOLPLUGIN_H
#define ITASKDBTOOLPLUGIN_H

#include <QtGlobal>

#include "../../interfaces.h"

template <class T1, class T2> class QPair;
enum QVariant::Type;
class QAbstractItemModel;

//! \defgroup ExtendableDataBaseManagerPlugin ExtendableDataBaseManagerPlugin
//!     \ingroup MainMenuPlugin_rel_dm
//! \defgroup ExtendableDataBaseManagerPlugin_int Interfaces
//!     \ingroup ExtendableDataBaseManagerPlugin
//! \defgroup ExtendableDataBaseManagerPlugin_imp Implementation
//!     \ingroup ExtendableDataBaseManagerPlugin

//! \addtogroup ExtendableDataBaseManagerPlugin_int
//! \{
//! \brief
class IExtendableDataManager : public IDataManagerPlugin
{
public:
    class ManagerDataItem
    {
    public:
        virtual QVector<QString> GetHeader() = 0;
        virtual QMap<int, QVector<QVariant> > GetData() = 0;
    };

    virtual bool RegisterExtentionFieldEditor(QString relation, QString field, QWidget *widget) = 0;
    virtual QWidget *GetExtentionFieldEditor(QString relation, QString field) = 0;

    virtual QList<ManagerDataItem> GetDataList(QString treeName) = 0;
    virtual ManagerDataItem GetDataItem(QString treeName, int id) = 0;
    virtual QMap<QString, QVariant::Type> GetTableHeader(QString treeName) = 0;

    virtual QAbstractItemModel *GetDataModel(QString treeName) = 0;
    virtual QAbstractItemModel *GetDataModel(QVector<QPair<QString, QString> > dataModelFields) = 0;

    virtual bool AddExtention(QString mainName, QString relationName,
                              QMap<QString, QVariant::Type> fields, QVector<QVariant> defaultData) = 0;
    virtual bool DeleteExtention(QString mainName, QString relationName) = 0;
    virtual bool SetActiveExtention(QString mainName, QString relationName) = 0;

    virtual int AddItem(QString treeName, ManagerDataItem task) = 0;
    virtual bool UpdateItem(QString treeName, ManagerDataItem task) = 0;
    virtual bool DeleteItem(QString treeName, int id) = 0;
};
Q_DECLARE_INTERFACE(IExtendableDataManager, "IExtendableDataManager v0.1")
//! @}
#endif // ITASKDBTOOLPLUGIN_H
