#include "experimentcontrolview.h"
#include "ui_form.h"

ModbusDataReaderView::ModbusDataReaderView(QWidget *parent) :
    PluginBase(parent)
{
    myReferencedPlugin = nullptr;
    connect(ui->buttonExit, SIGNAL(clicked()), this, SLOT(on_closeButton_clicked()));
    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(on_connectButton_clicked()));
    connect(ui->scanButton, SIGNAL(clicked()), this, SLOT(on_scanButton_clicked()));
    connect(ui->refreshButton, SIGNAL(clicked()), this, SLOT(on_refreshButton_clicked()));
    connect(ui->addRegisterPackButton, SIGNAL(clicked()), this, SLOT(on_addRegisterPackButton_clicked()));
    connect(ui->removeRegistersButton, SIGNAL(clicked()), this, SLOT(on_removeRegistersButton_clicked()));
    connect(ui->deviceNamesCombo, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_deviceNamesCombo_currentIndexChanged(const QString &)));
    connect(ui->chartScroll, SIGNAL(sliderMoved(int)), this, SLOT(on_chartScroll_sliderMoved(int)));
    connect(ui->buttonRunExperiment, SIGNAL(clicked()), this, SLOT(on_buttonRunExperiment_clicked()));
    connect(ui->buttonSaveResults, SIGNAL(clicked()), this, SLOT(on_buttonSaveResults_clicked()));
    connect(ui->buttonFilenameDialog, SIGNAL(clicked()), this, SLOT(on_buttonFilenameDialog_clicked()));

    dataChart.legend()->hide();
    dataChart.setTitle("Simple line dataChart example");
    ui->dataChartView->setChart(&dataChart);
    ui->dataChartView->setRenderHint(QPainter::Antialiasing);
    ui->dataChartView->installEventFilter(this);
    previousSliderValue = 0;
    currentChartXScale = 100;
//    connect(&clockUpdateTimer, &QTimer::timeout, this, [=]()
//    {
//        QTime time;
//        time.setHMS(0, 0, 0);
//        time.addMSecs(timeSinceStartPassed.elapsed());
//        qDebug() << time << timeSinceStartPassed.elapsed();
//        ui->lcdHours->display(time.toString("hh:mm:ss"));
//    });
    minYValue = 0;
    maxYValue = 0;
    ui->dataChartView->setChart(&dataChart);
}

ModbusDataReaderView::~ModbusDataReaderView()
{
}

void ModbusDataReaderView::onAllReferencesSet()
{
    for(auto iter = m_referencesMap.begin(); iter != m_referencesMap.end(); ++iter)
    {
        auto&& interfaceName = iter.key();
        auto&& plugin = iter.value();
        if(!QString::compare(interfaceName, "IModbusDataReader", Qt::CaseInsensitive))
        {
            auto instance = plugin->getObject();
            myReferencedPlugin = qobject_cast<IModbusDataReader*>(instance);
            connect(instance, SIGNAL(ExperimentStateChanged(bool)), this, SLOT(onExperimentStateChanged(bool)));
        }
    }
    PluginBase::onAllReferencesSet();
}

void ModbusDataReaderView::onAllReferencesReady()
{
    auto ports = myReferencedPlugin->GetAvailablePorts();
    ui->availablePortsView->setModel(ports);
    auto devices = myReferencedPlugin->GetAvailableModbusDeviceHandlers();
    ui->devicesView->setModel(devices);
    auto deviceNames = myReferencedPlugin->GetAvailableModbusDeviceNames();
    ui->deviceNamesCombo->setModel(deviceNames);
    auto registers = myReferencedPlugin->GetRegisterPacks();
    ui->registersView->setModel(registers);

    PluginBase::onAllReferencesReady();
}

void ModbusDataReaderView::on_closeButton_clicked()
{
    emit onClose(this);
}

void ModbusDataReaderView::on_connectButton_clicked()
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

void ModbusDataReaderView::on_scanButton_clicked()
{
    myReferencedPlugin->ScanForDevice(ui->deviceIdSpin->value());
}

void ModbusDataReaderView::on_refreshButton_clicked()
{
    myReferencedPlugin->UpdateAvailablePorts();
}

void ModbusDataReaderView::on_addRegisterPackButton_clicked()
{
    IModbusDataReader::RegstersPack pack;
    pack.type = (QModbusDataUnit::RegisterType)(ui->registersCombo->currentIndex() + 1);
    pack.start = ui->startRegisterSpin->value();
    pack.count = ui->registersCountSpin->value();
    pack.updateInterval = ui->updateIntervalSpin->value();
    myReferencedPlugin->AddRegisterPack(pack);
    QList<QLineSeries*> registerLineSeries = myReferencedPlugin->GetRegistersLineSeries();
    dataChart.removeAllSeries();

    foreach (QLineSeries* line, registerLineSeries)
    {
        dataChart.addSeries(line);
        connect(line, &QLineSeries::pointAdded, this, [=](int index)
        {
            SeriesPointAdded(line, index);
        });
    }

    dataChart.createDefaultAxes();
    dataChart.axisX()->setRange(0, currentChartXScale);
    dataChart.axisY()->setRange(minYValue, maxYValue);
}

void ModbusDataReaderView::on_removeRegistersButton_clicked()
{
    auto view = ui->registersView;
    RemoveModelItem(view);
}

void ModbusDataReaderView::RemoveModelItem(QAbstractItemView *view)
{
    auto selection = view->selectionModel()->selectedRows();

    if(selection.length() != 0)
    {
        int row = selection.first().row();
        view->model()->removeRow(row);
    }
}

bool ModbusDataReaderView::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->dataChartView)
    {
        if (event->type() == QEvent::Wheel)
        {
            QWheelEvent *mouseEvent = static_cast<QWheelEvent*>(event);
            bool isZoomIn = mouseEvent->angleDelta().y() > 0;
            currentChartXScale += (currentChartXScale / 10) * (isZoomIn ? -1 : 1);
            dataChart.axisX()->setRange(0, currentChartXScale);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        // pass the event on to the parent class
        return QWidget::eventFilter(watched, event);
    }
}

void ModbusDataReaderView::on_deviceNamesCombo_currentIndexChanged(const QString &arg1)
{
    if(arg1 != "")
        myReferencedPlugin->SetDeviceForSetup(arg1);
}

void ModbusDataReaderView::on_buttonStart_clicked()
{
    myReferencedPlugin->StartReading();
}

void ModbusDataReaderView::on_chartScroll_sliderMoved(int position)
{
    qreal xScroll = (currentChartXScale / 100.) * (position - previousSliderValue);
    dataChart.scroll(xScroll, 0);
    previousSliderValue = position;
}

void ModbusDataReaderView::SeriesPointAdded(QLineSeries *line, int index)
{
    if (!line)
        return;

    float lastXPoint = line->at(index).x();
    float lastYPoint = line->at(index).y();
    int chartScrollValue = ui->chartScroll->value();

    if(minYValue > lastYPoint)
    {
        minYValue = lastYPoint;
        dataChart.axisY()->setRange(minYValue, maxYValue);
    }

    if(maxYValue < lastYPoint)
    {
        maxYValue = lastYPoint;
        dataChart.axisY()->setRange(minYValue, maxYValue);
    }

    if(chartScrollValue >= ui->chartScroll->maximum()*0.9)
    {
        ui->chartScroll->setMaximum(lastXPoint);
        ui->chartScroll->setValue(chartScrollValue);
        ui->chartScroll->sliderMoved(chartScrollValue);
        ++chartScrollValue;
    }
}

void ModbusDataReaderView::on_buttonRunExperiment_clicked()
{
    if(myReferencedPlugin->GetReadingState())
    {
        myReferencedPlugin->StopReading();
    }
    else
    {
        myReferencedPlugin->StartReading();
    }
}

void ModbusDataReaderView::onExperimentStateChanged(bool state)
{
    SetDataFilename();
    ui->buttonSaveResults->setEnabled(!state);
    ui->buttonRunExperiment->setText(state ? "Stop" : "Start");

    if(state)
    {
        timeSinceStartPassed = QTime::currentTime();
        timeSinceStartPassed.start();
//        clockUpdateTimer.start(1000);
    }
}

void ModbusDataReaderView::on_buttonSaveResults_clicked()
{
    auto filename = ui->lineFilename->text();

    if(filename != "")
        myReferencedPlugin->SaveReadingData(filename);
}

void ModbusDataReaderView::on_buttonFilenameDialog_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,
                       tr("Experiment data file name"), QDir::currentPath());
    SetDataFilename(filename);
}

void ModbusDataReaderView::SetDataFilename(QString filename)
{
    QString extentionName = ui->comboSaveFormat->currentText().toLower();

    if(filename == "")
    {
        QString templateName = "ex";
        filename = QString("%1_%2.%3")
                   .arg(templateName)
                   .arg(myReferencedPlugin->GetReadingStartTime().toString("ddMM_hhmmss"))
                   .arg(extentionName);
    }

    if(!filename.contains(extentionName, Qt::CaseInsensitive))
    {
        filename.append(".").append(extentionName);
    }

    ui->lineFilename->setText(filename);
}
