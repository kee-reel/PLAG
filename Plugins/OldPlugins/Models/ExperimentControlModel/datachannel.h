#ifndef DATACHANNEL_H
#define DATACHANNEL_H

#include <QtGlobal>
#include <QObject>

#include "iexperimentcontrolmodel.h"

class DataChannel : public IExperimentControlModel::IDataChannel
{
public:
    DataChannel();

    // IDataChannel interface
public:
    QString GetName() override;
    ChannelMode GetChannelMode() override;
    bool SetChannelMode(ChannelMode channelMode) override;
    QList<ChannelMode> GetAvailableModes() override;
    QJsonObject GetExtraData() override;
    void SetExtraData(QJsonObject object) override;
    QLineSeries *GetLineSerie() override;
};

#endif // DATACHANNEL_H
