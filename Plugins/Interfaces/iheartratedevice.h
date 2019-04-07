#ifndef IHeartRateDevice_H
#define IHeartRateDevice_H

#include <QtCore>

//!  \defgroup HeartRateDevice HeartRateDevice
//!      \ingroup Plugins
//!  \defgroup HeartRateDevice_int Interface
//!      \ingroup HeartRateDevice
//!  \defgroup HeartRateDevice_imp Implementation
//!      \ingroup HeartRateDevice
//!  \defgroup HeartRateDevice_dep Dependent plugins
//!      \ingroup HeartRateDevice

//!  \addtogroup HeartRateDevice_int
//!  \{
class IHeartRateDevice
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
//!  \}
Q_DECLARE_INTERFACE(IHeartRateDevice, "IHeartRateDevice")
#endif // IHeartRateDevice_H
