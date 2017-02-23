#ifndef ITASKLISTMODEL_H
#define ITASKLISTMODEL_H

#include "../../System/MASS/interfaces.h"
#include "../../System/TaskDBToolPlugin/itaskdbtoolplugin.h"

template <class A>
class QVector;
class QAbstractItemModel;
class ITaskTreeModel : public IPluginModel
{
public:
    /// Get all data
    virtual QAbstractItemModel* GetTaskTree() = 0;
};
Q_DECLARE_INTERFACE(ITaskTreeModel, "ITaskTreeModel v0.1")

#endif // ITASKLISTMODEL_H
