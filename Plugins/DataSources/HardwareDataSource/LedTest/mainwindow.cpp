#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ArduinoUno = {
        "Arduino Uno",
        9025,
        67,
        13,
        6
    };

    inputParser = QRegExp("\\{([\\w\\d,]+)\\}");

    isPortSet = false;
    portsData = new QStandardItemModel();
    portsData->setColumnCount(4);
    portsData->setHeaderData(0, Qt::Horizontal, "Name");
    portsData->setHeaderData(1, Qt::Horizontal, "Vendor ID");
    portsData->setHeaderData(2, Qt::Horizontal, "Product ID");
    portsData->setHeaderData(3, Qt::Horizontal, "Device");
    ui->tableView->setModel(portsData);
    startTime = 0;

    auto ports = QSerialPortInfo::availablePorts();
    portsData->setRowCount(ports.length());
    qDebug() << "Available ports:" << ports.length();
    for(int i = 0; i < ports.length(); ++i) {
        auto port = ports[i];
        portsData->setData(portsData->index(i, 0), port.portName());
        portsData->setData(portsData->index(i, 1), port.hasVendorIdentifier() ? port.vendorIdentifier() : -1);
        portsData->setData(portsData->index(i, 2), port.hasProductIdentifier() ? port.productIdentifier() : -1);
        if(ArduinoUno.Compare(port.vendorIdentifier(), port.productIdentifier()))
        {
            portsData->setData(portsData->index(i, 3), ArduinoUno.name);
        }
    }

//    connect(ui->horizontalPlotScroll, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBarChanged(int)));
////    connect(ui->verticalPlotScroll, SIGNAL(valueChanged(int)), this, SLOT(vertScrollBarChanged(int)));
//    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisChanged(QCPRange)));
//    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(yAxisChanged(QCPRange)));
    ui->horizontalPlotScroll->setRange(0, 99);
    ui->customPlot->yAxis->setRange(0, 1024);
}

MainWindow::~MainWindow()
{
    if(isPortSet && arduinoPort->isOpen())
    {
        arduinoPort->close();
    }
    delete ui;
}

void MainWindow::SetPinOutput(int value)
{
    value = 2.55 * value;
    QString message = QString("w%1").arg(value);
    SendMessage(message);
}

void MainWindow::SendMessage(QString message)
{
    if(isPortSet && arduinoPort->isWritable())
    {
        auto str = message.toLocal8Bit().toStdString().c_str();
        arduinoPort->write(str);
        qDebug() << "Sent:" << str;
    }
    else
    {
        qDebug() << "Can't write:" << arduinoPort->isWritable() << arduinoPort->errorString();
    }
}

void MainWindow::ProcessPortInput()
{
    auto byteArray = arduinoPort->readAll();
    auto message = QString::fromStdString(byteArray.toStdString());
    serialBuffer.append(message);
    if(inputParser.indexIn(serialBuffer) != -1)
    {
        QString res = inputParser.capturedTexts().at(1);
        QStringList stringList = res.split(',');
        ui->textPortLog->append(res);
        serialBuffer = "";

        if(startTime == 0) startTime = QDateTime::currentMSecsSinceEpoch();
        double time = (QDateTime::currentMSecsSinceEpoch() - startTime) / 1000.0;
        timeScale.append(time);
        inputData.append((stringList[1]).toDouble());
        ReplotPlot();
    }
}

bool MainWindow::Setup()
{
    auto ports = QSerialPortInfo::availablePorts();
    for(int i = 0; i < ports.length(); ++i) {
        auto port = ports[i];
        if(ArduinoUno.Compare(port.vendorIdentifier(), port.productIdentifier()))
        {
            activePortName = port.portName();
            isPortSet = true;
            SetupPins();
        }
    }

    if(!isPortSet)
    {
        qDebug() << "Arduino isn't set!";
        return false;
    }

    openModeFlag = QSerialPort::ReadWrite;

    arduinoPort = new QSerialPort();
    arduinoPort->setPortName(activePortName);
    arduinoPort->open(openModeFlag);
    arduinoPort->setBaudRate(QSerialPort::Baud9600);
    arduinoPort->setDataBits(QSerialPort::Data8);
    arduinoPort->setParity(QSerialPort::NoParity);
    arduinoPort->setStopBits(QSerialPort::OneStop);
    arduinoPort->setFlowControl(QSerialPort::NoFlowControl);
    connect(arduinoPort, SIGNAL(readyRead()), SLOT(ProcessPortInput()));

    ui->customPlot->clearGraphs();
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    ui->customPlot->yAxis->setRange(0, 1000);
    ui->customPlot->addGraph();
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(QColor(28, 156, 255)));
    ui->customPlot->graph(1)->setPen(QPen(QColor(226, 6, 25)));

    return true;
}

void MainWindow::on_buttonSetup_clicked()
{
    if(!isPortSet)
    {
        isPortSet = Setup();
        if(!isPortSet) return;
        ui->buttonSetup->setText("Disconnect");
    }
    else
    {
        arduinoPort->close();
        disconnect(arduinoPort, SIGNAL(readyRead()), this, SLOT(ProcessPortInput()));
        ui->buttonSetup->setText("Connect");
        isPortSet = false;
        startTime = 0;
    }
}

void MainWindow::ReplotPlot()
{
    MakePlot(0, timeScale, inputData);
    ui->customPlot->xAxis->setRange(timeScale.last()*(windowXScale), timeScale.last());
    ui->customPlot->replot();
}

void MainWindow::SetupPins()
{
    if(inputPins.count() != 0)
        return;

    auto device = ArduinoUno;

    QRadioButton *radioBtn;

    for(int i = 0; i < device.inputPins; ++i)
    {
        radioBtn = new QRadioButton(QString("%1").arg(i+1));
        QGridLayout *layout = (QGridLayout*)ui->groupBoxInputs->layout();
        layout->addWidget(radioBtn, i%pinRowsCount, i/pinRowsCount);
        inputPins.append(radioBtn);
        connect(radioBtn, SIGNAL(clicked(bool)), SLOT(InputPinChanged()));
    }

    for(int i = 0; i < device.outputPins; ++i)
    {
        radioBtn = new QRadioButton(QString("%1").arg(i));
        QGridLayout *layout = (QGridLayout*)ui->groupBoxOutputs->layout();
        layout->addWidget(radioBtn, i%pinRowsCount, i/pinRowsCount);
        outputPins.append(radioBtn);
        connect(radioBtn, SIGNAL(clicked(bool)), SLOT(OutputPinChanged()));
    }

    radioBtn = new QRadioButton("None");
    ui->groupBoxOutputs->layout()->addWidget(radioBtn);
    outputPins.append(radioBtn);
    connect(radioBtn, SIGNAL(clicked(bool)), SLOT(OutputPinChanged()));
}

void MainWindow::InputPinChanged()
{
    for(int i = 0; i < inputPins.length(); ++i)
    {
        auto pin = inputPins[i];
        if(pin->isChecked())
        {
            SendMessage(QString("i").append(pin->text()));
            return;
        }
    }
}

void MainWindow::OutputPinChanged()
{
    for(int i = 0; i < outputPins.length(); ++i)
    {
        auto pin = outputPins[i];
        if(pin->isChecked())
        {
            if(pin->text() == "None")
            {
                if(activeOutPin != "")
                    SendMessage(QString("o%1").arg(activeOutPin));
            }
            else
            {
                activeOutPin = pin->text();
                SendMessage(QString("o").append(pin->text()));
            }
            return;
        }
    }
}

void MainWindow::MakePlot(int graph, QVector<double> &x, QVector<double> &y)
{
    ui->customPlot->graph(graph)->setData(x, y);
}

void MainWindow::on_buttonSend_clicked()
{
    SendMessage(ui->lineMessage->text());
    ui->lineMessage->clear();
}

void MainWindow::on_horizontalSliderHorizontal_sliderMoved(int position)
{
    SetPinOutput(position);
}

void MainWindow::on_horizontalSlider_sliderReleased()
{
    SendMessage(QString("d%1").arg(ui->horizontalSlider->value()));
}

//void MainWindow::horzScrollBarChanged(int value)
//{
//  if (qAbs(ui->customPlot->xAxis->range().center()-value/100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
//  {
//    ui->customPlot->xAxis->setRange(value/100.0, ui->customPlot->xAxis->range().size(), Qt::AlignCenter);
//    ui->customPlot->replot();
//  }
//}

//void MainWindow::vertScrollBarChanged(int value)
//{
//  if (qAbs(ui->customPlot->yAxis->range().center()+value/100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
//  {
//    ui->customPlot->yAxis->setRange(-value/100.0, ui->customPlot->yAxis->range().size(), Qt::AlignCenter);
//    ui->customPlot->replot();
//  }
//}

//void MainWindow::xAxisChanged(QCPRange range)
//{
//  ui->horizontalPlotScroll->setValue(qRound(range.center()*100.0)); // adjust position of scroll bar slider
//  ui->horizontalPlotScroll->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
//  ui->verticalPlotScroll->setRange(0, range.upper);
//}

//void MainWindow::yAxisChanged(QCPRange range)
//{
//  ui->verticalPlotScroll->setValue(qRound(-range.center()*100.0)); // adjust position of scroll bar slider
//  ui->verticalPlotScroll->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
//}

void MainWindow::on_horizontalPlotScroll_sliderMoved(int position)
{
    windowXScale = position / 100.;
}
