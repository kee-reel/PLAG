#include "neuralnetworkview.h"

NeuralNetworkView::NeuralNetworkView()
{
    mainForm = new MainForm;
    mainForm->setVisible(false);
    myModel = NULL;
}

NeuralNetworkView::~NeuralNetworkView()
{
    delete trainingSamples;
    delete testSamples;
}

void NeuralNetworkView::OnAllSetup()
{

}

QString NeuralNetworkView::GetLastError()
{

}

void NeuralNetworkView::SetModel(QObject *model)
{
    myModel = qobject_cast<INeuralNetworkModel*>(model);
    if(!myModel)
    {
        qDebug() << model->objectName() << "is not ITaskListModel.";
        return;
    }
    qDebug() << "ITaskListModel succesfully set.";
}

bool NeuralNetworkView::Open(QWidget *parent)
{
    qDebug() << "View OPEN" << parent;
    if(!myModel)
    {
        qDebug() << "Model isn't set!";
        return false;
    }
    connect(mainForm, SIGNAL(onClose()), this, SLOT(Close()));
    parent->layout()->addWidget(mainForm);
    mainForm->setParent(parent);
    mainForm->show();
    mainForm->SetModel(myModel);

    myModel->SetupNetwork(INeuralNetworkModel::NetworkParams() = {100, 0.1});
    myModel->AddLayer(INeuralNetworkModel::Input, INeuralNetworkModel::LayerParams() = {2, 0, 0, 4, 0});
    //myModel->AddLayer(INeuralNetworkModel::Hidden, INeuralNetworkModel::LayerParams() = {2, 0.7, 0.3, 100, 0});
    myModel->AddLayer(INeuralNetworkModel::Output, INeuralNetworkModel::LayerParams() = {1, 0.7, 0.3, 2, 0});

    trainingSamples = new QVector<INeuralNetworkModel::TrainSample>();
    INeuralNetworkModel::TrainSample buf;
    buf.first = {1, 1};
    buf.second = {1};
    trainingSamples->append(buf);
    buf.first = {-1, -1};
    buf.second = {0};
    trainingSamples->append(buf);
    buf.first = {-1, 1};
    buf.second = {1};
    trainingSamples->append(buf);
    buf.first = {1, -1};
    buf.second = {1};
    trainingSamples->append(buf);
    myModel->SetupTrainingSamples(trainingSamples);

    testSamples = new QVector<INeuralNetworkModel::TrainSample>();
    buf.first = {1, 0};
    buf.second = {1};
    testSamples->append(buf);
    buf.first = {0, -1};
    buf.second = {0};
    testSamples->append(buf);
    buf.first = {-0.4, 1};
    buf.second = {1};
    testSamples->append(buf);
    buf.first = {0.7, -1};
    buf.second = {1};
    testSamples->append(buf);
    myModel->SetupTestSamples(testSamples);

    return true;
}

bool NeuralNetworkView::Close()
{
    disconnect(mainForm, SIGNAL(onClose()), this, SLOT(Close()));
    mainForm->hide();
    myModel->CloseFromView(this);
    return true;
}
