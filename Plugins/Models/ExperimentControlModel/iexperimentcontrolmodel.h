#ifndef IEXPERIMENTCONTROLMODEL_H
#define IEXPERIMENTCONTROLMODEL_H

#include "../../interfaces.h"
#include "QtCharts"

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
    virtual QtCharts::QLineSeries *GetLineSeries() = 0;

    virtual void StartExperiment() = 0;
    virtual void StopExperiment() = 0;
};
//! }
Q_DECLARE_INTERFACE(IExperimentControlModel, "IExperimentControlModel")
#endif // IEXPERIMENTCONTROLMODEL_H
