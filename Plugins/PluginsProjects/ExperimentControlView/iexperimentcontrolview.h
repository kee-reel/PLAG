#ifndef IEXPERIMENTCONTROLVIEW_H
#define IEXPERIMENTCONTROLVIEW_H

#include "../../interfaces.h"

//! defgroup ExperimentControlView
//!     ingroup MainMenuPlugin_rel_m
//! defgroup ExperimentControlView_int Interface
//!     ingroup ExperimentControlView
//! defgroup ExperimentControlView_imp Implementation
//!     ingroup ExperimentControlView

//! addtogroup ExperimentControlView_int
//! {
class IExperimentControlView :
        public IViewPlugin
{
public:
    // Write your interface methods here
};
//! }
Q_DECLARE_INTERFACE(IExperimentControlView, "IExperimentControlView")
#endif // IEXPERIMENTCONTROLVIEW_H
