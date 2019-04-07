#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <QtCore>
#include <QVariant>
#include <QJsonObject>
#include <QDebug>
#include <QScriptEngine>
#include <QRegExp>
#include <limits>

#include "../../Interfaces/imachinelearningmanager.h"
#include "parameters.h"
#include "GeneticAlgorithm/chromosome.h"

class GeneticAlgorithm : public IMachineLearningManager::ILearningAlgorithm
{
    typedef Parameters::GeneticAlgorithmParams::Parameters Parameters;
public:
    QVector<Chromosome*> chromosomes;
    Parameters params;
    QVector<Chromosome*> breedChromosomes;
    QMap<float, Chromosome*> tournirTable;

    QStringList variables;
    QScriptEngine *myEngine;
    QScriptValue func;
    QScriptValueList funcAgs;
    float maxFitness = 0;

    GeneticAlgorithm();
    ~GeneticAlgorithm() override;
    static GeneticAlgorithm *Make(QJsonObject &paramsObj);
    float EvaluateFitness(Chromosome *chromosome);

    // ILearningAlgorithm interface
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
