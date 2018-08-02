#include "mainform.h"
#include "ui_mainform.h"

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
    myTreeView = new MyTreeView(this);
    ui->verticalLayout->setDirection(QBoxLayout::BottomToTop);
    ui->verticalLayout->addWidget(myTreeView);
    connect(myTreeView, SIGNAL(clicked(QModelIndex)), SLOT(onTreeViewClicked(QModelIndex)));
    connect(myTreeView, SIGNAL(doubleClicked(QModelIndex)), SLOT(onTreeViewDoubleClicked(QModelIndex)));
    connect(myTreeView, SIGNAL(pressed(QModelIndex)), SLOT(onTreeViewPressed(QModelIndex)));
    myTreeView->setExpandsOnDoubleClick(false);

#ifdef Q_OS_ANDROID
    ui->buttonAdd->setFocusPolicy(Qt::NoFocus);
    ui->buttonAdd->setToolTip("");
    ui->buttonDelete->setFocusPolicy(Qt::NoFocus);
    ui->buttonDelete->setToolTip("");
    ui->buttonEdit->setFocusPolicy(Qt::NoFocus);
    ui->buttonEdit->setToolTip("");
    ui->buttonExit->setVisible(false);
#endif

    addForm = new AddForm(this);
    connect(addForm, SIGNAL(OnClose()), this, SLOT(OnAddFormClosed()));
}

MainForm::~MainForm()
{
    delete addForm;
    delete ui;
}

void MainForm::SetModel(QAbstractItemModel *model)
{
    this->model = model;
    currentModelIndex = nullptr;
    myTreeView->setModel(model);
    addForm->SetModel(model);
}

void MainForm::resizeEvent(QResizeEvent *event)
{
    qDebug() << "Resize";
    addForm->resize(event->size());
}

void MainForm::OnAddFormClosed()
{
    show();
    ui->buttonAdd->setFocusPolicy(Qt::StrongFocus);
    ui->buttonDelete->setFocusPolicy(Qt::StrongFocus);
    ui->buttonEdit->setFocusPolicy(Qt::StrongFocus);
    ui->buttonExit->setFocusPolicy(Qt::StrongFocus);
    myTreeView->setFocusPolicy(Qt::StrongFocus);
    myTreeView->setFocus();
}

void MainForm::on_buttonAdd_clicked()
{
    QModelIndexList list = myTreeView->selectionModel()->selectedIndexes();
    QModelIndex newIndex;
    if(list.count())
    {
        model->insertRows(model->rowCount(list.first()), 1, list.first());
        myTreeView->expand(list.first());
        newIndex = model->index(model->rowCount(list.first())-1, 0, list.first());
    }
    else
    {
        model->insertRows(-1, 1);
        newIndex = model->index(model->rowCount()-1, 0);
    }
    addForm->ShowModelData(newIndex, true);
}

void MainForm::on_buttonExit_clicked()
{
    emit onClose();
}

void MainForm::on_buttonDelete_clicked()
{
    QModelIndexList list = myTreeView->selectionModel()->selectedIndexes();
    for(int i = list.count()-1; i >= 0; --i) {
        model->removeRows(list[i].row(), 1, list[i].parent());
    }
}

void MainForm::on_buttonEdit_clicked()
{
    QModelIndexList list = myTreeView->selectionModel()->selectedIndexes();
    if(list.count())
        addForm->ShowModelData(list.first());
}

void MainForm::onTreeViewPressed(const QModelIndex &index)
{
    currentModelIndex = &index;
}

void MainForm::onTreeViewClicked(const QModelIndex &index)
{
    if(expandFlag)
        expandFlag = false;
    else
    {
        myTreeView->setExpanded(index, !myTreeView->isExpanded(index));
        expandFlag = true;
    }
}
