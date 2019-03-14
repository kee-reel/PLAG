#ifndef IHEARTRATEDEVICEVIEW_H
#define IHEARTRATEDEVICEVIEW_H

#include "../../interfaces.h"

//! defgroup HeartRateDeviceView
//!     ingroup MainMenuPlugin_rel_m
//! defgroup HeartRateDeviceView_int Interface
//!     ingroup HeartRateDeviceView
//! defgroup HeartRateDeviceView_imp Implementation
//!     ingroup HeartRateDeviceView

//! addtogroup HeartRateDeviceView_int
//! {
class IHeartRateDeviceView :
        public IViewPlugin
{
public:
    // Write your interface methods here
};
//! }
Q_DECLARE_INTERFACE(IHeartRateDeviceView, "IHeartRateDeviceView")
#endif // IHEARTRATEDEVICEVIEW_H
