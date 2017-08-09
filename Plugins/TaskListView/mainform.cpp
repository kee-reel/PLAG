#include "mainform.h"
#include "ui_mainform.h"

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
    myTreeView = ui->treeView;// new MyTreeView(this);
    myTreeView->installEventFilter(this);
    ui->verticalLayout->setDirection(QBoxLayout::BottomToTop);
    ui->verticalLayout->addWidget(myTreeView);

    addForm = new AddForm(this);
    connect(addForm, SIGNAL(OnClose()), this, SLOT(OnAddFormClosed()));
}

MainForm::~MainForm()
{
    delete ui;
}

bool MainForm::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type()) {
    case QEvent::KeyRelease:{
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        switch (keyEvent->key()) {
        case Qt::Key_Space:
        case Qt::Key_Enter:
            on_buttonEdit_clicked();
            break;
        default:
            break;
        }
    }break;

    default:
        return false;
        break;
    }
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
    model->insertColumn(1);
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
        ui->buttonAdd->setFocusPolicy(Qt::NoFocus);
        ui->buttonDelete->setFocusPolicy(Qt::NoFocus);
        ui->buttonEdit->setFocusPolicy(Qt::NoFocus);
        ui->buttonExit->setFocusPolicy(Qt::NoFocus);
        myTreeView->setFocusPolicy(Qt::NoFocus);
        addForm->ShowModelData(list.first());
    }
}
