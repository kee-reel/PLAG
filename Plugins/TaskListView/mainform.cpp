#include "mainform.h"
#include "ui_mainform.h"

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::SetModel(QAbstractItemModel *taskTree)
{
    if(taskTree)
        ui->treeView->setModel(taskTree);
}

//void MainForm::paintEvent(QPaintEvent *event)
//{
//    QPainter p;
//    p.begin(this);

//    p.setRenderHint(QPainter::Antialiasing);
//    p.setPen(QPen(QColor(Qt::black), 5));
//    p.drawRect(rect());

//    QFont m_font;
//    m_font.setBold(true);

//    p.setFont(QFont("Arial", 9));

//    p.end();
//}

void MainForm::on_buttonAdd_clicked()
{

}

void MainForm::on_buttonExit_clicked()
{
    emit onClose();
}


