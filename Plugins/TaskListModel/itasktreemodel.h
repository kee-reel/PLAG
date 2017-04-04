#ifndef ITASKLISTMODEL_H
#define ITASKLISTMODEL_H

#include "../MainMenuModelPlugin/interfaces.h"

template <class A>
class QVector;
class QAbstractItemModel;
class ITreeModel : public IModelPlugin
{
public:
    virtual QString GetDataName() = 0;
    virtual QAbstractItemModel* GetTreeModel() = 0;
};
Q_DECLARE_INTERFACE(ITreeModel, "ITreeModel v0.1")

#endif // ITASKLISTMODEL_H
