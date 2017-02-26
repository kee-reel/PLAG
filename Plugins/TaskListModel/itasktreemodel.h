#ifndef ITASKLISTMODEL_H
#define ITASKLISTMODEL_H

#include "../../System/MASS/interfaces.h"

template <class A>
class QVector;
class QAbstractItemModel;
class ITreeModel : public IPluginModel
{
public:
    /// Get all data
    virtual QAbstractItemModel* GetTreeModel() = 0;
};
Q_DECLARE_INTERFACE(ITreeModel, "ITreeModel v0.1")

#endif // ITASKLISTMODEL_H
