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
    class IDataChannel
    {
    public:
        enum ChannelMode
        {
            IN,
            OUT,
            IN_OUT
        };

        virtual QString GetId() = 0;
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

signals:
    void ErrorOccurred(QString error);
};
//! }
Q_DECLARE_INTERFACE(IExperimentControlModel, "IExperimentControlModel")
#endif // IEXPERIMENTCONTROLMODEL_H
