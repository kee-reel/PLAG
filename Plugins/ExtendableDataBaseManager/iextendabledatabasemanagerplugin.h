#ifndef ITASKDBTOOLPLUGIN_H
#define ITASKDBTOOLPLUGIN_H

#include "../../Plugins/MainMenuModelPlugin/interfaces.h"

template <class T> class QVector;
template <class T> class QList;
template <class A, class B> class QMap;
class QVariant;
enum QVariant::Type;
class QAbstractItemModel;

class IExtendableDataBaseManagerPlugin : public IDataManagerPlugin
{
public:
    class ManagerDataItem{
    public:
        int id;
        QMap<QString, QVector<QVariant>> dataChunks;
    };

    virtual QList<ManagerDataItem> GetDataList(QString treeName) = 0;
    virtual ManagerDataItem GetDataItem(QString treeName, int id) = 0;
    virtual QAbstractItemModel *GetDataModel(QString treeName) = 0;
    virtual QMap<QString, QVariant::Type> GetTableHeader(QString treeName) = 0;

    virtual bool SetRelation(QString mainName, QString relationName, QMap<QString, QVariant::Type> fields, QVector<QVariant> defaultData) = 0;
    virtual bool DeleteRelation(QString mainName, QString relationName) = 0;
    virtual bool SetActiveRelation(QString mainName, QString relationName) = 0;

    virtual int AddItem(QString treeName, ManagerDataItem task) = 0;
    virtual bool EditItem(QString treeName, ManagerDataItem task) = 0;
    virtual bool DeleteItem(QString treeName, int id) = 0;
};
Q_DECLARE_INTERFACE(IExtendableDataBaseManagerPlugin, "IExtendableDataBaseManagerPlugin v0.1")

#endif // ITASKDBTOOLPLUGIN_H
