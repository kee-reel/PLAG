#include "experimentcontrolmodel.h"


ExperimentControlModel::ExperimentControlModel()
{
    myReferencedPlugin = NULL;
    openedView = NULL;
    openedModel = NULL;

    AvailablePortsModel.setColumnCount(3);
    AvailablePortsModel.setHeaderData(0, Qt::Horizontal, "Port");
    AvailablePortsModel.setHeaderData(1, Qt::Horizontal, "Vendor");
    AvailablePortsModel.setHeaderData(2, Qt::Horizontal, "Device");

    ValuesModel.setColumnCount(4);
    ValuesModel.setHeaderData(0, Qt::Horizontal, "Name");
    ValuesModel.setHeaderData(1, Qt::Horizontal, "Type");
    ValuesModel.setHeaderData(2, Qt::Horizontal, "Address");
    ValuesModel.setHeaderData(3, Qt::Horizontal, "Value");
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

}

QString ExperimentControlModel::GetLastError()
{
}

void ExperimentControlModel::UpdateDevicesList()
{
    auto devices = myReferencedPlugin->GetAvailableModbusDeviceHandlers();

    AvailableDevicesModel.UpdateDevicesList(devices);
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
            connect(pluginInfo->Instance, SIGNAL(ModbusListUpdated()), this, SLOT(UpdateDevicesList()));

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
}

QList<IExperimentControlModel::IExperimentSetup *> ExperimentControlModel::GetAvailableExperimentSetups()
{
}

void ExperimentControlModel::StartExperiment(IExperimentControlModel::IExperimentSetup *setup)
{
}

void ExperimentControlModel::StopExperiment()
{

}

QAbstractItemModel *ExperimentControlModel::GetAvailablePorts()
{
    UpdateAvailablePorts();
    return &AvailablePortsModel;
}

void ExperimentControlModel::UpdateAvailablePorts()
{
    auto ports = myReferencedPlugin->GetAvailablePorts();

    AvailablePortsModel.clear();
    foreach (auto port, ports)
    {
        QList<QStandardItem *> itemList = {
            new QStandardItem(port.portName),
            new QStandardItem(QString::number(port.vendorId)),
            new QStandardItem(QString::number(port.productId))
        };
        AvailablePortsModel.appendRow(itemList);
    }
}

bool ExperimentControlModel::OpenPort(int modelIndex, IModbusDeviceDataManager::ConnectionSettings connectionSettings)
{
    myReferencedPlugin->OpenPort(AvailablePortsModel.item(modelIndex, 0)->text(), connectionSettings);
}

void ExperimentControlModel::ScanForDevice(int deviceId)
{
    myReferencedPlugin->ScanForDevice(deviceId);
}

QAbstractItemModel *ExperimentControlModel::GetAvailableModbusDeviceHandlers()
{
    return &AvailableDevicesModel;
}

QAbstractItemModel *ExperimentControlModel::GetAvailableModbusDeviceNames()
{
    return AvailableDevicesModel.GetDeviceNamesModel();
}

void ExperimentControlModel::ClosePort(int modelIndex)
{

}


QAbstractItemModel *ExperimentControlModel::GetRegisterPacks()
{
    return &RegisterPacksModel;
}

void ExperimentControlModel::SetDeviceIdForPacks(int deviceRow)
{
    int deviceId = (AvailableDevicesModel.rowCount() != 0 && AvailableDevicesModel.rowCount() > deviceRow) ?
                AvailableDevicesModel.data(AvailableDevicesModel.index(deviceRow, 0)).toInt() : -1;
    RegisterPacksModel.SetActiveDeviceId(deviceId);
}

void ExperimentControlModel::AddRegisterPack(RegstersPack pack)
{
    RegisterPacksModel.AddRegisterPack(pack);
}

void ExperimentControlModel::AddNewValuesFromPack(RegstersPack pack)
{
//    QString typeStr = GetRegisterString(pack.type);
//    QString shortTypeStr = typeStr;
//    shortTypeStr.truncate(3);
//    for(int i = 0; i < pack.count; ++i)
//    {
//        QList<QStandardItem *> itemList = {
//            new QStandardItem( QString("%1%2").arg(shortTypeStr).arg(pack.start + i)),
//            new QStandardItem(typeStr),
//            new QStandardItem(QString::number(pack.start + i)),
//            new QStandardItem(QString::number(0))
//        };
//        ValuesModel.appendRow(itemList);
//    }
}

QAbstractItemModel *ExperimentControlModel::GetValues()
{
    return &ValuesModel;
}


