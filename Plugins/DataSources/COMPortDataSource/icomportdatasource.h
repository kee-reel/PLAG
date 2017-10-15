#ifndef ICOMPORTDATASOURCE_H
#define ICOMPORTDATASOURCE_H

#include "../../interfaces.h"

//! defgroup COMPortDataSource
//!     ingroup MainMenuPlugin_rel_m
//! defgroup COMPortDataSource_int Interface
//!     ingroup COMPortDataSource
//! defgroup COMPortDataSource_imp Implementation
//!     ingroup COMPortDataSource

//! addtogroup COMPortDataSource_int
//! {
class ICOMPortDataSource :
        public IDataSourcePlugin
{
public:
    // Write your interface methods here
};
//! }
Q_DECLARE_INTERFACE(ICOMPortDataSource, "ICOMPortDataSource")
#endif // ICOMPORTDATASOURCE_H
