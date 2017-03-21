#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <QObject>
#include <QVector>
#include <QList>
#include <QDebug>
#include <QPair>
#include "neurallayer.h"
#include "ineuralnetworkmodel.h"

class NeuralNetwork : public QObject
{
    Q_OBJECT
public:
    explicit NeuralNetwork(INeuralNetworkModel::NetworkParams params);
    ~NeuralNetwork();
    void AddInputLayer(INeuralNetworkModel::LayerParams params);
    void AddHiddenLayer(INeuralNetworkModel::LayerParams params);
    void AddOutputLayer(INeuralNetworkModel::LayerParams params);
    bool RunTraining();
    bool RunTest();

    QVector<INeuralNetworkModel::TrainSample> *trainingSamples;
    QVector<INeuralNetworkModel::TrainSample> *testSamples;

private:
    InputNeuralLayer *inputLayer;
    QList<NeuralLayer*> layers;
    OutputNeuralLayer *outputLayer;

    float resultError;
    float resultErrorThreshold;
    int maxEpoch;

private slots:
    float RunTrainSet(INeuralNetworkModel::TrainSample &trainSet);
    float RunTestSet(INeuralNetworkModel::TrainSample &testSet);
};

#endif // NEURALNETWORK_H
