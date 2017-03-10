#include "mainform.h"
#include "ui_mainform.h"

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
    addForm = new AddForm(this);
    myTreeView = ui->treeView;//new MyTreeView(this);
    ui->verticalLayout->addWidget(myTreeView);

    setAcceptDrops(true);
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::SetModel(QAbstractItemModel *model)
{
    this->model = model;
    currentModelIndex = NULL;
    myTreeView->setModel(model);
    addForm->SetModel(model);
}

void MainForm::resizeEvent(QResizeEvent *event)
{
    qDebug() << "Resize";
    addForm->resize(event->size());
}

void MainForm::on_buttonAdd_clicked()
{
    QModelIndexList list = myTreeView->selectionModel()->selectedIndexes();
    for(int i = 0; i < list.count(); i++) {
        model->insertRows(list[i].row(), 1, list[i]);
    }
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
    QModelIndexList list = myTreeView->selectionModel()->selectedIndexes();
    for(int i = 0; i < list.count(); i++) {
        model->removeRows(list[i].row(), 1, list[i].parent());
    }
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
