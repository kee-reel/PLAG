#ifndef ARDUINOSERIALDATAMANAGER_H
#define ARDUINOSERIALDATAMANAGER_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "iarduinoserialdatamanager.h"

// Here you can include your related plugins interfaces
// For example:
// #include "../../[PluginTypes]/SomePlugin/isomeplugin.h"
// [Plugin types]: DataSources, DataManagers, Models, Views

#include "../../DataSources/COMPortDataSource/icomportdatasource.h"

//! addtogroup ArduinoSerialDataManager_imp
//! {
class ArduinoSerialDataManager : public
    QObject,
    IArduinoSerialDataManager
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IDataManagerPlugin
        IArduinoSerialDataManager
    )

public:
    ArduinoSerialDataManager();
    ~ArduinoSerialDataManager();

    // IPlugin interface
public:
    void SetPluginInfo(PluginInfo *pluginInfo) override;
    void OnAllSetup() override;
    QString GetLastError() override;
    void AddReferencePlugin(PluginInfo *pluginInfo) override;

public slots:
    void ReferencePluginClosed(PluginInfo *pluginInfo) override;

signals:
    void OnClose(PluginInfo*);
    void OnClose();

    // IArduinoSerialDataManager interface
public:
    void SetPinMode(int pin, PinMode pinMode) override;
    void DigitalWrite(int pin, DigitalValue value) override;
    void AnalogWrite(int pin, int value) override;
    void SetDelay(int delayIntMills) override;
    void OscilloscopeOn(int pin, int resolution, int trigger) override;
    void OscilloscopeGo(OscilloscopeRepeatMode mode) override;
    void OscilloscopeOff() override;

    void DigitalRead(int pin) override;
    void AnalogRead(int pin) override;
    void TimeSinceDeviceStart() override;
signals:
    void ReadOscilloscopeValue(int value);
    void ReadDigitalValue(DigitalValue value);
    void ReadAnalogValue(int value);
    void ReadTimeSinceDeviceStartValue(int value);

private:
    PluginInfo *pluginInfo;
    ICOMPortDataSource* myReferencedPlugin;
    ICOMPortDataSource::ISerialPortHandler *arduinoPort;

    QRegExp inputParser;
    QString messageBuffer;
    QByteArray messageByteBuffer;

    void SetupPort();
    void WriteToPort(QString &str);

    void ProcessBuffer(QByteArray *buffer);

private slots:
    void ReadPortData(QByteArray *buffer);
};
//! }
#endif // ARDUINOSERIALDATAMANAGER_H
