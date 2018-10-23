#include "artnetwork.h"

ARTNetwork::ARTNetwork()
{
    comparingLayer = NULL;
    recognitionLayer = NULL;

    params.size = 0;
    params.L = 2;
    params.similarity = 0.9;

//    QVector<bool> input1{1,1,0,1,1,
//                         1,0,1,0,1};
//    comparingLayer->Input(input1);

//    QVector<bool> input2{0,0,1,0,0,
//                         1,1,1,1,1};
//    comparingLayer->Input(input2);

//    QVector<bool> input3{1,1,1,1,1,
//                         1,0,1,0,1};
//    comparingLayer->Input(input3);

//    QVector<bool> input4{0,0,1,0,0,
//                         0,1,1,1,1};
//    comparingLayer->Input(input4);

//    QVector<bool> input5{1,0,1,0,0,
//                         1,1,1,1,1};
//    comparingLayer->Input(input5);

//    qDebug() << "Result neurons";
//    for(int i = 0; i < recognitionLayer->neurons.length(); ++i)
    //        qDebug() << i << recognitionLayer->neurons[i]->outputWeights;
}

ARTNetwork::~ARTNetwork()
{
    if(comparingLayer) delete comparingLayer;
    if(recognitionLayer) delete recognitionLayer;
}

ARTNetwork *ARTNetwork::Make(QJsonObject &paramsObj)
{
    ARTNetwork *network = new ARTNetwork();
    network->params.size = paramsObj.value("size").toInt();
    network->params.L = paramsObj.value("L").toDouble();
    network->params.similarity = paramsObj.value("similarity").toDouble();
    return network;
}

bool ARTNetwork::SetNetworkParams(QJsonObject paramsObj)
{
    params.L = paramsObj.value("L").toDouble();
    params.similarity = paramsObj.value("similarity").toDouble();
    int size = paramsObj.value("size").toInt();
    if(params.size != size)
    {
        // Recreate layers
        params.size = size;
        if(comparingLayer) delete comparingLayer;
        comparingLayer = new ComparingLayer(params.size, &params);
        if(recognitionLayer) delete recognitionLayer;
        recognitionLayer = new RecognitionLayer(params.size, &params);
        comparingLayer->recognitionLayer = recognitionLayer;
        recognitionLayer->comparingLayer = comparingLayer;
    }
    else
        params.size = size;
}

void ARTNetwork::SetupSamplesF(QJsonObject parameters, QVector<InputSampleF> *samples)
{
    qDebug() << "This type of data is not digestable by ARTNetwork :c";
}

void ARTNetwork::SetupSamplesI(QJsonObject parameters, QVector<InputSampleI> *samples)
{
    inputData = samples;
}

bool ARTNetwork::AddLayer(QJsonObject layerParams)
{

}

void ARTNetwork::ResetLayers()
{

}

float ARTNetwork::RunTrainSet()
{

}

QVector<QVariant> ARTNetwork::RunTrainingAndGetResult()
{
    if(!comparingLayer) comparingLayer = new ComparingLayer(params.size, &params);
    if(!recognitionLayer) recognitionLayer = new RecognitionLayer(params.size, &params);
    comparingLayer->recognitionLayer = recognitionLayer;
    recognitionLayer->comparingLayer = comparingLayer;

    for(int i = 0; i < inputData->size(); ++i)
    {
        comparingLayer->Input((*inputData)[i].first);
        qDebug() << endl;
    }

    QVector<QVariant> result;
    for(int i = 1; i < recognitionLayer->neurons.length(); ++i)
    {
        QList<int> list = QList<int>::fromVector(recognitionLayer->neurons[i]->outputWeights);
        result.append(QVariant::fromValue(list));
    }
    return result;
}

float ARTNetwork::RunTestSet()
{

}
