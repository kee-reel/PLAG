#ifndef IHEARTRATEDEVICEMODEL_H
#define IHEARTRATEDEVICEMODEL_H

#include "../../interfaces.h"

//! defgroup HeartRateDeviceModel
//!     ingroup MainMenuPlugin_rel_m
//! defgroup HeartRateDeviceModel_int Interface
//!     ingroup HeartRateDeviceModel
//! defgroup HeartRateDeviceModel_imp Implementation
//!     ingroup HeartRateDeviceModel

//! addtogroup HeartRateDeviceModel_int
//! {
class IHeartRateDeviceModel :
    public IModelPlugin
{
public:
    // Write your interface methods here
    virtual void SetHbO2Data(float) = 0;
signals:
    void HeartbeatData(float);
    void TempoData(float);
	void TempoData12(float);
};
//! }
Q_DECLARE_INTERFACE(IHeartRateDeviceModel, "IHeartRateDeviceModel")
#endif // IHEARTRATEDEVICEMODEL_H

class IHeartRateDeviceModel :
    public IHeartRateDeviceModel
{
public:
	void TempoData12(float);
};
//! }
Q_DECLARE_INTERFACE(IHeartRateDeviceModel, "IHeartRateDeviceModel")
#endif // IHEARTRATEDEVICEMODEL_H
