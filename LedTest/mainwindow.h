#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QStandardItemModel>
#include <QDebug>
#include <QTimer>

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
    void Setup();
    void SendMessage(QString message);
    void on_horizontalSlider_sliderMoved(int position);
    void on_horizontalSlider_2_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    QSerialPort *arduinoPort;
    QString activePortName;
    bool isPortSet;
    QStandardItemModel *portsData;
    QTimer *readTimer;
    QString serialBuffer;
    QRegExp inputParser;

    QIODevice::OpenModeFlag openModeFlag;
    struct DeviceInfo{
        quint16 vendorId;
        quint16 productId;
        bool Compare(quint16 vendorId, quint16 productId)
        {
            return this->vendorId == vendorId &&
                    this->productId == productId;
        }
    };

    DeviceInfo ArduinoUno;

    void UpdateLED(char pinId, int value);
};

#endif // MAINWINDOW_H
