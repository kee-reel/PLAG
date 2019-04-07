#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <QJsonObject>
#include <QObject>
#include <QVector>
#include <QList>
#include <QDebug>
#include <QPair>

#include "../../Interfaces/imachinelearningmanager.h"
#include "Perceptron/neurallayer.h"

class Perceptron : public QObject, public IMachineLearningManager::ILearningAlgorithm
{
    Q_OBJECT
    typedef Parameters::Perceptron::NetworkParams NetworkParams;
    typedef Parameters::Perceptron::LayerParams LayerParams;
    typedef Parameters::Perceptron::LayerType LayerType;
public:
    Perceptron(NetworkParams params);
    static Perceptron *Make(QJsonObject &paramsObj);
    ~Perceptron() override;

    void SetupSamplesF(QJsonObject parameters, QVector<InputSampleF> *samples) override;
    void SetupSamplesI(QJsonObject parameters, QVector<InputSampleI> *samples) override;
    bool SetNetworkParams(QJsonObject params) override;
    bool AddLayer(QJsonObject layerParams) override;
    void ResetLayers() override;
    float RunTrainSet() override;
    float RunTestSet() override;

private:
    InputNeuralLayer *inputLayer;
    QList<NeuralLayer*> layers;
    OutputNeuralLayer *outputLayer;

    QVector<InputSampleF> *trainingSamples;
    QVector<InputSampleF> *testSamples;

    float resultError;
    NetworkParams networkParams;

private slots:
    float RunTrainSet(InputSampleF &trainSet);
    QVector<QVariant> RunTrainingAndGetResult();
    float RunTestSet(InputSampleF &testSet);
};

#endif // NEURALNETWORK_H
