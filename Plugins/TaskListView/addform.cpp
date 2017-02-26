#include "addform.h"
#include "ui_addform.h"
#include <QDebug>

AddForm::AddForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddForm)
{
    ui->setupUi(this);
    mapper = new QDataWidgetMapper(this);
    close();
}

AddForm::~AddForm()
{
    delete ui;
}

void AddForm::SetModel(QAbstractItemModel *model)
{
    mapper->setModel(model);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    ui->label_2->setText(model->headerData(0, Qt::Horizontal).typeName());
    mapper->addMapping(ui->lineEdit_2, 0);
}

void AddForm::ShowModelData(const QModelIndex &index)
{
    show();
    mapper->setCurrentModelIndex(index);
}

void AddForm::on_buttonOk_clicked()
{
    mapper->submit();
    close();
}

void AddForm::on_buttonClose_clicked()
{
    close();
}
