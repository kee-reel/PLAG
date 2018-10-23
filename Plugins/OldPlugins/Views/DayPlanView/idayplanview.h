#ifndef IDAYPLANVIEW_H
#define IDAYPLANVIEW_H

#include "../../interfaces.h"

//! defgroup DayPlanView
//!     ingroup MainMenuPlugin_rel_m
//! defgroup DayPlanView_int Interface
//!     ingroup DayPlanView
//! defgroup DayPlanView_imp Implementation
//!     ingroup DayPlanView

//! addtogroup DayPlanView_int
//! {
class IDayPlanView :
        public IViewPlugin
{
public:
    // Write your interface methods here
};
//! }
Q_DECLARE_INTERFACE(IDayPlanView, "IDayPlanView")
#endif // IDAYPLANVIEW_H
