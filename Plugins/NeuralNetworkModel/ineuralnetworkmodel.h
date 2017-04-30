#ifndef IEMPTYPLUGINMODEL_H
#define IEMPTYPLUGINMODEL_H

#include "../MainMenuModelPlugin/interfaces.h"
template <class A, class B>
class QPair;
template <class A>
class QVector;
class QJsonObject;

typedef QPair<QVector<float>, QVector<float>> TrainSample;

class INeuralNetworkModel : public IModelPlugin
{
public:
    class INeuralNetwork{
        virtual void SetupTrainingSamples(QVector<TrainSample> *samples) = 0;
        virtual void SetupTestSamples(QVector<TrainSample> *samples) = 0;

        virtual void AddLayer(QJsonObject *layerParams) = 0;
        virtual void ResetLayers() = 0;

        virtual float RunTraining() = 0;
        virtual float RunTest() = 0;
    };

    // { "Type": <NetworkType>, <Varying for every network> }
    virtual INeuralNetwork *SetupNetwork(QJsonObject *networkParams) = 0;

};
Q_DECLARE_INTERFACE(INeuralNetworkModel, "INeuralNetworkModel v0.1")

#endif // IEMPTYPLUGINMODEL_H
