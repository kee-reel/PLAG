#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ArduinoUno = {
        9025,
        67
    };

    inputParser = QRegExp("{(\\D+),(\\d+)}");

    isPortSet = false;
    portsData = new QStandardItemModel();
    portsData->setColumnCount(3);
    portsData->setHeaderData(0, Qt::Horizontal, "Name");
    portsData->setHeaderData(1, Qt::Horizontal, "Vendor identifier");
    portsData->setHeaderData(2, Qt::Horizontal, "Product identifier");
    ui->tableView->setModel(portsData);

    auto ports = QSerialPortInfo::availablePorts();
    qDebug() << "Available ports:" << ports.length();
    for(int i = 0; i < ports.length(); ++i) {
        auto port = ports[i];
//        portsData->setData(portsData->index(i, 0), port.portName());
//        portsData->setData(portsData->index(i, 1), port.hasVendorIdentifier() ? port.vendorIdentifier() : -1);
//        portsData->setData(portsData->index(i, 2), port.hasProductIdentifier() ? port.productIdentifier() : -1);

        if(ArduinoUno.Compare(port.vendorIdentifier(), port.productIdentifier()))
        {
            activePortName = port.portName();
            isPortSet = true;
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
    connect(ui->buttonSetup, SIGNAL(clicked(bool)), SLOT(Setup()));

}

MainWindow::~MainWindow()
{
    if(isPortSet && arduinoPort->isOpen())
        arduinoPort->close();
    delete ui;
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    ui->label_3->setText(QString("%1%").arg(position));
    SendMessage("s9");
    UpdateLED('w', position);
}

void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{
    ui->label_4->setText(QString("%1%").arg(position));
    SendMessage("s10");
    UpdateLED('w', position);
}

void MainWindow::UpdateLED(char pinId, int value)
{
    value = 2.55 * value;
    QString message = QString("%1%2").arg(pinId).arg(value);
    SendMessage(message);
}

void MainWindow::SendMessage(QString message)
{
    if(isPortSet && arduinoPort->isWritable())
    {
        arduinoPort->write(message.toStdString().c_str());
        qDebug() << "Sent:" << message;
    }
    else
    {
        qDebug() << "Can't write:" << arduinoPort->isWritable() << arduinoPort->errorString();
    }
}

void MainWindow::ProcessPortInput()
{
    auto inputData = arduinoPort->readAll();
    auto message = QString::fromStdString(inputData.toStdString());
    //qDebug() << "Read:" << message;
    serialBuffer.append(message);
    if(serialBuffer.contains('}'))
    {
        serialBuffer = serialBuffer.remove('{').remove('}');
        qDebug() << "Buffer:" << serialBuffer.split(',');
        serialBuffer = "";

    }
}

void MainWindow::Setup()
{
    SendMessage("i");
    SendMessage("r");
    SendMessage("d5");
}
