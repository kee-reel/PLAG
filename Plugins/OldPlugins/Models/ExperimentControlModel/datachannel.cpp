#include "datachannel.h"

DataChannel::DataChannel()
{
}

QString DataChannel::GetName()
{

}

IExperimentControlModel::IDataChannel::ChannelMode DataChannel::GetChannelMode()
{
}

bool DataChannel::SetChannelMode(IExperimentControlModel::IDataChannel::ChannelMode channelMode)
{
}

QList<IExperimentControlModel::IDataChannel::ChannelMode> DataChannel::GetAvailableModes()
{
}

QJsonObject DataChannel::GetExtraData()
{
}

void DataChannel::SetExtraData(QJsonObject object)
{
}

QLineSeries *DataChannel::GetLineSerie()
{
}
