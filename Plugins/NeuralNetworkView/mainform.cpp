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
    model->RunTraining();
}

void MainForm::on_buttonRunTest_clicked()
{
    model->RunTest();
}

void MainForm::on_buttonClose_clicked()
{
    emit onClose();
}
