#ifndef IMAINMENUMODULE_H
#define IMAINMENUMODULE_H

#include "interfaces.h"
template<class Type>
class QList;
//! \defgroup MainMenuModule MainMenuModule
//! \ingroup MASS
//! \brief MainMenuModules application module.
//! @{

//!
//! \brief The IMainMenuPluginModel class
//!
class IMainMenuPluginModel : public IModelPlugin
{ 
public:
    //! \brief Structure that contains some info about menu item.
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
