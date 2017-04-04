#ifndef ITASKLISTMODEL_H
#define ITASKLISTMODEL_H

#include "../MainMenuModelPlugin/interfaces.h"

template <class A>
class QVector;
class QAbstractItemModel;
class ITaskSketchModel: public IModelPlugin
{
public:
    virtual QAbstractItemModel* GetModel() = 0;
};
Q_DECLARE_INTERFACE(ITaskSketchModel, "ITaskSketchModel v0.1")

#endif // ITASKLISTMODEL_H
