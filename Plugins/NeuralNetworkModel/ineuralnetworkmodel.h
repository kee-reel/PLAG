#ifndef INEURALNETWORKMODEL_H
#define INEURALNETWORKMODEL_H

#include "../MainMenuModelPlugin/interfaces.h"
template <class A, class B>
class QPair;
template <class A>
class QVector;

typedef QPair<QVector<float>, QVector<float>> InputSampleF;
typedef QPair<QVector<int>, QVector<int>> InputSampleI;

//! \defgroup NeuralNetworkModel
//!     \ingroup MainMenuPlugin_rel_m
//! \defgroup NeuralNetworkModel_int Interfaces
//!     \ingroup NeuralNetworkModel
//! \defgroup NeuralNetworkModel_imp Implementation
//!     \ingroup NeuralNetworkModel

//! \addtogroup NeuralNetworkModel_int
//! \{
class INeuralNetworkModel : public IModelPlugin
{
public:
    class INeuralNetwork{
    public:
        virtual ~INeuralNetwork(){}
        virtual bool SetNetworkParams(QJsonObject params) = 0;

        virtual void SetupSamplesF(QJsonObject parameters, QVector<InputSampleF> *samples) = 0;
        virtual void SetupSamplesI(QJsonObject parameters, QVector<InputSampleI> *samples) = 0;

        virtual bool AddLayer(QJsonObject layerParams) = 0;
        virtual void ResetLayers() = 0;

        virtual float RunTrainSet() = 0;
        virtual QVector<QVariant> RunTrainingAndGetResult() = 0;
        virtual float RunTestSet() = 0;
    };

    // { "Type": <NetworkType>, <Varying for every network> }
    virtual INeuralNetwork *SetupNetwork(QJsonObject networkParams) = 0;

};
Q_DECLARE_INTERFACE(INeuralNetworkModel, "INeuralNetworkModel v0.1")
//! \}
#endif // IEMPTYPLUGINMODEL_H
