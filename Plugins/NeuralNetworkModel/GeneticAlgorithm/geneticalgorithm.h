#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <QVector>
#include <QVariant>
#include <QJsonObject>
#include <QDebug>
#include <QScriptEngine>
#include <QRegExp>

#include "ineuralnetworkmodel.h"
#include "parameters.h"
#include "GeneticAlgorithm/chromosome.h"

class GeneticAlgorithm : public INeuralNetworkModel::INeuralNetwork
{
    typedef GeneticAlgorithmParams::Parameters Parameters;
public:
    QVector<Chromosome*> chromosomes;
    Parameters params;
    QStringList variables;
    QScriptEngine myEngine;
    QScriptValue func;
    QScriptValueList funcAgs;

    GeneticAlgorithm();
    static GeneticAlgorithm *Make(QJsonObject &paramsObj);
    float EvaluateFitness(Chromosome *chromosome);

    // INeuralNetwork interface
public:
    bool SetNetworkParams(QJsonObject paramsObj) override;
    void SetupSamplesF(QJsonObject parameters, QVector<InputSampleF> *samples) override;
    void SetupSamplesI(QJsonObject parameters, QVector<InputSampleI> *samples) override;

    bool AddLayer(QJsonObject layerParams) override;
    void ResetLayers() override;

    float RunTrainSet() override;
    QVector<QVariant> RunTrainingAndGetResult() override;
    float RunTestSet() override;
};

#endif // GENETICALGORITHM_H