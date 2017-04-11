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
    explicit NeuralNetwork(Perceptron::NetworkParams params);
    ~NeuralNetwork();
    void AddLayer(Perceptron::LayerType type, Perceptron::LayerParams params);
    void ResetLayers();
    float RunTraining();
    float RunTest();

    QVector<INeuralNetworkModel::TrainSample> *trainingSamples;
    QVector<INeuralNetworkModel::TrainSample> *testSamples;

private:
    InputNeuralLayer *inputLayer;
    QList<NeuralLayer*> layers;
    OutputNeuralLayer *outputLayer;

    float resultError;
    Perceptron::NetworkParams networkParams;

private slots:
    float RunTrainSet(INeuralNetworkModel::TrainSample &trainSet);
    float RunTestSet(INeuralNetworkModel::TrainSample &testSet);
};

#endif // NEURALNETWORK_H
