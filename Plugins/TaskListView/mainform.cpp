#include "mainform.h"
#include "ui_mainform.h"

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
    addForm = new AddForm(this);

//    ui->treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
//    ui->treeView->setDragEnabled(true);
//    ui->treeView->setAcceptDrops(true);
//    ui->treeView->setDropIndicatorShown(true);
//    ui->treeView->setDragDropMode(QAbstractItemView::InternalMove);
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::SetModel(QAbstractItemModel *model)
{
    this->model = model;
    currentModelIndex = NULL;
    ui->treeView->setModel(model);
    addForm->SetModel(model);
}

void MainForm::resizeEvent(QResizeEvent *event)
{
    qDebug() << "Resize";
    addForm->resize(event->size());
}

void MainForm::on_buttonAdd_clicked()
{
    if(currentModelIndex)
        model->insertRows(currentModelIndex->row(), 1, *currentModelIndex);
    else
        model->insertRows(0, 1);
}

void MainForm::on_buttonExit_clicked()
{
    emit onClose();
}

void MainForm::on_treeView_doubleClicked(const QModelIndex &index)
{
    if(currentModelIndex)
        addForm->ShowModelData(index);
}

void MainForm::on_buttonDelete_clicked()
{
    if(currentModelIndex)
        model->removeRows(currentModelIndex->row(), 1, currentModelIndex->parent());
}

void MainForm::on_treeView_pressed(const QModelIndex &index)
{
    currentModelIndex = &index;
}

void MainForm::on_buttonEdit_clicked()
{
    if(currentModelIndex)
        addForm->ShowModelData(*currentModelIndex);
}
