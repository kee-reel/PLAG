#include "comportdatasource.h"

COMPortDataSource::COMPortDataSource()
{
//    ArduinoUno = {
//        "Arduino Uno",
//        9025,
//        67,
//        13,
//        6
//    };

//    inputParser = QRegExp("\\{([\\w\\d,]+)\\}");

//    isPortSet = false;
//    portsData = new QStandardItemModel();
//    portsData->setColumnCount(4);
//    portsData->setHeaderData(0, Qt::Horizontal, "Name");
//    portsData->setHeaderData(1, Qt::Horizontal, "Vendor ID");
//    portsData->setHeaderData(2, Qt::Horizontal, "Product ID");
//    portsData->setHeaderData(3, Qt::Horizontal, "Device");
//    ui->tableView->setModel(portsData);
//    startTime = 0;

//    auto ports = QSerialPortInfo::availablePorts();
//    portsData->setRowCount(ports.length());
//    qDebug() << "Available ports:" << ports.length();
//    for(int i = 0; i < ports.length(); ++i) {
//        auto port = ports[i];
//        portsData->setData(portsData->index(i, 0), port.portName());
//        portsData->setData(portsData->index(i, 1), port.hasVendorIdentifier() ? port.vendorIdentifier() : -1);
//        portsData->setData(portsData->index(i, 2), port.hasProductIdentifier() ? port.productIdentifier() : -1);
//        if(ArduinoUno.Compare(port.vendorIdentifier(), port.productIdentifier()))
//        {
//            portsData->setData(portsData->index(i, 3), ArduinoUno.name);
//        }
//    }
}

COMPortDataSource::~COMPortDataSource()
{
}

void COMPortDataSource::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void COMPortDataSource::OnAllSetup()
{

}

QString COMPortDataSource::GetLastError()
{

}

void COMPortDataSource::AddReferencePlugin(PluginInfo *pluginInfo)
{
    switch(pluginInfo->Meta->Type){
    case PLUGINVIEW:{
    } break;

    case PLUGINMODEL:{
    } break;

    case ROOTMODEL:{
    } break;

    case DATAMANAGER:{
    }break;
    }
}

void COMPortDataSource::ReferencePluginClosed(PluginInfo *pluginInfo)
{

}

void COMPortDataSource::Setup()
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
        return;
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
}

void COMPortDataSource::SetPinOutput(int value)
{
    value = 2.55 * value;
    QString message = QString("w%1").arg(value);
    SendMessage(message);
}

void COMPortDataSource::SendMessage(QString message)
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

void COMPortDataSource::ProcessPortInput()
{
    auto byteArray = arduinoPort->readAll();
    auto message = QString::fromStdString(byteArray.toStdString());
    serialBuffer.append(message);
    if(inputParser.indexIn(serialBuffer) != -1)
    {
        QString res = inputParser.capturedTexts().at(1);
        QStringList stringList = res.split(',');
        serialBuffer = "";

        if(startTime == 0) startTime = QDateTime::currentMSecsSinceEpoch();
        double time = (QDateTime::currentMSecsSinceEpoch() - startTime) / 1000.0;
        timeScale.append(time);
        inputData.append((stringList[1]).toDouble());
    }
}

void COMPortDataSource::SetupPins()
{
//    if(inputPins.count() != 0)
//        return;

//    auto device = ArduinoUno;

//    QRadioButton *radioBtn;

//    for(int i = 0; i < device.inputPins; ++i)
//    {
//        radioBtn = new QRadioButton(QString("%1").arg(i+1));
//        QGridLayout *layout = (QGridLayout*)ui->groupBoxInputs->layout();
//        layout->addWidget(radioBtn, i%pinRowsCount, i/pinRowsCount);
//        inputPins.append(radioBtn);
//        connect(radioBtn, SIGNAL(clicked(bool)), SLOT(InputPinChanged()));
//    }

//    for(int i = 0; i < device.outputPins; ++i)
//    {
//        radioBtn = new QRadioButton(QString("%1").arg(i));
//        QGridLayout *layout = (QGridLayout*)ui->groupBoxOutputs->layout();
//        layout->addWidget(radioBtn, i%pinRowsCount, i/pinRowsCount);
//        outputPins.append(radioBtn);
//        connect(radioBtn, SIGNAL(clicked(bool)), SLOT(OutputPinChanged()));
//    }

//    radioBtn = new QRadioButton("None");
//    ui->groupBoxOutputs->layout()->addWidget(radioBtn);
//    outputPins.append(radioBtn);
//    connect(radioBtn, SIGNAL(clicked(bool)), SLOT(OutputPinChanged()));
}
