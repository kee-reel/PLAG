#include "mainform.h"
#include "ui_mainform.h"

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
    addForm = new AddForm(this);
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::SetModel(QAbstractItemModel *model)
{
    this->model = model;
    ui->treeView->setModel(model);
    addForm->SetModel(model);
}

//void MainForm::resizeEvent(QResizeEvent *event)
//{
//    addForm->resize(event->size());
//}

void MainForm::on_buttonAdd_clicked()
{

}

void MainForm::on_buttonExit_clicked()
{
    emit onClose();
}

void MainForm::on_treeView_doubleClicked(const QModelIndex &index)
{
    addForm->ShowModelData(index);
}
