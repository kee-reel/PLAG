#ifndef IMAINMENUMODULE_H
#define IMAINMENUMODULE_H

#include <QtCore>

#include "../PluginsCommon/iplugin.h"

//! \defgroup MainMenuPlugin MainMenuPlugin
//!     \ingroup MASS
//! \defgroup MainMenuPlugin_imp Implementation
//!     \ingroup MainMenuPlugin
//! \defgroup MainMenuPlugin_int Interfaces
//!     \ingroup MainMenuPlugin
//! \defgroup MainMenuPlugin_rel Related plugins
//!     \ingroup MainMenuPlugin
//!
//!     \defgroup MainMenuPlugin_rel_ds DataSource plugins
//!         \ingroup MainMenuPlugin_rel
//!     \defgroup MainMenuPlugin_rel_dm DataManager plugins
//!         \ingroup MainMenuPlugin_rel
//!     \defgroup MainMenuPlugin_rel_m Model plugins
//!         \ingroup MainMenuPlugin_rel
//!     \defgroup MainMenuPlugin_rel_v View plugins
//!         \ingroup MainMenuPlugin_rel

//! \addtogroup MainMenuPlugin_int
//! @{

//! \brief Interface that describes MainMenu plugin class.
//!
//! Main Menu is plugin that should implement interaction with menu.
//! Menu contains items that describes plugins that now included in
//! programm.
class IMainMenuModel
{
public:
    //! \brief Structure that contains some info about menu item.
    //!
    //! Menu item describes plugin that implements IModelPlugin. All items presented in tree structure.
    //! Every item contains information about model plugin, related model plugins and view plugins that
    //! relates to plugin.
    class IMenuItem
    {
    public:
        //! \brief Meta information about plugin.
        virtual const MetaInfo &getMeta() = 0;
        //! \brief Model plugins that relate to plugin.
        virtual QVector<QWeakPointer<IMenuItem>> getConnectedItems() = 0;
    protected:
        virtual ~IMenuItem() {}
    };

    //! \brief Returns root menu item.
    virtual QVector<QWeakPointer<IMenuItem>> getMenuItems() = 0;

    //! \brief Runs view plugin that relates to item.
    //! \param Model plugin that contains view plugin to run.
    //! \param View plugin that needs to open.
    virtual void openItem(QWeakPointer<IMenuItem> item) = 0;

protected:
    virtual ~IMainMenuModel() {}
};
Q_DECLARE_INTERFACE(IMainMenuModel, "IMainMenuModule v0.1")
Q_DECLARE_METATYPE(IMainMenuModel*)
//! }@
#endif // IMAINMENUMODULE_H
