#ifndef IEMPTYPLUGINMODEL_H
#define IEMPTYPLUGINMODEL_H

#include "../../System/MASS/interfaces.h"

class IEmptyPluginModel : public IPluginModel
{
public:
    virtual void TestFunc() = 0;
};
Q_DECLARE_INTERFACE(IEmptyPluginModel, "IEmptyPluginModel v0.1")

#endif // IEMPTYPLUGINMODEL_H
