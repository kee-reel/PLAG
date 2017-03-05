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

void MainForm::resizeEvent(QResizeEvent *event)
{
    addForm->resize(event->size());
}

void MainForm::on_buttonAdd_clicked()
{
    qDebug() << "on_buttonAdd_clicked";
    model->insertRows(currentModelIndex->row(), 1, currentModelIndex->parent());
}

void MainForm::on_buttonExit_clicked()
{
    emit onClose();
}

void MainForm::on_treeView_doubleClicked(const QModelIndex &index)
{
    addForm->ShowModelData(index);
}

void MainForm::on_buttonDelete_clicked()
{
    qDebug() << "on_buttonDelete_clicked";
    model->removeRows(currentModelIndex->row(), 1, currentModelIndex->parent());
}

void MainForm::on_treeView_pressed(const QModelIndex &index)
{
    currentModelIndex = &index;
    qDebug() << currentModelIndex->row();
}

void MainForm::on_buttonEdit_clicked()
{
    addForm->ShowModelData(*currentModelIndex);
}
