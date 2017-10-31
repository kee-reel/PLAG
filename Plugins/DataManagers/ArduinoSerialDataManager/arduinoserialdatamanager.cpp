#include "arduinoserialdatamanager.h"

#include <QTimer>
#include <QDebug>

ArduinoSerialDataManager::ArduinoSerialDataManager()
{
    arduinoPort = NULL;
    inputParser = QRegExp("\\{(.+)\\}");
    inputParser.setMinimal(true);
}

ArduinoSerialDataManager::~ArduinoSerialDataManager()
{
}

void ArduinoSerialDataManager::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void ArduinoSerialDataManager::SetupPort()
{
    ICOMPortDataSource::DeviceInfo ArduinoUnoDevice = {9025, 67};
    myReferencedPlugin->AddSupportedDevice("Arduino Uno", ArduinoUnoDevice);
    auto ports = myReferencedPlugin->GetPortHandlers();

    foreach (auto port, ports)
    {
        if(port->connectedDeviceInfo.productId == ArduinoUnoDevice.productId &&
                port->connectedDeviceInfo.vendorId == ArduinoUnoDevice.vendorId)
        {
            arduinoPort = port;
        }
    }

    if(arduinoPort == NULL)
    {
        qDebug() << "Can't find Arduino Uno port!";
        return;
    }

    if(!arduinoPort->OpenPort(QIODevice::ReadWrite))
    {
        qCritical() << "Can't open port";
        return;
    }

    auto port = arduinoPort->GetSerialPort();
    port->setBaudRate(QSerialPort::Baud115200);
    auto portObject = arduinoPort->GetInstance();
    connect(portObject, SIGNAL(ReadData(QByteArray*)), this, SLOT(ReadPortData(QByteArray*)));
}

void ArduinoSerialDataManager::OnAllSetup()
{
    SetupPort();
}

QString ArduinoSerialDataManager::GetLastError()
{
}

void ArduinoSerialDataManager::AddReferencePlugin(PluginInfo *pluginInfo)
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
        case PLUGINVIEW:
            {
            } break;

        case PLUGINMODEL:
            {
            } break;

        case ROOTMODEL:
            {
            } break;

        case DATAMANAGER:
            {
            } break;

        case DATASOURCE:
            {
                myReferencedPlugin = qobject_cast<ICOMPortDataSource*>(pluginInfo->Instance);

                if(!myReferencedPlugin)
                {
                    qDebug() << pluginInfo->Meta->Name << "is not ICOMPortDataSource.";
                    return;
                }

                qDebug() << "ICOMPortDataSource succesfully set.";
            } break;
    }
}

void ArduinoSerialDataManager::ReferencePluginClosed(PluginInfo *pluginInfo)
{
}

void ArduinoSerialDataManager::WriteToPort(QString &str)
{
    if(arduinoPort == NULL)
        return;

    str.append('\n');
    arduinoPort->WriteData(str.toStdString().c_str());
}

void ArduinoSerialDataManager::ProcessBuffer(QByteArray *buffer)
{
    //    messageBuffer.append( QString::fromStdString(buffer->toStdString()));
    //    qDebug() << "messageBuffer:" << messageBuffer;
    //    int pos = inputParser.indexIn(messageBuffer);
    //    int lastCapturePos = -1;
    //    while(pos != -1)
    //    {
    //        QString res = inputParser.capturedTexts().at(1);
    //        qDebug() << "ProcessBuffer" << res;
    //        if(res.contains("Osc"))
    //        {
    //            QStringList args = res.split(',');
    //            if(args.length() > 1)
    //            {
    //                QByteArray byteValue = args[1].toStdString().c_str();
    //                short unsigned int value = ((byteValue[0] & 0xFF) << 8) + (char)byteValue[1];
    //                emit ReadOscilloscopeValue(value);
    //            }
    //        }
    //        lastCapturePos = pos;
    //        pos += inputParser.matchedLength();
    //        pos = inputParser.indexIn(messageBuffer, pos);
    //    }
    //    if(lastCapturePos != -1)
    //        messageBuffer = messageBuffer.mid(lastCapturePos);
    messageByteBuffer.append(*buffer);
    //    qDebug() << "messageBuffer:" << messageByteBuffer;
    int pos = messageByteBuffer.indexOf('{');
    int endPos = messageByteBuffer.indexOf('}');
    bool isCaptured = (pos != -1) && (endPos != -1);
    int captureLenght;
    int lastCapturePos = -1;

    while(isCaptured)
    {
        captureLenght = endPos - pos;
        QByteArray res = messageByteBuffer.mid(pos+1, captureLenght-1);
        qDebug() << "ProcessBuffer" << res;

        if(res.contains("Osc"))
        {
            QList<QByteArray> args = res.split(',');

            if(args.length() > 1)
            {
                QByteArray byteValue = args[1];
                short unsigned int value = ((byteValue[0] & 0xFF) << 8) | (byteValue[1] & 0xFF);
                qDebug() << "Value:" << value;
                emit ReadOscilloscopeValue(value);
            }
        }

        lastCapturePos = pos;
        pos += captureLenght;
        endPos += captureLenght;
        pos = messageByteBuffer.indexOf('{',pos);
        endPos = messageByteBuffer.indexOf('}', endPos);
        isCaptured = (pos != -1) && (endPos != -1);
    }

    if(lastCapturePos != -1)
        messageByteBuffer = messageByteBuffer.mid(lastCapturePos);
}

void ArduinoSerialDataManager::ReadPortData(QByteArray *buffer)
{
    ProcessBuffer(buffer);
}

void ArduinoSerialDataManager::SetPinMode(int pin, IArduinoSerialDataManager::PinMode pinMode)
{
    auto str = QString("x,pinMode,%1,%2").arg(pin).arg(pinMode);
    WriteToPort(str);
}

void ArduinoSerialDataManager::DigitalWrite(int pin, IArduinoSerialDataManager::DigitalValue value)
{
    auto str = QString("x,digitalWrite,%1,%2").arg(pin).arg(value);
    WriteToPort(str);
}

void ArduinoSerialDataManager::AnalogWrite(int pin, int value)
{
    auto str = QString("x,analogWrite,%1,%2").arg(pin).arg(value);
    WriteToPort(str);
}

void ArduinoSerialDataManager::SetDelay(int delayIntMills)
{
    auto str = QString("x,delay,%1").arg(delayIntMills);
    WriteToPort(str);
}

void ArduinoSerialDataManager::OscilloscopeOn(int pin, int resolution, int trigger)
{
    auto str = QString("x,oscilloscopeOn,%1,%2,%3").arg(pin).arg(resolution).arg(trigger);
    WriteToPort(str);
}

void ArduinoSerialDataManager::OscilloscopeGo(IArduinoSerialDataManager::OscilloscopeRepeatMode mode)
{
    auto str = QString("x,oscilloscopeGo,%1").arg(mode);
    WriteToPort(str);
}

void ArduinoSerialDataManager::OscilloscopeOff()
{
    auto str = QString("x,oscilloscopeOff");
    WriteToPort(str);
}

void ArduinoSerialDataManager::DigitalRead(int pin)
{
    auto str = QString("x,digitalRead,%1").arg(pin);
    WriteToPort(str);
}

void ArduinoSerialDataManager::AnalogRead(int pin)
{
    auto str = QString("x,analogRead,%1").arg(pin);
    WriteToPort(str);
}

void ArduinoSerialDataManager::TimeSinceDeviceStart()
{
    auto str = QString("x,millis");
    WriteToPort(str);
}


