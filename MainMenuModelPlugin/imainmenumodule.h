#ifndef IMAINMENUMODULE_H
#define IMAINMENUMODULE_H

#include "../TimeKeeper/interfaces.h"

class QStringList;
class IMainMenuPluginModel : public IPluginModel
{
public:
    virtual QStringList GetTasks() = 0;
};
Q_DECLARE_INTERFACE(IMainMenuPluginModel, "IMainMenuModule v0.1")
#endif // IMAINMENUMODULE_H
