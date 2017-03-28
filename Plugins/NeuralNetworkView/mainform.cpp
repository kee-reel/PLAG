#include "mainform.h"
#include "ui_mainform.h"

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::SetModel(INeuralNetworkModel *Model)
{
    model = Model;
}

void MainForm::on_buttonRunTrain_clicked()
{
    if(model->RunTraining())
    {
        qDebug() << "Network trained!";
    }
    else
        qDebug() << "Network not trained!";
}

void MainForm::on_buttonRunTest_clicked()
{
    if(model->RunTest())
    {
        qDebug() << "Network passed all tests!";
    }
    else
    {
        qDebug() << "Network not passed tests!";
    }
}

void MainForm::on_buttonClose_clicked()
{
    emit onClose();
}
