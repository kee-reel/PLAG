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

void MainForm::SetModel(ITaskSketchModel *model)
{
    this->myModel = model;
}

void MainForm::resizeEvent(QResizeEvent *event)
{
    qDebug() << "Resize";

}
