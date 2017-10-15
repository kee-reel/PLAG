#ifndef IGRIDMAINMENUVIEW_H
#define IGRIDMAINMENUVIEW_H

#include "../../interfaces.h"

//! defgroup GridMainMenuView
//!     ingroup MainMenuPlugin_rel_m
//! defgroup GridMainMenuView_int Interface
//!     ingroup GridMainMenuView
//! defgroup GridMainMenuView_imp Implementation
//!     ingroup GridMainMenuView

//! addtogroup GridMainMenuView_int
//! {
class IGridMainMenuView :
        public IViewPlugin
{
public:
    // Write your interface methods here
};
//! }
Q_DECLARE_INTERFACE(IGridMainMenuView, "IGridMainMenuView")
#endif // IGRIDMAINMENUVIEW_H
