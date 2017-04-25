#ifndef ITASKSKETCHMODEL_H
#define ITASKSKETCHMODEL_H

#include "../MainMenuModelPlugin/interfaces.h"

template <class A>
class QVector;
class QAbstractItemModel;
class ITaskSketchModel: public IModelPlugin
{
public:
    virtual QAbstractItemModel* GetModel() = 0;
    virtual QAbstractItemModel* GetInternalModel() = 0;
    virtual void ConvertSketchToTask(int sketchId) = 0;
signals:
    void ConvertTaskToSketch(int);
};
Q_DECLARE_INTERFACE(ITaskSketchModel, "ITaskSketchModel v0.1")

#endif // ITASKLISTMODEL_H
