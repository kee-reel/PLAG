#ifndef EMPTYMODULE_H
#define EMPTYMODULE_H

#include <QtCore>
#include <QLayout>
#include <QObject>
#include <QDebug>
#include <QStandardItemModel>

#include "../../Common/plugin_base.h"

#include "../../Interfaces/imachinelearningmanager.h"

//! \addtogroup MachineLearningManager_dep
//!  \{
//!
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

class PerceptronLearningAlgorithmView : public PluginBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IPlugin)

public:
    PerceptronLearningAlgorithmView();
    virtual ~PerceptronLearningAlgorithmView() override;

    // PluginBase interface
public:
    virtual void onAllReferencesSet() override;
    virtual void onAllReferencesReady() override;

public:
    QVector<InputSampleF> trainingSamples;
    QVector<InputSampleF> testSamples;
    QStandardItemModel itemModel;
    QStandardItemModel trainImagesModel;
    QStandardItemModel testImagesModel;

private slots:
    void MarkNetworkStatsToUpdate();
    void on_buttonRunTrain_clicked();
    void on_buttonClose_clicked();
    void on_buttonAdd_clicked();
    void on_buttonRemove_clicked();

    void on_listView_clicked(const QModelIndex &index);
    void on_spinSize_valueChanged(int arg1);
    void on_spinLearnSpeed_valueChanged(double arg1);
    void on_spinMoment_valueChanged(double arg1);
    void on_spinFuncIndent_valueChanged(double arg1);
    void on_spinBias_valueChanged(double arg1);

    void on_buttonLoadImage_clicked();
    void on_buttonRemoveImages_clicked();
    void on_buttonLoadImage_2_clicked();
    void on_buttonRemoveImages_2_clicked();
    void on_spinEpoch_editingFinished();
    void on_spinErrorThreshold_editingFinished();
    void on_spinMinWeight_editingFinished();
    void on_spinMaxWeight_editingFinished();
    void on_spinTestErrorThreshold_editingFinished();
    void on_buttonResumeTraining_clicked();

private:
    IMachineLearningManager *model;
    IMachineLearningManager::ILearningAlgorithm *network;
    QModelIndex currentIndex;
    bool isStatsChanged;
    QList<LayerParams> layersList;
    QList<QImage> trainImages;
    QList<QImage> testImages;
    QVector<double> trainErrorVector;
    QVector<double> testErrorVector;
    int epoch;
    QVector<double> xValues;

    void RunTrainFromEpoch(int maxEpoch);
    bool UpdateNetworkStats();
    void UpdateLayerStatsGUI();
    void MakePlot(int graph, QVector<double> &x, QVector<double> &y);
    void ReplotPlot();
    QJsonObject ConvertNetworkParams();
    QJsonObject ConvertLayerParams(LayerType type, LayerParams &params);
};

#endif // EMPTYMODULE_H
