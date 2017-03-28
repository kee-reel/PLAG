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
    ui->listView->setModel(itemModel);
    connect(this->ui->spinEpoch,            SIGNAL(valueChanged(int)), this, SLOT(MarkNetworkStatsToUpdate()));
    connect(this->ui->spinErrorThreshold,   SIGNAL(valueChanged(double)), this, SLOT(MarkNetworkStatsToUpdate()));
    connect(this->ui->listView,   SIGNAL(indexesMoved(QModelIndexList)), this, SLOT(MarkNetworkStatsToUpdate()));
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

void MainForm::UpdateNetworkStats()
{
    model->SetupNetwork(INeuralNetworkModel::NetworkParams() = {ui->spinEpoch->value(), ui->spinErrorThreshold->value()});
    model->AddLayer(INeuralNetworkModel::Input, INeuralNetworkModel::LayerParams() = {2, 0, 0, 4, 0});
    model->AddLayer(INeuralNetworkModel::Hidden, INeuralNetworkModel::LayerParams() = {2, 0.7, 0.3, 2, 0});
    model->AddLayer(INeuralNetworkModel::Output, INeuralNetworkModel::LayerParams() = {1, 0.7, 0.5, 2, 0});

    trainingSamples->clear();
    testSamples->clear();

    trainingSamples->append({{1, 1}, {1}});
    trainingSamples->append({{0, 0}, {0}});
    trainingSamples->append({{0, 1}, {1}});
    trainingSamples->append({{1, 0}, {1}});
    model->SetupTrainingSamples(trainingSamples);

    testSamples->append({{1, 1.1},      {1}});
    testSamples->append({{1, 0.5},      {1}});
    testSamples->append({{0.2, 0},      {0}});
    testSamples->append({{0.2, 0.1},    {0}});
    model->SetupTestSamples(testSamples);

    isStatsChanged = false;
}

void MainForm::on_buttonRunTrain_clicked()
{
    if(isStatsChanged)
        UpdateNetworkStats();

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
        UpdateNetworkStats();

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
    QStandardItem *item = new QStandardItem( QString("N=%0|S=%1|M=%2|In=%3|B=%4")
                                             .arg(newLayer.size)
                                             .arg(newLayer.LearnSpeed)
                                             .arg(newLayer.Moment)
                                             .arg(newLayer.FuncIndent)
                                             .arg(newLayer.Bias)
                                             );
    QBrush brush = QBrush(QColor(100+qrand()%20, 100+qrand()%50, 130+qrand()%120));
    item->setBackground(brush);
    itemModel->appendRow(item);

}

void MainForm::on_buttonRemove_clicked()
{
    QModelIndex index = ui->listView->selectionModel()->currentIndex();
    if(index.isValid())
    {
        itemModel->removeRow(index.row());
        layersList.removeAt(index.row());
    }
}

void MainForm::on_listView_clicked(const QModelIndex &index)
{
    if(index.isValid())
    {
        itemModel->removeRow(index.row());
        layersList.removeAt(index.row());
    }
}
