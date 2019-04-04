#include "mainform.h"
#include "ui_mainform.h"

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
}

MainForm::~MainForm()
{
    delete galleryForm;
    delete ui;
}

