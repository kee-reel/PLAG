#include "mainform.h"
#include "ui_mainform.h"

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
    galleryForm = new GalleryForm(this);
    galleryForm->setVisible(false);
    imageFormat = "png";
    connect(ui->buttonClear, SIGNAL(clicked(bool)), ui->widgetPaint, SLOT(Clean()));
}

MainForm::~MainForm()
{
    delete galleryForm;
    delete ui;
}

void MainForm::SetModel(ITaskSketchModel *model)
{
    this->myModel = model;
}

void MainForm::resizeEvent(QResizeEvent *event)
{
    galleryForm->setGeometry(rect());
}

void MainForm::on_buttonClose_clicked()
{
    emit onClose();
}

void MainForm::on_buttonCreate_clicked()
{

}

void MainForm::on_buttonSave_clicked()
{
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    ui->widgetPaint->image.save(&buffer, "PNG");
    buffer.close();
}

void MainForm::on_buttonOpenGallery_clicked()
{
    galleryForm->setVisible(true);
}
