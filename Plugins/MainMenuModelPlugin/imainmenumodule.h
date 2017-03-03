#ifndef IMAINMENUMODULE_H
#define IMAINMENUMODULE_H

#include "../../System/MASS/interfaces.h"

template<class Type>
class QList;
class IMainMenuPluginModel : public IRootModelPlugin
{ 
public:
    virtual QList<MetaInfo*> GetChildPlugins() = 0;
    virtual void RunPlugin(int pluginId) = 0;
};
Q_DECLARE_INTERFACE(IMainMenuPluginModel, "IMainMenuModule v0.1")
#endif // IMAINMENUMODULE_H
