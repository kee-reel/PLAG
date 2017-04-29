#ifndef IPOMODOROMODEL_H
#define IPOMODOROMODEL_H

#include "../MainMenuModelPlugin/interfaces.h"

template <class A>
class QVector;
class QAbstractItemModel;
class IPomodoroModel: public IModelPlugin
{
public:
    virtual QAbstractItemModel* GetModel() = 0;
    virtual QAbstractItemModel* GetInternalModel() = 0;
};
Q_DECLARE_INTERFACE(IPomodoroModel, "IPomodoroModel v0.1")

#endif // ITASKLISTMODEL_H
