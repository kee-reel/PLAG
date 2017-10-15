#ifndef IEXPERIMENTCONTROLMODEL_H
#define IEXPERIMENTCONTROLMODEL_H

#include "../../interfaces.h"

//! defgroup ExperimentControlModel
//!     ingroup MainMenuPlugin_rel_m
//! defgroup ExperimentControlModel_int Interface
//!     ingroup ExperimentControlModel
//! defgroup ExperimentControlModel_imp Implementation
//!     ingroup ExperimentControlModel

//! addtogroup ExperimentControlModel_int
//! {
class IExperimentControlModel :
        public IModelPlugin
{
public:
    // Write your interface methods here
};
//! }
Q_DECLARE_INTERFACE(IExperimentControlModel, "IExperimentControlModel")
#endif // IEXPERIMENTCONTROLMODEL_H
