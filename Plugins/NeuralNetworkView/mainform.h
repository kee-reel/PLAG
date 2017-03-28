#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include <QDebug>
#include <QStandardItemModel>

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

private:
    Ui::MainForm *ui;
    INeuralNetworkModel *model;
    QModelIndex currentIndex;
    bool isStatsChanged;
    QList<INeuralNetworkModel::LayerParams> layersList;

    void UpdateNetworkStats();
};

#endif // MAINFORM_H
