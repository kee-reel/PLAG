#include "experimentcontrolmodel.h"


ExperimentControlModel::ExperimentControlModel()
{
    // myReferencedPlugin = NULL;
    openedView = NULL;
    openedModel = NULL;
}

ExperimentControlModel::~ExperimentControlModel()
{
}

void ExperimentControlModel::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void ExperimentControlModel::OnAllSetup()
{
    auto ports = myReferencedPlugin->GetAvailablePorts();

    if(ports.length() == 0)
        return;

    IModbusDeviceDataManager::ConnectionSettings settings;
    settings.baud = QSerialPort::Baud19200;
    settings.dataBits = QSerialPort::Data8;
    settings.numberOfRetries = 3;
    settings.parity = QSerialPort::NoParity;
    settings.responseTimeout = 1000;
    settings.stopBits = QSerialPort::OneStop;
    myReferencedPlugin->OpenPort(ports.first().portName, settings);
    QTimer::singleShot(5000, [=]()
    {
        auto list = myReferencedPlugin->GetAvailableModbusDevices();

        foreach (auto device, list)
        {
            auto deviceInstance = device->GetInstance();
            //            public slots:
            //                virtual bool ReadRequest(DataTypes dataType) = 0;
            //                virtual bool WriteRequest(DataTypes dataType, const QVector<quint16> &data) = 0;
            //            signals:
            //                void OnReadRequestArrived(DataTypes dataType, const QVector<quint16> &data);
            connect(deviceInstance, SIGNAL(OnReadRequestArrived(QModbusDataUnit::RegisterType, const QVector<quint16> &)),
                    this, SLOT(ProcessDataInput(QModbusDataUnit::RegisterType,QVector<quint16>)));
            device->ReadRequest(QModbusDataUnit::InputRegisters);
            deviceHandlers.append(device);
        }
    });
}

QString ExperimentControlModel::GetLastError()
{
}

void ExperimentControlModel::AddReferencePlugin(PluginInfo *pluginInfo)
{
    switch(pluginInfo->Meta->Type)
    {
        case PLUGINVIEW:
        {
            relatedViewPlugins.append(pluginInfo);
            qDebug() << "New IViewPlugin added (" << pluginInfo->Meta->Name << ").";
            connect(pluginInfo->Instance, SIGNAL( OnClose(PluginInfo*) ), SLOT( ReferencePluginClosed(PluginInfo*) ));
        } break;

        case PLUGINMODEL:
        {
            relatedModelPlugins.append(pluginInfo);
            qDebug() << "New IModelPlugin added (" << pluginInfo->Meta->Name << ").";
            connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
        } break;

        case ROOTMODEL:
        {
            if(pluginInfo->Meta->InterfaceName == "IMAINMENUMODEL")
            {
                pluginInfo->Plugin.model->AddReferencePlugin(this->pluginInfo);
            }
        } break;

        case DATAMANAGER:
        {
            myReferencedPlugin = qobject_cast<IModbusDeviceDataManager*>(pluginInfo->Instance);

            if(!myReferencedPlugin)
            {
                qDebug() << pluginInfo->Meta->Name << "is not IModbusDeviceDataManager.";
                return;
            }

            qDebug() << "IModbusDeviceDataManager succesfully set.";
            connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
            connect(pluginInfo->Instance, SIGNAL(ErrorOccurred(QString)), this, SIGNAL(ErrorOccurred(QString)));
        } break;
    }
}

void ExperimentControlModel::ReferencePluginClosed(PluginInfo *pluginInfo)
{
}

bool ExperimentControlModel::Open(IModelPlugin *parent)
{
    qDebug() << "ExperimentControlModel open.";

    if(relatedViewPlugins.count() == 0)
    {
        qDebug() << "!ExperimentControlModel hasn't any views!";
        return false;
    }

    openedView = relatedViewPlugins.first();
    qDebug() << "ExperimentControlModel opens related view " << openedView->Meta->Name;

    if(!openedView->Plugin.view->Open(this))
    {
        qDebug() << "!Can't open first view!";
        openedView = NULL;
        return false;
    }

    return true;
}

void ExperimentControlModel::Close()
{
    qDebug() << "ExperimentControlModel close.";

    if(openedView != NULL && !openedView->Plugin.view->Close())
    {
        qDebug() << "View plugin" << openedView->Meta->Name
                 << "not closed, but model closing anyway.";
    }

    if(openedModel != NULL)
        openedView->Plugin.view->Close();

    openedView = NULL;
    openedModel = NULL;
    emit OnClose(pluginInfo);
    emit OnClose();
}

void ExperimentControlModel::ProcessDataInput(QModbusDataUnit::RegisterType dataType, const QVector<quint16> &data)
{
    qDebug() << "KEKS" << dataType << data;
    //    if(dataRecieveTime.isNull())
    //    {
    //        dataRecieveTime.start();
    //    }
    //    lineSerie.append(dataRecieveTime.elapsed(), dataType);
}

QList<IExperimentControlModel::IExperimentSetup *> ExperimentControlModel::GetAvailableExperimentSetups()
{
}

void ExperimentControlModel::StartExperiment(IExperimentControlModel::IExperimentSetup *setup)
{
    //    myReferencedPlugin->OscilloscopeOn(0,100,0);
    //    myReferencedPlugin->OscilloscopeGo(IArduinoSerialDataManager::OscilloscopeRepeatMode::ON);
}

void ExperimentControlModel::StopExperiment()
{
    //    myReferencedPlugin->OscilloscopeOff();
}
