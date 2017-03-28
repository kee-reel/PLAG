#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include <QDebug>
#include "../NeuralNetworkModel/ineuralnetworkmodel.h"

namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();
    void SetModel(INeuralNetworkModel *Model);
signals:
    void onClose();
private slots:

    void on_buttonRunTrain_clicked();

    void on_buttonRunTest_clicked();

    void on_buttonClose_clicked();

private:
    Ui::MainForm *ui;
    INeuralNetworkModel *model;
};

#endif // MAINFORM_H
