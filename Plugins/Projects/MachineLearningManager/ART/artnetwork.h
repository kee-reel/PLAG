#ifndef ARTNETWORK_H
#define ARTNETWORK_H

#include <QVector>
#include <QList>
#include <QVariant>
#include <QJsonObject>

#include "../../Interfaces/imachinelearningmanager.h"
#include "ART/comparinglayer.h"
#include "ART/recognitionlayer.h"
#include "parameters.h"

class ARTNetwork : public IMachineLearningManager::ILearningAlgorithm
{
protected:
    typedef Parameters::ART::NetworkParams NetworkParams;
    ARTNetwork();
    ~ARTNetwork() override;

public:
    static ARTNetwork *Make(QJsonObject &paramsObj);

    // ILearningAlgorithm interface
public:
    bool SetNetworkParams(QJsonObject params) override;
    void SetupSamplesF(QJsonObject parameters, QVector<InputSampleF> *samples) override;
    void SetupSamplesI(QJsonObject parameters, QVector<InputSampleI> *samples) override;
    bool AddLayer(QJsonObject layerParams) override;
    void ResetLayers() override;
    float RunTrainSet() override;
    QVector<QVariant> RunTrainingAndGetResult() override;
    float RunTestSet() override;

private:
    NetworkParams params;
    ComparingLayer *comparingLayer;
    RecognitionLayer *recognitionLayer;
    QVector<InputSampleI> *inputData;
};

#endif // ARTNETWORK_H
