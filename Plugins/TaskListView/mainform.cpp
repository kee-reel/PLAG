#include "mainform.h"
#include "ui_mainform.h"

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
    myTreeView = new MyTreeView(this);//ui->treeView;
    ui->verticalLayout->setDirection(QBoxLayout::BottomToTop);
    ui->verticalLayout->addWidget(myTreeView);

    addForm = new AddForm(this);
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

void MainForm::hideMainWidgets()
{
    ui->verticalLayout->setEnabled(true);
}

void MainForm::on_buttonAdd_clicked()
{
    QModelIndexList list = myTreeView->selectionModel()->selectedIndexes();
    if(list.count())
    {
        for(int i = 0; i < list.count(); i++) {
            model->insertRows(list[i].row(), 1, list[i]);
            myTreeView->expand(list[i]);
        }
    }
    else
        model->insertRows(-1, 1, QModelIndex());
}

void MainForm::on_buttonExit_clicked()
{
    emit onClose();
}

void MainForm::on_treeView_doubleClicked(const QModelIndex &index)
{
    ui->verticalLayout->setEnabled(false);
    addForm->ShowModelData(index);
}

void MainForm::on_buttonDelete_clicked()
{
    QModelIndexList list = myTreeView->selectionModel()->selectedIndexes();
    for(int i = list.count()-1; i >= 0; --i) {
        model->removeRows(list[i].row(), 1, list[i].parent());
    }
}

void MainForm::on_treeView_pressed(const QModelIndex &index)
{
    currentModelIndex = &index;
}

void MainForm::on_buttonEdit_clicked()
{
    QModelIndexList list = myTreeView->selectionModel()->selectedIndexes();
    if(list.count())
    {
        ui->verticalLayout->setEnabled(false);
        addForm->ShowModelData(list.first());
    }
}
