#ifndef COMMONARDUINOPROTOCOLMODEL_H
#define COMMONARDUINOPROTOCOLMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "icommonarduinoprotocolmodel.h"

// Here you can include your related plugins interfaces
// For example:
// #include "../../[PluginTypes]/SomePlugin/isomeplugin.h"
// [Plugin types]: DataSources, DataManagers, Models, Views
#include "../../DataManagers/HardwareDataManager/ihardwaredatamanager.h"

//! addtogroup CommonArduinoProtocolModel_imp
//! {
class CommonArduinoProtocolModel : public
    QObject,
    ICommonArduinoProtocolModel,
    IHardwareDataManager::IProtocolHandler
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IModelPlugin
        ICommonArduinoProtocolModel
    )

public:
    CommonArduinoProtocolModel();
    ~CommonArduinoProtocolModel();

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

    // IModelPlugin interface
public slots:
    bool Open(IModelPlugin *model) override;
    void Close() override;


private:
    PluginInfo *pluginInfo;

    // ISomePlugin *myReferencedPlugin;

    PluginInfo *openedModel;
    QList< PluginInfo* > relatedModelPlugins;
    PluginInfo *openedView;
    QList< PluginInfo* > relatedViewPlugins;

    // IProtocolHandler interface
public:
    bool CheckPortProtocolSupport(QObject *portHandler) override;
    bool SetPort(QObject *portHandler) override;

    // Write your internal methods here
signals:
    void WriteData(QByteArray &buffer);

private slots:
    void ReadData(QByteArray *buffer);

    // ICommonArduinoProtocolModel interface
public:
    void SetPinMode(int pin, PinMode pinMode) override;
    void DigitalRead(int pin) override;
    void DigitalWrite(int pin, DigitalValue value) override;
    void AnalogRead(int pin) override;
    void AnalogWrite(int pin, int value) override;
    void TimeSinceDeviceStart() override;
    void SetDelay(int delayIntMills) override;
    void OscilloscopeOn(int pin, int resolution, int trigger) override;
    void OscilloscopeGo(OscilloscopeRepeatMode mode) override;
    void OscilloscopeOff() override;

signals:
    void ReadOscilloscopeValue(int value);
    void ReadDigitalValue(DigitalValue value);
    void ReadAnalogValue(int value);
    void ReadTimeSinceDeviceStartValue(int value);
};
//! }
#endif // COMMONARDUINOPROTOCOLMODEL_H

