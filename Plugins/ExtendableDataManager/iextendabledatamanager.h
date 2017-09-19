#ifndef ITASKDBTOOLPLUGIN_H
#define ITASKDBTOOLPLUGIN_H

#include "../../Plugins/MainMenuModelPlugin/interfaces.h"

template <class T> class QVector;
template <class T> class QList;
template <class A, class B> class QMap;
class QVariant;
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
    class ManagerDataItem{
    public:
        int id;
        QMap<QString, QVector<QVariant> > dataChunks;
    };

    class IDataTypeEditor
    {
    public:
        virtual void SetValue(QVariant value) = 0;
        virtual QVariant GetValue() = 0;
        virtual QWidget* GetWidget() = 0;
    };

    virtual void RegisterDataTypeEditor(QString relation, QString field, IDataTypeEditor *delegate) = 0;
    virtual IDataTypeEditor* GetDataTypeEditor(QString relation, QString field) = 0;

    virtual QList<ManagerDataItem> GetDataList(QString treeName) = 0;
    virtual ManagerDataItem GetDataItem(QString treeName, int id) = 0;
    virtual QMap<QString, QVariant::Type> GetTableHeader(QString treeName) = 0;

    virtual QAbstractItemModel *GetDataModel(QString treeName) = 0;

    virtual bool SetRelation(QString mainName, QString relationName,
                             QMap<QString, QVariant::Type> fields, QVector<QVariant> defaultData) = 0;
    virtual bool DeleteRelation(QString mainName, QString relationName) = 0;
    virtual bool SetActiveRelation(QString mainName, QString relationName) = 0;

    virtual int AddItem(QString treeName, ManagerDataItem task) = 0;
    virtual bool UpdateItem(QString treeName, ManagerDataItem task) = 0;
    virtual bool DeleteItem(QString treeName, int id) = 0;
};
Q_DECLARE_INTERFACE(IExtendableDataManager, "IExtendableDataManager v0.1")
//! @}
#endif // ITASKDBTOOLPLUGIN_H
