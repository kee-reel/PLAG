#ifndef COMPORTDATASOURCE_H
#define COMPORTDATASOURCE_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QDateTime>

#include "icomportdatasource.h"
#include "devicepin.h"

// Here you can include your related plugins interfaces
// For example: #include "../../Models/SomeModel/isomemodel.h"

//! addtogroup COMPortDataSource_imp
//! {
class COMPortDataSource : public QObject, ICOMPortDataSource
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
            IDataSourcePlugin
            ICOMPortDataSource
            )

public:
    COMPortDataSource();
    ~COMPortDataSource();

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

    // IDataSourcePlugin interface
public:
    void Setup() override;

private:
    PluginInfo *pluginInfo;

private: // Internal methods and fields:
    QList<DevicePin*> inputPins;
    QList<DevicePin*> outputPins;
    const int pinRowsCount = 7;

    QSerialPort *arduinoPort;
    QString activePortName;
    bool isPortSet;
    QTimer *readTimer;
    QString serialBuffer;
    QRegExp inputParser;
    QVector<double> inputData;
    QVector<double> timeScale;
    double startTime;
    double windowXScale;
    double windowYScale;
    QString activeOutPin;

    QIODevice::OpenModeFlag openModeFlag;
    struct DeviceInfo{
        QString name;
        quint16 vendorId;
        quint16 productId;
        int inputPins;
        int outputPins;
        bool Compare(quint16 vendorId, quint16 productId)
        {
            return this->vendorId == vendorId &&
                    this->productId == productId;
        }
    };

    DeviceInfo ArduinoUno;

    void SetPinOutput(int value);
    void MakePlot(int graph, QVector<double> &x, QVector<double> &y);
    void SetupPins();

private slots:
    void ProcessPortInput();
    void SendMessage(QString message);
};
//! }
#endif // COMPORTDATASOURCE_H
