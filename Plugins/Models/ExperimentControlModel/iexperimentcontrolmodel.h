#ifndef IEXPERIMENTCONTROLMODEL_H
#define IEXPERIMENTCONTROLMODEL_H

#include "../../interfaces.h"
#include "../../DataManagers/ModbusDeviceDataManager/imodbusdevicedatamanager.h"
#include "QtCharts"
#include "QSerialPort"
#include "QModbusDataUnit"

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
    class IDataChannel
    {
    public:
        enum ChannelMode
        {
            INPUT,
            OUTPUT,
            IN_OUT
        };

        virtual QString GetName() = 0;
        virtual QString SetName() = 0;
        virtual ChannelMode GetChannelMode() = 0;
        virtual bool SetChannelMode(ChannelMode channelMode) = 0;
        virtual QList<ChannelMode> GetAvailableModes() = 0;
        virtual QJsonObject GetExtraData() = 0;
        virtual void SetExtraData(QJsonObject object) = 0;
        virtual QtCharts::QLineSeries *GetLineSerie() = 0;
    };

    class IExperimentSetup
    {
        virtual QString GetExperimentSetupName() = 0;
        virtual void SetExperimentSetupName(QString name) = 0;
        virtual QMap<QString, IDataChannel*> GetDataChannels() = 0;
    };

    virtual QList<IExperimentSetup*> GetAvailableExperimentSetups() = 0;
    virtual void StartExperiment(IExperimentSetup *setup) = 0;
    virtual void StopExperiment() = 0;

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
};
//! }
Q_DECLARE_INTERFACE(IExperimentControlModel, "IExperimentControlModel")
#endif // IEXPERIMENTCONTROLMODEL_H
