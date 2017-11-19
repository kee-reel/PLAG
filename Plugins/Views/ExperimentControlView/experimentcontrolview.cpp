#include "experimentcontrolview.h"
#include "ui_form.h"

ExperimentControlView::ExperimentControlView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    myReferencedPlugin = NULL;
    ui->setupUi(this);
    connect(ui->buttonExit, SIGNAL(clicked(bool)), this, SLOT(Close()));
    dataChart.legend()->hide();
    dataChart.setTitle("Simple line dataChart example");
    ui->dataChartView->setChart(&dataChart);
    ui->dataChartView->setRenderHint(QPainter::Antialiasing);

    //    connect(ui->buttonStart, &QPushButton::clicked, this, [=]()
    //    {
    //        myReferencedPlugin->StartExperiment();
    //    });
    //    connect(ui->buttonStop, &QPushButton::clicked, this, [=]()
    //    {
    //        myReferencedPlugin->StopExperiment();
    //    });
}

ExperimentControlView::~ExperimentControlView()
{
}

void ExperimentControlView::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void ExperimentControlView::OnAllSetup()
{
    SetupData();
}

QString ExperimentControlView::GetLastError()
{
}

void ExperimentControlView::SetupData()
{
    auto ports = myReferencedPlugin->GetAvailablePorts();
    ui->availablePortsView->setModel(ports);

    auto devices = myReferencedPlugin->GetAvailableModbusDeviceHandlers();
    ui->devicesView->setModel(devices);

    auto deviceNames = myReferencedPlugin->GetAvailableModbusDeviceNames();
    ui->deviceNamesCombo->setModel(deviceNames);

    auto registers = myReferencedPlugin->GetRegisterPacks();
    ui->registersView->setModel(registers);

    auto values = myReferencedPlugin->GetValues();
    ui->valuesView->setModel(values);
}

void ExperimentControlView::AddReferencePlugin(PluginInfo *pluginInfo)
{
    switch(pluginInfo->Meta->Type)
    {
        case PLUGINVIEW:
        {
        } break;

        case PLUGINMODEL:
        {
            myReferencedPlugin = qobject_cast<IExperimentControlModel*>(pluginInfo->Instance);

            if(!myReferencedPlugin)
            {
                qDebug() << pluginInfo->Meta->Name << "is not ISomePlugin.";
                return;
            }

            qDebug() << "ISomePlugin succesfully set.";
            myReferencedPlugin->AddReferencePlugin(this->pluginInfo);
            connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));

            //            auto lineSeries = myReferencedPlugin->GetLineSeries();
            //            dataChart.addSeries(lineSeries);
            //            dataChart.createDefaultAxes();
            //            dataChart.axisY()->setRange(0, 1024);
            //            connect(lineSeries, &QLineSeries::pointAdded, this, [=](int index)
            //            {
            //                dataChart.axisX()->setRange(0, lineSeries->at(index).x());
            //            });
        } break;

        case ROOTMODEL:
        {
        } break;

        case DATAMANAGER:
        {
        } break;
    }
}

void ExperimentControlView::ReferencePluginClosed(PluginInfo *pluginInfo)
{
}

bool ExperimentControlView::Open(IModelPlugin *model)
{
    qDebug() << "ExperimentControlView open.";

    // If something not set.
    if(false)
    {
        qDebug() << "!ExperimentControlView not fully initialized!";
        return false;
    }

    emit OnOpen(this);
    return true;
}

bool ExperimentControlView::Close()
{
    qDebug() << "ExperimentControlView close.";

    // If view cannot close.
    if(false)
    {
        qDebug() << "!ExperimentControlView cannot close right now!";
        return false;
    }

    emit OnClose(pluginInfo);
    emit OnClose();
    return true;
}

void ExperimentControlView::on_connectButton_clicked()
{
    IModbusDeviceDataManager::ConnectionSettings settings;

    settings.parity = (QSerialPort::Parity)ui->parityCombo->currentIndex();
    if (settings.parity > 0)
        settings.parity = (QSerialPort::Parity)(settings.parity + 1);
    settings.baud = (QSerialPort::BaudRate)ui->baudCombo->currentText().toInt();
    settings.dataBits = (QSerialPort::DataBits)ui->dataBitsCombo->currentText().toInt();
    settings.stopBits = (QSerialPort::StopBits)ui->stopBitsCombo->currentText().toInt();
    settings.responseTimeout = ui->timeoutSpinner->value();
    settings.numberOfRetries = ui->retriesSpinner->value();

    auto selection = ui->availablePortsView->selectionModel()->selectedRows();
    if(selection.length() != 0)
    {
        int row = selection.first().row();
        myReferencedPlugin->OpenPort(row, settings);
    }
}

void ExperimentControlView::on_scanButton_clicked()
{
    myReferencedPlugin->ScanForDevice(ui->deviceIdSpin->value());
}

void ExperimentControlView::on_refreshButton_clicked()
{
    myReferencedPlugin->UpdateAvailablePorts();
}

void ExperimentControlView::on_addRegisterPackButton_clicked()
{
    IExperimentControlModel::RegstersPack pack;
    pack.type = (QModbusDataUnit::RegisterType)(ui->registersCombo->currentIndex() + 1);
    pack.start = ui->startRegisterSpin->value();
    pack.count = ui->registersCountSpin->value();
    pack.updateInterval = ui->updateIntervalSpin->value();
    myReferencedPlugin->AddRegisterPack(pack);
}

void ExperimentControlView::on_removeRegistersButton_clicked()
{
    auto view = ui->registersView;
    RemoveModelItem(view);
}

void ExperimentControlView::RemoveModelItem(QAbstractItemView *view)
{
    auto selection = view->selectionModel()->selectedRows();
    if(selection.length() != 0)
    {
        int row = selection.first().row();
        view->model()->removeRow(row);
    }
}

void ExperimentControlView::on_deviceNamesCombo_currentIndexChanged(int index)
{
    myReferencedPlugin->SetDeviceIdForPacks(index);
}

void ExperimentControlView::on_tabWidget_tabBarClicked(int index)
{
    if(index == 2)
    {
        emit myReferencedPlugin->SetDeviceIdForPacks(ui->deviceNamesCombo->currentIndex());
    }
}
