#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <QJsonObject>
#include <QObject>
#include <QVector>
#include <QList>
#include <QDebug>
#include <QPair>

#include "ineuralnetworkmodel.h"
#include "neurallayer.h"

class Perceptron : public QObject, INeuralNetworkModel::INeuralNetwork
{
    Q_OBJECT
    struct NetworkParams{
        int maxEpoch;
        float trainErrorThreshold;
        float testErrorThreshold;
        float minWeight;
        float maxWeight;
    };

    struct LayerParams{
        int size;
        float LearnSpeed;
        float Moment;
        float FuncIndent;
        float Bias;
    };

    enum LayerType{
        Input,
        Hidden,
        Output
    };

public:
    Perceptron(Perceptron::NetworkParams params);
    static Perceptron *Make(QJsonObject *paramsObj) const;
    ~Perceptron();
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
    NetworkParams networkParams;

private slots:
    float RunTrainSet(INeuralNetworkModel::TrainSample &trainSet);
    float RunTestSet(INeuralNetworkModel::TrainSample &testSet);

    // INeuralNetwork interface
private:
    void SetupTrainingSamples(QVector<INeuralNetworkModel::TrainSample> *samples) override;
    void SetupTestSamples(QVector<INeuralNetworkModel::TrainSample> *samples) override;
    void AddLayer(QJsonObject *layerParams) override;
};

#endif // NEURALNETWORK_H
