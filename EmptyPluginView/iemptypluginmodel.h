#ifndef IEMPTYPLUGINMODEL_H
#define IEMPTYPLUGINMODEL_H

#include "../TimeKeeper/interfaces.h"

class IEmptyPluginModel : public IPluginModel
{
public:
    virtual void TestFunc();
};
Q_DECLARE_INTERFACE(IEmptyPluginModel, "IEmptyPluginModel v0.1")

#endif // IEMPTYPLUGINMODEL_H
