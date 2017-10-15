#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QStandardItemModel>
#include <QDebug>
#include <QTimer>
#include <QRadioButton>
#include <QGridLayout>
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:
    void ProcessPortInput();
    bool Setup();
    void SendMessage(QString message);
    void InputPinChanged();
    void OutputPinChanged();

    void on_buttonSetup_clicked();
    void on_buttonSend_clicked();
    void on_horizontalSliderHorizontal_sliderMoved(int position);
    void on_horizontalSlider_sliderReleased();

//    void vertScrollBarChanged(int value);
//    void horzScrollBarChanged(int value);
//    void xAxisChanged(QCPRange range);
//    void yAxisChanged(QCPRange range);
    void on_horizontalPlotScroll_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    QList<QRadioButton*> inputPins;
    QList<QRadioButton*> outputPins;
    const int pinRowsCount = 7;

    QSerialPort *arduinoPort;
    QString activePortName;
    bool isPortSet;
    QStandardItemModel *portsData;
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
    void ReplotPlot();
    void SetupPins();
    void InsertNewPin(QString name, QLayout *lay);
};

#endif // MAINWINDOW_H
