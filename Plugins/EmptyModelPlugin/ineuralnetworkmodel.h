#ifndef IEMPTYPLUGINMODEL_H
#define IEMPTYPLUGINMODEL_H

#include "../MainMenuModelPlugin/interfaces.h"

class INeuralNetworkModel : public IModelPlugin
{
public:
    virtual void TestFunc() = 0;
};
Q_DECLARE_INTERFACE(INeuralNetworkModel, "INeuralNetworkModel v0.1")

#endif // IEMPTYPLUGINMODEL_H
