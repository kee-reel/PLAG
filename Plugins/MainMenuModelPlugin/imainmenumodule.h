#ifndef IMAINMENUMODULE_H
#define IMAINMENUMODULE_H

#include "interfaces.h"
template<class Type>
class QList;
//! \defgroup MainMenuModule MainMenuModule
//! \ingroup MASS
//! \brief MainMenuModules application module.
//! @{

//! \brief Interface that describes MainMenu plugin class.
//!
//! Main Menu is plugin that should implement interaction with menu.
//! Menu contains items that describes plugins that now included in
//! programm.
class IMainMenuPluginModel : public IModelPlugin
{ 
public:
    //! \brief Structure that contains some info about menu item.
    //!
    //! Menu item describes plugin that implements IModelPlugin. All items presented in tree structure.
    //! Every item contains information about model plugin, related model plugins and view plugins that
    //! relates to plugin.
    struct MenuItem{
        //! \brief Meta information about plugin.
        MetaInfo* meta;
        //! \brief View plugins that relate to plugin.
        QList<MetaInfo*> ViewItems;
        //! \brief Model plugins that relate to plugin.
        QList<MenuItem*> SubItems;
    };

    //! \brief Returns root menu item (all items presented in tree structure).
    virtual MenuItem* GetRootMenuItem() = 0;

    //! \brief Runs view plugin that relates to item.
    //! \param Model plugin that contains view plugin to run.
    //! \param View plugin that needs to open.
    virtual void RunItem(MenuItem* item, MetaInfo *viewMeta) = 0;
};
Q_DECLARE_INTERFACE(IMainMenuPluginModel, "IMainMenuModule v0.1")
//! }@
#endif // IMAINMENUMODULE_H
