#include "addform.h"
#include "ui_addform.h"

AddForm::AddForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddForm)
{
    ui->setupUi(this);
    mapper = new QDataWidgetMapper(this);
    hide();
}

AddForm::~AddForm()
{
    delete ui;
}

void AddForm::SetModel(QAbstractItemModel *model)
{
    mapper->setModel(model);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    ui->label_2->setText(model->headerData(0, Qt::Horizontal).toString());
    mapper->addMapping(ui->lineEdit_2, 0);
}

void AddForm::ShowModelData(const QModelIndex &index)
{
    show();
    ui->lineEdit_2->setFocus();
    mapper->setRootIndex(index.parent());
    mapper->setCurrentModelIndex(index);
    qDebug() << "=========================" << index.data() << index.row() << mapper->currentIndex();
}

void AddForm::on_buttonOk_clicked()
{
    mapper->submit();
    on_buttonClose_clicked();
}

void AddForm::on_buttonClose_clicked()
{
    emit OnClose();
    hide();
}

bool AddForm::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::KeyRelease:{
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        qDebug() << keyEvent->key();
        switch (keyEvent->key()) {
        case Qt::Key_Enter:
            qDebug() << event->type();
            on_buttonOk_clicked();
            break;
        case Qt::Key_Escape:
            on_buttonClose_clicked();
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
