#ifndef IHEARTRATEDEVICEMODEL_H
#define IHEARTRATEDEVICEMODEL_H

#include <QtCore>

//! defgroup HeartRateDeviceModel_int Interface
//!     ingroup HeartRateDeviceModel
//! defgroup HeartRateDeviceModel_imp Implementation
//!     ingroup HeartRateDeviceModel

//! addtogroup HeartRateDeviceModel_int
//! {
class IHeartRateDeviceModel
{
public slots:
    virtual void SetHbO2Data(float) = 0;
    virtual void ChooseDataIndex(int) = 0;
    virtual void StartTracking() = 0;
    virtual void StopTracking() = 0;

signals:
    void HeartbeatData(float);
    void TempoData(float);
};
//! }
Q_DECLARE_INTERFACE(IHeartRateDeviceModel, "IHeartRateDeviceModel")
#endif // IHEARTRATEDEVICEMODEL_H
