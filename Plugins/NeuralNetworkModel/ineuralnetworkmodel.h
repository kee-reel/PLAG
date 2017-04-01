#ifndef IEMPTYPLUGINMODEL_H
#define IEMPTYPLUGINMODEL_H

#include "../MainMenuModelPlugin/interfaces.h"
template <class A, class B>
class QPair;
template <class A>
class QVector;
class INeuralNetworkModel : public IModelPlugin
{
public:
    typedef QPair<QVector<float>, QVector<float>> TrainSample;

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

    virtual void SetupNetwork(NetworkParams params) = 0;
    virtual void AddLayer(LayerType type, LayerParams params) = 0;
    virtual void ResetLayers() = 0;

    virtual float RunTraining() = 0;
    virtual float RunTest() = 0;
    virtual void SetupTrainingSamples(QVector<TrainSample> *samples) = 0;
    virtual void SetupTestSamples(QVector<TrainSample> *samples) = 0;

};
Q_DECLARE_INTERFACE(INeuralNetworkModel, "INeuralNetworkModel v0.1")

#endif // IEMPTYPLUGINMODEL_H
