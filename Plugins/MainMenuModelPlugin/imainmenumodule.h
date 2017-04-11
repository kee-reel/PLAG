#ifndef IMAINMENUMODULE_H
#define IMAINMENUMODULE_H

#include "interfaces.h"

template<class Type>
class QList;
class IMainMenuPluginModel : public IModelPlugin
{ 
public:
    struct MenuItem{
        MetaInfo* meta;
        QList<MetaInfo*> ViewItems;
        QList<MenuItem*> SubItems;
    };

    virtual MenuItem* GetRootMenuItem() = 0;
    virtual void RunItem(MenuItem* item, MetaInfo *viewMeta) = 0;
};
Q_DECLARE_INTERFACE(IMainMenuPluginModel, "IMainMenuModule v0.1")
#endif // IMAINMENUMODULE_H
