#ifndef IHARDWAREDATAMANAGER_H
#define IHARDWAREDATAMANAGER_H

#include "../../interfaces.h"

//! defgroup HardwareDataManager
//!     ingroup MainMenuPlugin_rel_m
//! defgroup HardwareDataManager_int Interface
//!     ingroup HardwareDataManager
//! defgroup HardwareDataManager_imp Implementation
//!     ingroup HardwareDataManager

//! addtogroup HardwareDataManager_int
//! {
class IHardwareDataManager :
        public IDataManagerPlugin
{
public:
    // Write your interface methods here
};
//! }
Q_DECLARE_INTERFACE(IHardwareDataManager, "IHardwareDataManager")
#endif // IHARDWAREDATAMANAGER_H
