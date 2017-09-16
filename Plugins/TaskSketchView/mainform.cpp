#include "mainform.h"
#include "ui_mainform.h"

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    myModel = NULL;
    ui->setupUi(this);
    galleryForm = new GalleryForm(this);
    galleryForm->setVisible(false);
    imageFormat = "png";
    //connect(ui->buttonSave, SIGNAL(clicked(bool)), SLOT(on_buttonSave_clicked()));
    //connect(ui->buttonClear, SIGNAL(clicked(bool)), ui->widgetPaint, SLOT(Clean()));
    connect(galleryForm, SIGNAL(OnItemDelete(int)), SLOT(OnItemDelete(int)));
    connect(galleryForm, SIGNAL(OnItemConvert(int)), SLOT(OnItemConvertSlot(int)));

#ifdef Q_OS_ANDROID
    ui->buttonClear->setFocusPolicy(Qt::NoFocus);
    ui->buttonClear->setToolTip("");
    ui->buttonOpenGallery->setFocusPolicy(Qt::NoFocus);
    ui->buttonOpenGallery->setToolTip("");
    ui->buttonSave->setFocusPolicy(Qt::NoFocus);
    ui->buttonSave->setToolTip("");
    ui->buttonClose->setVisible(false);
#endif
}

MainForm::~MainForm()
{
    delete galleryForm;
    delete ui;
}

void MainForm::SetModel(ITaskSketchModel *model)
{
    if(myModel != NULL)
        return;

    myModel = model;
    taskModel = model->GetModel();
    sketchModel = model->GetInternalModel();
    galleryForm->SetModel(sketchModel);

    int n = sketchModel->rowCount();
    for(int i = 0; i < n; ++i)
    {
        QModelIndex index = sketchModel->index(i, 0);
        QByteArray ba = index.data().toByteArray();
        galleryForm->AddImage(i, ba);
    }
}

void MainForm::resizeEvent(QResizeEvent *event)
{
    galleryForm->setGeometry(rect());
}

void MainForm::OnItemDelete(int index)
{
    sketchModel->removeRows(index, 1);
}

void MainForm::OnItemConvertSlot(int index)
{
    myModel->ConvertSketchToTask(index);
    //myModel->OpenTaskEdit(taskModel->rowCount()-1);
}

void MainForm::on_buttonClear_clicked()
{
    ui->widgetPaint->Clean();
}

void MainForm::on_buttonSave_clicked()
{
    QByteArray array = ui->widgetPaint->GetRawData();

    sketchModel->insertRows(0, 1);
    QModelIndex root = sketchModel->index(0, 0);
    sketchModel->setData(root, QVariant(array));
    galleryForm->AddImage(0, array);
}

void MainForm::on_buttonOpenGallery_clicked()
{
    galleryForm->setVisible(true);
}

void MainForm::on_buttonClose_clicked()
{
    emit onClose();
}
