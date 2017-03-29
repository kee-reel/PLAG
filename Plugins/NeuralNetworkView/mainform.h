#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include <QDebug>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QPixmap>
#include <QIcon>
#include <QRgb>

#include "../NeuralNetworkModel/ineuralnetworkmodel.h"

namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT

public:
    QVector<INeuralNetworkModel::TrainSample> *trainingSamples;
    QVector<INeuralNetworkModel::TrainSample> *testSamples;
    QStandardItemModel *itemModel;
    QStandardItemModel *imagesModel;

    explicit MainForm(QWidget *parent = 0);
    ~MainForm();
    void SetModel(INeuralNetworkModel *Model);
signals:
    void onClose();
private slots:
    void MarkNetworkStatsToUpdate();
    void on_buttonRunTrain_clicked();
    void on_buttonRunTest_clicked();
    void on_buttonClose_clicked();
    void on_buttonAdd_clicked();
    void on_buttonRemove_clicked();

    void on_listView_clicked(const QModelIndex &index);
    void on_spinEpoch_valueChanged(int arg1);
    void on_spinErrorThreshold_valueChanged(double arg1);
    void on_spinSize_valueChanged(int arg1);
    void on_spinLearnSpeed_valueChanged(double arg1);
    void on_spinMoment_valueChanged(double arg1);
    void on_spinFuncIndent_valueChanged(double arg1);
    void on_spinBias_valueChanged(double arg1);

    void on_buttonLoadImage_clicked();
    void on_buttonRemoveImages_clicked();

private:
    Ui::MainForm *ui;
    INeuralNetworkModel *model;
    QModelIndex currentIndex;
    bool isStatsChanged;
    QList<INeuralNetworkModel::LayerParams> layersList;
    QList<QImage> inputImages;
    QVector<double> errorVector;

    bool UpdateNetworkStats();
    void UpdateLayerStatsGUI();
    void MakePlot(QVector<double> &x, QVector<double> &y);
};

#endif // MAINFORM_H
