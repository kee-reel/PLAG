#include "heartratedevice.h"

HeartRateDevice::HeartRateDevice() :
    PluginBase()
{
}

HeartRateDevice::~HeartRateDevice()
{
}

void HeartRateDevice::onAllReferencesSet()
{
    for(auto iter = m_referencesMap.begin(); iter != m_referencesMap.end(); ++iter)
    {
        auto&& interfaceName = iter.key();
        auto&& plugin = iter.value();
        if(!QString::compare(interfaceName, "IModbusDataReader", Qt::CaseInsensitive))
        {
            auto instance = plugin->getObject();
            deviceManager = qobject_cast<IModbusDataReader*>(instance);
        }
        else if(!QString::compare(interfaceName, "IFuzzyLogicManager", Qt::CaseInsensitive))
        {
            auto instance = plugin->getObject();
            fuzzyLogic = qobject_cast<IFuzzyLogicManager*>(instance);
        }
    }
    PluginBase::onAllReferencesSet();
}

void HeartRateDevice::onAllReferencesReady()
{
    savedBeatsCount = 10;
    minLowerValue = 100000;
    maxLowerValue = 0;

    //        CO2Data = heartData.at(1);
    //        connect(CO2Data, &QLineSeries::pointAdded, this, [=](int index)
    //        {
    //            qDebug() << CO2Data->at(index);
    //        });

    qDebug() << "FUZZY SETUP";
    fuzzyHR = fuzzyLogic->MakeInputVariable("HR", 40, 200);
    lowHRSet = fuzzyLogic->MakeSet("Low", fuzzyLogic->MakeMembershipFunc(IFuzzyLogicManager::IMembershipFunc::Triangular,
                                   QList<float>() = {40, 40, 120}));
    medHRSet = fuzzyLogic->MakeSet("Medium", fuzzyLogic->MakeMembershipFunc(IFuzzyLogicManager::IMembershipFunc::Triangular,
                                   QList<float>() = {55, 120, 185}));
    highHRSet = fuzzyLogic->MakeSet("High", fuzzyLogic->MakeMembershipFunc(IFuzzyLogicManager::IMembershipFunc::Triangular,
                                    QList<float>() = {120, 200, 200}));
    fuzzyHR->AddSet(lowHRSet);
    fuzzyHR->AddSet(medHRSet);
    fuzzyHR->AddSet(highHRSet);
    fuzzyCO2 = fuzzyLogic->MakeInputVariable("CO2", 85, 100);
    lowCO2Set = fuzzyLogic->MakeSet("Low", fuzzyLogic->MakeMembershipFunc(IFuzzyLogicManager::IMembershipFunc::Triangular,
                                    QList<float>() = {85, 85, 90}));
    medCO2Set = fuzzyLogic->MakeSet("Medium", fuzzyLogic->MakeMembershipFunc(IFuzzyLogicManager::IMembershipFunc::Triangular,
                                    QList<float>() = {87, 93, 95}));
    highCO2Set = fuzzyLogic->MakeSet("High", fuzzyLogic->MakeMembershipFunc(IFuzzyLogicManager::IMembershipFunc::Triangular,
                                     QList<float>() = {91, 100, 100}));
    fuzzyCO2->AddSet(lowCO2Set);
    fuzzyCO2->AddSet(medCO2Set);
    fuzzyCO2->AddSet(highCO2Set);
    fuzzyTempo = fuzzyLogic->MakeOutputVariable("Tempo", 0, 100);
    lowTempoSet = fuzzyLogic->MakeSet("Low", fuzzyLogic->MakeMembershipFunc(IFuzzyLogicManager::IMembershipFunc::Triangular,
                                      QList<float>() = {0, 0, 40}));
    medTempoSet = fuzzyLogic->MakeSet("Medium", fuzzyLogic->MakeMembershipFunc(IFuzzyLogicManager::IMembershipFunc::Triangular,
                                      QList<float>() = {30, 50, 70}));
    highTempoSet = fuzzyLogic->MakeSet("High", fuzzyLogic->MakeMembershipFunc(IFuzzyLogicManager::IMembershipFunc::Triangular,
                                       QList<float>() = {60, 100, 100}));
    fuzzyTempo->AddSet(lowTempoSet);
    fuzzyTempo->AddSet(medTempoSet);
    fuzzyTempo->AddSet(highTempoSet);
    IFuzzyLogicManager::IFuzzyRule *rule = fuzzyLogic->MakeRule();
    rule->AddCondition(fuzzyHR, lowHRSet);
    rule->AddCondition(fuzzyCO2, lowCO2Set);
    rule->AddConsequence(fuzzyTempo, lowTempoSet);
    fuzzyTempo->AddRule(rule);
    rule = fuzzyLogic->MakeRule();
    rule->AddCondition(fuzzyHR, medHRSet);
    rule->AddCondition(fuzzyCO2, medCO2Set);
    rule->AddConsequence(fuzzyTempo, medTempoSet);
    fuzzyTempo->AddRule(rule);
    rule = fuzzyLogic->MakeRule();
    rule->AddCondition(fuzzyHR, highHRSet);
    rule->AddCondition(fuzzyCO2, highCO2Set);
    rule->AddConsequence(fuzzyTempo, highTempoSet);
    fuzzyTempo->AddRule(rule);
    fuzzyTempo->AddInput(fuzzyHR);
    fuzzyHR->SetValue(41);
    qDebug() << "HR:" << heartRate << "Tempo:" << fuzzyTempo->GetOutput();
    //fuzzyTempo->AddInput(fuzzyCO2);
    //    fuzzyHR->SetValue(100);
    //    fuzzyCO2->SetValue(50);

    PluginBase::onAllReferencesReady();
}

void HeartRateDevice::AddHeartbeat(QPointF point)
{
    beatsList.append(point.x());

    if(beatsList.count() >= savedBeatsCount)
        beatsList.removeFirst();

    float time = beatsList.last() - beatsList.first();
    heartRate = (beatsList.count() * (60 / time));
    fuzzyHR->SetValue(heartRate);
    float tempo = 100 - fuzzyTempo->GetOutput();
    qDebug() << "HR:" << heartRate << "Tempo:" << tempo;
    emit HeartbeatData(heartRate);
    emit TempoData(tempo);
}

void HeartRateDevice::CompareValues(int index)
{
    QPointF point = HRData->at(index);
    float y = point.y();
    minLowerValue = y < minLowerValue ? y : minLowerValue + (y-minLowerValue)/savedBeatsCount;
    maxLowerValue = y > maxLowerValue ? y : maxLowerValue - (maxLowerValue-y)/savedBeatsCount;

    if(y < (minLowerValue + (maxLowerValue - minLowerValue)/2) )
    {
        if(!isFalling)
        {
            isFalling = true;
            AddHeartbeat(point);
        }
    }
    else
    {
        if(isFalling)
        {
            isFalling = false;
        }
    }
}

void HeartRateDevice::SetHbO2Data(float value)
{
    fuzzyCO2->SetValue(value);
}

void HeartRateDevice::ChooseDataIndex(int index)
{
    heartRateDataIndex = index;
}

void HeartRateDevice::StartTracking()
{
    heartData = deviceManager->GetRegistersLineSeries();
    HRData = heartData.at(heartRateDataIndex);
    connect(HRData, &QLineSeries::pointAdded, this, &HeartRateDevice::CompareValues);
}

void HeartRateDevice::StopTracking()
{
    disconnect(HRData, &QLineSeries::pointAdded, this, &HeartRateDevice::CompareValues);
}
