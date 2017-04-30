#include "neuralnetworkmodel.h"

NeuralNetworkModel::NeuralNetworkModel()
{
    tableName = "TaskTree";
    activeViewId = -1;
    dataManager = NULL;
    neuralNetwork = NULL;
}

NeuralNetworkModel::~NeuralNetworkModel()
{
}

void NeuralNetworkModel::OnAllSetup()
{

}

QString NeuralNetworkModel::GetLastError()
{

}

void NeuralNetworkModel::AddChildModel(IModelPlugin *model, MetaInfo *meta)
{
    qDebug() << "New child" << meta->Name;
    PluginInfo<IModelPlugin> newPlugin = {model, meta};
    childModelPlugins.append(newPlugin);
}

void NeuralNetworkModel::AddView(IViewPlugin *view, MetaInfo *meta)
{
    PluginInfo<IViewPlugin> newPlugin = {view, meta};
    viewPlugins.append(newPlugin);
    qDebug() << "IPluginView succesfully set.";
}

void NeuralNetworkModel::AddDataManager(QObject *dataManager)
{
    qDebug() <<  "is not IExtendableDataBaseManagerPlugin.";
    this->dataManager = qobject_cast<IExtendableDataBaseManagerPlugin*>(dataManager);
    if(!this->dataManager)
    {
        qDebug() << dataManager->objectName() << "is not IExtendableDataBaseManagerPlugin.";
        return;
    }
    qDebug() << "IExtendableDataBaseManagerPlugin succesfully set.";
}

bool NeuralNetworkModel::Open(IModelPlugin *parent, QWidget *parentWidget)
{
    qDebug() << "NeuralNetworkModel runs";
    if(viewPlugins.count() == 0){
        qDebug() << "I dont have any views!";
        return false;
    }
    myParent = parent;
    myParentWidget = parentWidget;
    activeViewId = 0;

    qDebug() << viewPlugins[activeViewId].meta->Name;
    if(!viewPlugins[activeViewId].plugin->Open(myParentWidget))
    {
        qDebug() << "Can't open first view!";
        return false;
    }

    return true;
}

bool NeuralNetworkModel::CloseFromView(IViewPlugin *view)
{
    activeViewId = -1;
    myParent->ChildSelfClosed(this);
    return true;
}

void NeuralNetworkModel::ChildSelfClosed(IModelPlugin *child)
{

}

INeuralNetworkModel::INeuralNetwork *NeuralNetworkModel::SetupNetwork(QJsonObject *networkParams)
{
    if(!networkParams->contains("Type"))
        return NULL;

    switch (networkParams["Type"]) {
    case "Perceptron":
        if(Perceptron::Make(networkParams))
        break;
    default:
        break;
    }

}

void NeuralNetworkModel::AddLayer(Perceptron::LayerType type, Perceptron::LayerParams params)
{
    neuralNetwork->AddLayer(type, params);
}

void NeuralNetworkModel::ResetLayers()
{
    neuralNetwork->ResetLayers();
}

float NeuralNetworkModel::RunTraining()
{
    return neuralNetwork->RunTraining();
}

float NeuralNetworkModel::RunTest()
{
    return neuralNetwork->RunTest();
}

void NeuralNetworkModel::SetupTrainingSamples(QVector<INeuralNetworkModel::TrainSample> *samples)
{
    neuralNetwork->trainingSamples = samples;
}

void NeuralNetworkModel::SetupTestSamples(QVector<INeuralNetworkModel::TrainSample> *samples)
{
    neuralNetwork->testSamples = samples;
}
