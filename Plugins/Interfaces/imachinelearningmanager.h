#ifndef IMachineLearningManager_H
#define IMachineLearningManager_H

#include <QtCore>

template <class A, class B>
class QPair;
template <class A>
class QVector;

typedef QPair<QVector<float>, QVector<float>> InputSampleF;
typedef QPair<QVector<int>, QVector<int>> InputSampleI;

//!  \defgroup MachineLearningManager MachineLearningManager
//!      \ingroup Plugins
//! \defgroup MachineLearningManager_int Interfaces
//!     \ingroup MachineLearningManager
//! \defgroup MachineLearningManager_imp Implementation
//!     \ingroup MachineLearningManager
//!  \defgroup MachineLearningManager_dep Dependent plugins
//!      \ingroup MachineLearningManager

//! \addtogroup MachineLearningManager_int
//!  \{
class IMachineLearningManager
{
public:
    class ILearningAlgorithm{
    public:
        virtual ~ILearningAlgorithm(){}
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
    virtual ILearningAlgorithm *SetupNetwork(QJsonObject networkParams) = 0;

};
Q_DECLARE_INTERFACE(IMachineLearningManager, "IMachineLearningManager v0.1")
//!  \}
#endif // IEMPTYPLUGINMODEL_H
