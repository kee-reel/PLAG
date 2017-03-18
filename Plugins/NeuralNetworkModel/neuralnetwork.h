#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <QObject>
#include <QVector>
#include <QList>
#include <QDebug>
#include "neurallayer.h"

class NeuralNetwork : public QObject
{
    Q_OBJECT
public:
    explicit NeuralNetwork(int inputs);

private:
    InputNeuralLayer *inputLayer;
    QList<NeuralLayer*> hiddenLayers;
    OutputNeuralLayer *outputLayer;

    struct TrainingPair{
        QVector<float> inputs;
        QVector<float> outputs;
    };
    QVector<TrainingPair> trainingSamples;
    float resultError;
    float resultErrorThreshold;

    int maxEpoch;

private slots:
    void RunEpoch();
    void RunTrainSet(int trainSet);

};

#endif // NEURALNETWORK_H
