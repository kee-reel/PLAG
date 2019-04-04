#ifndef IEXPERIMENTCONTROLMODEL_H
#define IEXPERIMENTCONTROLMODEL_H

#include "imodbusdevicedatamanager.h"
#include <QtCore>
#include <QtCharts>
#include <QSerialPort>
#include <QModbusDataUnit>

//! defgroup ExperimentControlModel
//!     ingroup MainMenuPlugin_rel_m
//! defgroup ExperimentControlModel_int Interface
//!     ingroup ExperimentControlModel
//! defgroup ExperimentControlModel_imp Implementation
//!     ingroup ExperimentControlModel

//! addtogroup ExperimentControlModel_int
//! {
class IExperimentControlModel
{
public:

    virtual bool GetExperimentState() = 0;
    virtual void StartExperiment() = 0;
    virtual void StopExperiment() = 0;
    virtual QDateTime GetExperimentStartTime() = 0;
    virtual bool SaveExperimentData(QString filename) = 0;

    struct PortInfo
    {
        QString portName;
        int productId;
        int vendorId;
    };

    virtual QAbstractItemModel *GetAvailablePorts() = 0;
    virtual void UpdateAvailablePorts() = 0;
    virtual bool OpenPort(int modelIndex, IModbusDeviceDataManager::ConnectionSettings connectionSettings) = 0;
    virtual void ScanForDevice(int deviceId) = 0;
    virtual QAbstractItemModel *GetAvailableModbusDeviceHandlers() = 0;
    virtual QAbstractItemModel *GetAvailableModbusDeviceNames() = 0;
    virtual void ClosePort(int modelIndex) = 0;

    struct RegstersPack
    {
        QModbusDataUnit::RegisterType type;
        int start;
        int count;
        int updateInterval;
    };

    virtual QAbstractItemModel *GetRegisterPacks() = 0;
    virtual void SetDeviceForSetup(QString deviceName) = 0;
    virtual void AddRegisterPack(RegstersPack pack) = 0;

    virtual QList<QLineSeries*> GetRegistersLineSeries() = 0;

signals:
    void ErrorOccurred(QString error);
    void ExperimentStateChanged(bool state);
};
//! }
Q_DECLARE_INTERFACE(IExperimentControlModel, "IExperimentControlModel")
#endif // IEXPERIMENTCONTROLMODEL_H
