#include "mainform.h"
#include "ui_mainform.h"

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
    trainingSamples = new QVector<INeuralNetworkModel::TrainSample>();
    testSamples = new QVector<INeuralNetworkModel::TrainSample>();
    itemModel = new QStandardItemModel();
    imagesModel = new QStandardItemModel();
    ui->listView->setModel(itemModel);
    ui->listViewImages->setModel(imagesModel);
    ui->tabWidget->setTabEnabled(0, false);
}

MainForm::~MainForm()
{
    delete ui;
    delete trainingSamples;
    delete testSamples;
}

void MainForm::SetModel(INeuralNetworkModel *Model)
{
    model = Model;
    isStatsChanged = true;
}

void MainForm::MarkNetworkStatsToUpdate()
{
    isStatsChanged = true;
}

bool MainForm::UpdateNetworkStats()
{
    if(layersList.count() < 2)
        return false;
    int width = inputImages.first().width();
    int height = inputImages.first().height();
    layersList.first().size = width * height;
    layersList.last().size = inputImages.count();

    model->SetupNetwork(INeuralNetworkModel::NetworkParams() = {ui->spinEpoch->value(), ui->spinErrorThreshold->value()});
    model->AddLayer(INeuralNetworkModel::Input, layersList.first());
    for(int i = 1; i < layersList.count()-1; ++i)
        model->AddLayer(INeuralNetworkModel::Hidden, layersList[i]);
    model->AddLayer(INeuralNetworkModel::Output, layersList.last());

    trainingSamples->clear();
    testSamples->clear();

    INeuralNetworkModel::TrainSample buf;
    buf.first.resize(layersList.first().size);
    buf.second.resize(inputImages.count());
    for(int i = 0; i < inputImages.count(); ++i)
    {
        for(int h = 0; h < height; ++h)
            for(int w = 0; w < width; ++w)
                buf.first[h*width + w] = inputImages[i].pixelColor(w, h).red()/255.;
        for(int j = 0; j < inputImages.count(); ++j)
            buf.second[j] = 0;
        buf.second[i] = 1;
        trainingSamples->append(buf);
    }
    model->SetupTrainingSamples(trainingSamples);

    testSamples->append({{1, 1.1},      {1}});
    testSamples->append({{1, 0.5},      {1}});
    testSamples->append({{0.2, 0},      {0}});
    testSamples->append({{0.2, 0.1},    {0}});
    model->SetupTestSamples(testSamples);

    isStatsChanged = false;
    return true;
}

void MainForm::UpdateLayerStatsGUI()
{
    QModelIndex index = ui->listView->selectionModel()->currentIndex();
    if(!index.isValid())
    {
        ui->tabWidget->setTabEnabled(0, false);
        return;
    }

    ui->tabWidget->setTabEnabled(0, true);
    INeuralNetworkModel::LayerParams params = layersList[index.row()];
    ui->spinSize->setValue(params.size);
    ui->spinLearnSpeed->setValue(params.LearnSpeed);
    ui->spinMoment->setValue(params.Moment);
    ui->spinFuncIndent->setValue(params.FuncIndent);
    ui->spinBias->setValue(params.Bias);
}

void MainForm::on_buttonRunTrain_clicked()
{
    if(isStatsChanged)
        if(!UpdateNetworkStats())
            return;

    if(model->RunTraining())
    {
        qDebug() << "Network trained!";
    }
    else
        qDebug() << "Network not trained!";
}

void MainForm::on_buttonRunTest_clicked()
{
    if(isStatsChanged)
        if(!UpdateNetworkStats())
            return;

    if(model->RunTest())
    {
        qDebug() << "Network passed all tests!";
    }
    else
    {
        qDebug() << "Network not passed tests!";
    }
}

void MainForm::on_buttonClose_clicked()
{
    emit onClose();
}

void MainForm::on_buttonAdd_clicked()
{
    INeuralNetworkModel::LayerParams newLayer = {1, 0.7, 0.5, 2, 0};
    layersList.append(newLayer);
    QStandardItem *item = new QStandardItem(QString::number(layersList.count()));
    QBrush brush = QBrush(QColor(100+qrand()%20, 100+qrand()%50, 130+qrand()%120));
    item->setBackground(brush);
    itemModel->appendRow(item);
    UpdateLayerStatsGUI();
}

void MainForm::on_buttonRemove_clicked()
{
    QModelIndex index = ui->listView->selectionModel()->currentIndex();
    if(index.isValid())
    {
        itemModel->removeRow(index.row());
        layersList.removeAt(index.row());
    }
    UpdateLayerStatsGUI();
}

void MainForm::on_listView_clicked(const QModelIndex &index)
{
    UpdateLayerStatsGUI();
}

void MainForm::on_spinEpoch_valueChanged(int arg1)
{
    MarkNetworkStatsToUpdate();
}

void MainForm::on_spinErrorThreshold_valueChanged(double arg1)
{
    MarkNetworkStatsToUpdate();
}

void MainForm::on_spinSize_valueChanged(int arg1)
{
    QModelIndex index = ui->listView->selectionModel()->currentIndex();
    if(!index.isValid())
        return;
    layersList[index.row()].size = arg1;
    MarkNetworkStatsToUpdate();
}

void MainForm::on_spinLearnSpeed_valueChanged(double arg1)
{
    QModelIndex index = ui->listView->selectionModel()->currentIndex();
    if(!index.isValid())
        return;
    layersList[index.row()].LearnSpeed = arg1;
    MarkNetworkStatsToUpdate();
}

void MainForm::on_spinMoment_valueChanged(double arg1)
{
    QModelIndex index = ui->listView->selectionModel()->currentIndex();
    if(!index.isValid())
        return;
    layersList[index.row()].Moment = arg1;
    MarkNetworkStatsToUpdate();
}

void MainForm::on_spinFuncIndent_valueChanged(double arg1)
{
    QModelIndex index = ui->listView->selectionModel()->currentIndex();
    if(!index.isValid())
        return;
    layersList[index.row()].FuncIndent = arg1;
    MarkNetworkStatsToUpdate();
}

void MainForm::on_spinBias_valueChanged(double arg1)
{
    QModelIndex index = ui->listView->selectionModel()->currentIndex();
    if(!index.isValid())
        return;
    layersList[index.row()].Bias = arg1;
    MarkNetworkStatsToUpdate();
}

void MainForm::on_buttonLoadImage_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Add Image"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));
    QImage image = QImage(fileName);
    if(image.isNull()) return;
    inputImages.append(image);
    QStandardItem *item = new QStandardItem(QIcon(QPixmap::fromImage(image)), fileName);
    imagesModel->appendRow(item);
}

void MainForm::on_buttonRemoveImages_clicked()
{

}
