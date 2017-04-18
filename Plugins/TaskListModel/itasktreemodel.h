#ifndef ITASKLISTMODEL_H
#define ITASKLISTMODEL_H

#include "../MainMenuModelPlugin/interfaces.h"

class QVariant;
class QAbstractItemModel;
template <class A> class QVector;
template <class A, class B> class QMap;
enum QVariant::Type;

class ITaskTreeModel : public IModelPlugin
{
public:
    virtual QString GetDataName() = 0;
    virtual void AttachRelation(QMap<QString, QVariant::Type> relationStruct, QString relationName, QVector<QVariant> defaultData) = 0;
    virtual void SetActiveRelation(QString relationName) = 0;
    virtual QAbstractItemModel* GetTreeModel() = 0;
};
Q_DECLARE_INTERFACE(ITaskTreeModel, "ITaskTreeModel v0.1")

#endif // ITASKLISTMODEL_H
