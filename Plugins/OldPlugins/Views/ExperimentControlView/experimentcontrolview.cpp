#include "experimentcontrolview.h"
#include "ui_form.h"

ExperimentControlView::ExperimentControlView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    myReferencedPlugin = nullptr;
    ui->setupUi(this);
    connect(ui->buttonExit, SIGNAL(clicked(bool)), this, SLOT(Close()));
    dataChart.legend()->hide();
    dataChart.setTitle("Simple line dataChart example");
    ui->dataChartView->setChart(&dataChart);
    ui->dataChartView->setRenderHint(QPainter::Antialiasing);
    ui->dataChartView->installEventFilter(this);
    previousSliderValue = 0;
    currentChartXScale = 100;
    connect(&clockUpdateTimer, &QTimer::timeout, this, [=]()
    {
        QTime time;
        time.setHMS(0, 0, 0);
        time.addMSecs(timeSinceStartPassed.elapsed());
        qDebug() << time << timeSinceStartPassed.elapsed();
        ui->lcdHours->display(time.toString("hh:mm:ss"));
    });
    minYValue = 0;
    maxYValue = 0;
    ui->dataChartView->setChart(&dataChart);
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
    if(!myReferencedPlugin)
        return;

    auto ports = myReferencedPlugin->GetAvailablePorts();
    ui->availablePortsView->setModel(ports);
    auto devices = myReferencedPlugin->GetAvailableModbusDeviceHandlers();
    ui->devicesView->setModel(devices);
    auto deviceNames = myReferencedPlugin->GetAvailableModbusDeviceNames();
    ui->deviceNamesCombo->setModel(deviceNames);
    auto registers = myReferencedPlugin->GetRegisterPacks();
    ui->registersView->setModel(registers);
}

void ExperimentControlView::AddReferencePlugin(PluginInfo *pluginInfo)
{
    switch(pluginInfo->Meta->Type)
    {
        case VIEWPLUGIN:
        {
        } break;

        case MODELPLUGIN:
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
            connect(pluginInfo->Instance, SIGNAL(ExperimentStateChanged(bool)), this, SLOT(onExperimentStateChanged(bool)));
        } break;

        case COREPLUGIN:
        {
        } break;

        case DATAMANAGERPLUGIN:
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

bool ExperimentControlView::eventFilter(QObject *watched, QEvent *event)
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

void ExperimentControlView::on_deviceNamesCombo_currentIndexChanged(const QString &arg1)
{
    if(arg1 != "")
        myReferencedPlugin->SetDeviceForSetup(arg1);
}

void ExperimentControlView::on_buttonStart_clicked()
{
    myReferencedPlugin->StartExperiment();
}

void ExperimentControlView::on_chartScroll_sliderMoved(int position)
{
    qreal xScroll = (currentChartXScale / 100.) * (position - previousSliderValue);
    dataChart.scroll(xScroll, 0);
    previousSliderValue = position;
}

void ExperimentControlView::SeriesPointAdded(QLineSeries *line, int index)
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

void ExperimentControlView::on_buttonRunExperiment_clicked()
{
    if(myReferencedPlugin->GetExperimentState())
    {
        myReferencedPlugin->StopExperiment();
    }
    else
    {
        myReferencedPlugin->StartExperiment();
    }
}

void ExperimentControlView::onExperimentStateChanged(bool state)
{
    SetDataFilename();
    ui->buttonSaveResults->setEnabled(!state);
    ui->buttonRunExperiment->setText(state ? "Stop" : "Start");

    if(state)
    {
        timeSinceStartPassed = QTime::currentTime();
        timeSinceStartPassed.start();
        clockUpdateTimer.start(1000);
    }
}

void ExperimentControlView::on_buttonSaveResults_clicked()
{
    auto filename = ui->lineFilename->text();

    if(filename != "")
        myReferencedPlugin->SaveExperimentData(filename);
}

void ExperimentControlView::on_buttonFilenameDialog_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,
                       tr("Experiment data file name"), QDir::currentPath());
    SetDataFilename(filename);
}

void ExperimentControlView::SetDataFilename(QString filename)
{
    QString extentionName = ui->comboSaveFormat->currentText().toLower();

    if(filename == "")
    {
        QString templateName = "ex";
        filename = QString("%1_%2.%3")
                   .arg(templateName)
                   .arg(myReferencedPlugin->GetExperimentStartTime().toString("ddMM_hhmmss"))
                   .arg(extentionName);
    }

    if(!filename.contains(extentionName, Qt::CaseInsensitive))
    {
        filename.append(".").append(extentionName);
    }

    ui->lineFilename->setText(filename);
}
