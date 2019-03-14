#include "heartratedevicemodel.h"

HeartRateDeviceModel::HeartRateDeviceModel()
{
    // myReferencedPlugin = nullptr;
    openedView = nullptr;
    openedModel = nullptr;
    fuzzyLogic = nullptr;
    deviceManager = nullptr;
    /*
    ui->setupUi(this);
    */
}

HeartRateDeviceModel::~HeartRateDeviceModel()
{
}

void HeartRateDeviceModel::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void HeartRateDeviceModel::OnAllSetup()
{
}

QString HeartRateDeviceModel::GetLastError()
{
}

void HeartRateDeviceModel::AddReferencePlugin(PluginInfo *pluginInfo)
{
    /* Select your reference plugin case and get it. For example:
        case PLUGINMODEL:{
            myReferencedPlugin = qobject_cast<ISomePlugin*>(pluginInfo->Instance);
            if(!myReferencedPlugin)
            {
                qDebug() << pluginInfo->Meta->Name << "is not ISomePlugin.";
                return;
            }
            qDebug() << "ISomePlugin succesfully set.";
            connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
        } break;
    */
    switch(pluginInfo->Meta->Type)
    {
        case VIEWPLUGIN:
        {
            relatedViewPlugins.append(pluginInfo);
            qDebug() << "New IViewPlugin added (" << pluginInfo->Meta->Name << ").";
            connect(pluginInfo->Instance, SIGNAL( OnClose(PluginInfo*) ), SLOT( ReferencePluginClosed(PluginInfo*) ));
        } break;

        case MODELPLUGIN:
        {
            relatedModelPlugins.append(pluginInfo);
            qDebug() << "New IModelPlugin added (" << pluginInfo->Meta->Name << ").";
            connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
            IExperimentControlModel *deviceManagerBuf = qobject_cast<IExperimentControlModel*>(pluginInfo->Instance);

            if(deviceManagerBuf)
            {
                deviceManager = deviceManagerBuf;
                qDebug() << "IExperimentControlModel succesfully set.";
                connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
            }

            IFuzzyLogicModel *fuzzyLogicBuf = qobject_cast<IFuzzyLogicModel*>(pluginInfo->Instance);

            if(fuzzyLogicBuf)
            {
                fuzzyLogic = fuzzyLogicBuf;
                qDebug() << "IFuzzyLogicModel succesfully set.";
                connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
            }
        } break;

        case COREPLUGIN:
        {
            pluginInfo->Plugin.model->AddReferencePlugin(this->pluginInfo);
        } break;

        case DATAMANAGERPLUGIN:
        {
        } break;
    }
}

void HeartRateDeviceModel::ReferencePluginClosed(PluginInfo *pluginInfo)
{
}

void HeartRateDeviceModel::InitSystems()
{
    heartData = deviceManager->GetRegistersLineSeries();
    savedBeatsCount = 10;
    minLowerValue = 100000;
    maxLowerValue = 0;

    if(heartData.length() != 0)
    {
        HRData = heartData.at(0);
        connect(HRData, &QLineSeries::pointAdded, this, [=](int index)
        {
            CompareValues(HRData->at(index));
        });
        //        CO2Data = heartData.at(1);
        //        connect(CO2Data, &QLineSeries::pointAdded, this, [=](int index)
        //        {
        //            qDebug() << CO2Data->at(index);
        //        });
    }

    qDebug() << "FUZZY SETUP";
    fuzzyHR = fuzzyLogic->MakeInputVariable("HR", 40, 200);
    lowHRSet = fuzzyLogic->MakeSet("Low", fuzzyLogic->MakeMembershipFunc(IFuzzyLogicModel::IMembershipFunc::Triangular,
                                   QList<float>() = {40, 40, 120}));
    medHRSet = fuzzyLogic->MakeSet("Medium", fuzzyLogic->MakeMembershipFunc(IFuzzyLogicModel::IMembershipFunc::Triangular,
                                   QList<float>() = {55, 120, 185}));
    highHRSet = fuzzyLogic->MakeSet("High", fuzzyLogic->MakeMembershipFunc(IFuzzyLogicModel::IMembershipFunc::Triangular,
                                    QList<float>() = {120, 200, 200}));
    fuzzyHR->AddSet(lowHRSet);
    fuzzyHR->AddSet(medHRSet);
    fuzzyHR->AddSet(highHRSet);
    fuzzyCO2 = fuzzyLogic->MakeInputVariable("CO2", 85, 100);
    lowCO2Set = fuzzyLogic->MakeSet("Low", fuzzyLogic->MakeMembershipFunc(IFuzzyLogicModel::IMembershipFunc::Triangular,
                                    QList<float>() = {85, 85, 90}));
    medCO2Set = fuzzyLogic->MakeSet("Medium", fuzzyLogic->MakeMembershipFunc(IFuzzyLogicModel::IMembershipFunc::Triangular,
                                    QList<float>() = {87, 93, 95}));
    highCO2Set = fuzzyLogic->MakeSet("High", fuzzyLogic->MakeMembershipFunc(IFuzzyLogicModel::IMembershipFunc::Triangular,
                                     QList<float>() = {91, 100, 100}));
    fuzzyCO2->AddSet(lowCO2Set);
    fuzzyCO2->AddSet(medCO2Set);
    fuzzyCO2->AddSet(highCO2Set);
    fuzzyTempo = fuzzyLogic->MakeOutputVariable("Tempo", 0, 100);
    lowTempoSet = fuzzyLogic->MakeSet("Low", fuzzyLogic->MakeMembershipFunc(IFuzzyLogicModel::IMembershipFunc::Triangular,
                                      QList<float>() = {0, 0, 40}));
    medTempoSet = fuzzyLogic->MakeSet("Medium", fuzzyLogic->MakeMembershipFunc(IFuzzyLogicModel::IMembershipFunc::Triangular,
                                      QList<float>() = {30, 50, 70}));
    highTempoSet = fuzzyLogic->MakeSet("High", fuzzyLogic->MakeMembershipFunc(IFuzzyLogicModel::IMembershipFunc::Triangular,
                                       QList<float>() = {60, 100, 100}));
    fuzzyTempo->AddSet(lowTempoSet);
    fuzzyTempo->AddSet(medTempoSet);
    fuzzyTempo->AddSet(highTempoSet);
    IFuzzyLogicModel::IFuzzyRule *rule = fuzzyLogic->MakeRule();
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
}

void HeartRateDeviceModel::AddHeartbeat(QPointF point)
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

void HeartRateDeviceModel::CompareValues(QPointF point)
{
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

bool HeartRateDeviceModel::Open(IModelPlugin *parent)
{
    InitSystems();
    qDebug() << "HeartRateDeviceModel open.";

    if(relatedViewPlugins.count() == 0)
    {
        qDebug() << "!HeartRateDeviceModel hasn't any views!";
        return false;
    }

    openedView = relatedViewPlugins.first();
    qDebug() << "HeartRateDeviceModel opens related view " << openedView->Meta->Name;

    if(!openedView->Plugin.view->Open(this))
    {
        qDebug() << "!Can't open first view!";
        openedView = nullptr;
        return false;
    }

    return true;
}

void HeartRateDeviceModel::Close()
{
    qDebug() << "HeartRateDeviceModel close.";

    if(openedView != nullptr && !openedView->Plugin.view->Close())
    {
        qDebug() << "View plugin" << openedView->Meta->Name
                 << "not closed, but model closing anyway.";
    }

    if(openedModel != nullptr)
        openedView->Plugin.view->Close();

    openedView = nullptr;
    openedModel = nullptr;
    emit OnClose(pluginInfo);
    emit OnClose();
}


void HeartRateDeviceModel::SetHbO2Data(float value)
{
    fuzzyCO2->SetValue(value);
}
