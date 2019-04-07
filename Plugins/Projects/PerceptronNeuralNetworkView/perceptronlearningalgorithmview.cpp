#include "perceptronlearningalgorithmview.h"
#include "ui_form.h"

PerceptronLearningAlgorithmView::PerceptronLearningAlgorithmView() :
    PluginBase()
{
    model = nullptr;
    network = nullptr;

    ui->listView->setModel(&itemModel);
    ui->listViewImages->setModel(&trainImagesModel);
    ui->listViewImages_2->setModel(&testImagesModel);
    ui->tabWidget->setTabEnabled(0, false);

    ui->customPlot->clearGraphs();
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    ui->customPlot->yAxis->setRange(0, 1);
    ui->customPlot->addGraph();
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(QColor(28, 156, 255)));
    ui->customPlot->graph(1)->setPen(QPen(QColor(226, 6, 25)));

    connect(ui->buttonRunTrain, SIGNAL(clicked()), this, SLOT(on_buttonRunTrain_clicked()));
    connect(ui->buttonClose, SIGNAL(clicked()), this, SLOT(on_buttonClose_clicked()));
    connect(ui->buttonAdd, SIGNAL(clicked()), this, SLOT(on_buttonAdd_clicked()));
    connect(ui->buttonRemove, SIGNAL(clicked()), this, SLOT(on_buttonRemove_clicked()));
    connect(ui->listView, SIGNAL(clicked(QModelIndex)), this, SLOT(on_listView_clicked(const QModelIndex &)));
    connect(ui->spinSize, SIGNAL(valueChanged(int)), this, SLOT(on_spinSize_valueChanged(int)));
    connect(ui->spinLearnSpeed, SIGNAL(valueChanged(double)), this, SLOT(on_spinLearnSpeed_valueChanged(double)));
    connect(ui->spinMoment, SIGNAL(valueChanged(double)), this, SLOT(on_spinMoment_valueChanged(double)));
    connect(ui->spinFuncIndent, SIGNAL(valueChanged(double)), this, SLOT(on_spinFuncIndent_valueChanged(double)));
    connect(ui->spinBias, SIGNAL(valueChanged(double)), this, SLOT(on_spinBias_valueChanged(double)));
    connect(ui->buttonLoadImage, SIGNAL(clicked()), this, SLOT(on_buttonLoadImage_clicked()));
    connect(ui->buttonRemoveImages, SIGNAL(clicked()), this, SLOT(on_buttonRemoveImages_clicked()));
    connect(ui->buttonLoadImage_2, SIGNAL(clicked()), this, SLOT(on_buttonLoadImage_2_clicked()));
    connect(ui->buttonRemoveImages_2, SIGNAL(clicked()), this, SLOT(on_buttonRemoveImages_2_clicked()));
    connect(ui->spinEpoch, SIGNAL(editingFinished()), this, SLOT(on_spinEpoch_editingFinished()));
    connect(ui->spinErrorThreshold, SIGNAL(editingFinished()), this, SLOT(on_spinErrorThreshold_editingFinished()));
    connect(ui->spinMinWeight, SIGNAL(editingFinished()), this, SLOT(on_spinMinWeight_editingFinished()));
    connect(ui->spinMaxWeight, SIGNAL(editingFinished()), this, SLOT(on_spinMaxWeight_editingFinished()));
    connect(ui->spinTestErrorThreshold, SIGNAL(editingFinished()), this, SLOT(on_spinTestErrorThreshold_editingFinished()));
    connect(ui->buttonResumeTraining, SIGNAL(clicked()), this, SLOT(on_buttonResumeTraining_clicked()));
}

PerceptronLearningAlgorithmView::~PerceptronLearningAlgorithmView()
{

}

void PerceptronLearningAlgorithmView::onAllReferencesSet()
{
    for(auto iter = m_referencesMap.begin(); iter != m_referencesMap.end(); ++iter)
    {
        auto&& interfaceName = iter.key();
        auto&& plugin = iter.value();
        if(!QString::compare(interfaceName, "IMachineLearningManager", Qt::CaseInsensitive))
        {
            model = castPluginToInterface<IMachineLearningManager>(plugin);
        }
    }
    PluginBase::onAllReferencesSet();
}

void PerceptronLearningAlgorithmView::onAllReferencesReady()
{
    isStatsChanged = true;
//    iLearningAlgorithm::ILearningAlgorithm *netw = model->SetupNetwork(QJsonObject{
//                            {"Type", "ART"},
//                            {"size", 14},
//                            {"L", 2},
//                            {"similarity", 0.9}
//                        });

//    QVector<InputSampleI> samples;
//    InputSampleI buf;
//    QVector<int> input1{1,0,0,1,1,1,
//                        1,1,1,0,0,0,
//                            1,0};
//    buf.first = input1;
//    samples.append(buf);

//    QVector<int> input2{1,1,0,0,0,0,
//                        0,0,1,1,1,1,
//                            0,0};
//    buf.first = input2;
//    samples.append(buf);
//    QVector<int> input3{0,0,1,1,0,0,
//                        0,1,0,0,1,0,
//                            1,1};
//    buf.first = input3;
//    samples.append(buf);
//    QVector<int> input4{1,1,0,0,1,0,
//                        0,0,1,1,1,1,
//                            0,0};
//    buf.first = input4;
//    samples.append(buf);
//    QVector<int> input5{1,0,0,0,1,1,
//                        1,1,1,0,0,0,
//                            1,0};
//    buf.first = input5;
//    samples.append(buf);

//    netw->SetupSamplesI(QJsonObject(), &samples);
//    QVector<QVariant> result = netw->RunTrainingAndGetResult();
//    for(int i = 0; i < result.length(); ++i)
//        qDebug() << result[i].value<QList<int>>();

//    iLearningAlgorithm::ILearningAlgorithm *netw = model->SetupNetwork(QJsonObject{
//                                {"Type", "GeneticAlgorithm"},
//                                {"fitnessThreshold", 0.99},
//                                {"iterations", 150},
//                                {"populationSize", 5},
//                                {"geneCapacity", 100},
//                                {"targetResult", 40.},
//                            });
//    netw->SetupSamplesF(QJsonObject{
//                           {"Func", "2*a + 4*b"}
//                       }, NULL);
//    netw->RunTrainingAndGetResult();

    PluginBase::onAllReferencesReady();
}
void PerceptronLearningAlgorithmView::MarkNetworkStatsToUpdate()
{
    isStatsChanged = true;
    ui->buttonResumeTraining->setEnabled(false);
}

bool PerceptronLearningAlgorithmView::UpdateNetworkStats()
{
    if(layersList.count() < 2 || !trainImages.length())
        return false;
    int width = trainImages.first().width();
    int height = trainImages.first().height();
    layersList.first().size = width * height;
    layersList.last().size = trainImages.count();
    ui->checkTrain->setEnabled(false);
    ui->checkTest->setEnabled(false);

    if(!network)
        network = model->SetupNetwork(ConvertNetworkParams());
    else
    {
        network->SetNetworkParams(ConvertNetworkParams());
        network->ResetLayers();
    }

    network->AddLayer(ConvertLayerParams(Input, layersList.first()));
    for(int i = 1; i < layersList.count()-1; ++i)
        network->AddLayer(ConvertLayerParams(Hidden, layersList[i]));
    network->AddLayer(ConvertLayerParams(Output, layersList.last()));

    trainingSamples.clear();
    testSamples.clear();

    InputSampleF buf;
    buf.first.resize(layersList.first().size);
    buf.second.resize(trainImages.count());
    for(int i = 0; i < trainImages.count(); ++i)
    {
        for(int h = 0; h < height; ++h)
            for(int w = 0; w < width; ++w)
                buf.first[h*width + w] = qRed(trainImages[i].pixel(w, h))/255.;
        for(int j = 0; j < trainImages.count(); ++j)
            buf.second[j] = 0;
        buf.second[i] = 1;
        trainingSamples.append(buf);
    }
    network->SetupSamplesF(QJsonObject{ {"Type", "Train"} }, &trainingSamples);

    for(int i = 0; i < testImages.count(); ++i)
    {
        for(int h = 0; h < height; ++h)
            for(int w = 0; w < width; ++w)
                buf.first[h*width + w] = qRed(testImages[i].pixel(w, h))/255.;
        for(int j = 0; j < testImages.count(); ++j)
            buf.second[j] = 0;
        buf.second[i] = 1;
        testSamples.append(buf);
    }
    network->SetupSamplesF(QJsonObject{ {"Type", "Test"} }, &testSamples);

    isStatsChanged = false;
    return true;
}

void PerceptronLearningAlgorithmView::UpdateLayerStatsGUI()
{
    QModelIndex index = ui->listView->selectionModel()->currentIndex();
    if(!index.isValid())
    {
        ui->tabWidget->setTabEnabled(0, false);
        return;
    }

    ui->tabWidget->setTabEnabled(0, true);
    LayerParams params = layersList[index.row()];
    ui->spinSize->setValue(params.size);
    ui->spinLearnSpeed->setValue(params.LearnSpeed);
    ui->spinMoment->setValue(params.Moment);
    ui->spinFuncIndent->setValue(params.FuncIndent);
    ui->spinBias->setValue(params.Bias);
    MarkNetworkStatsToUpdate();
}

void PerceptronLearningAlgorithmView::MakePlot(int graph, QVector<double> &x, QVector<double> &y)
{
    ui->customPlot->graph(graph)->setData(x, y);
}

void PerceptronLearningAlgorithmView::ReplotPlot()
{
    xValues.append(epoch);
    MakePlot(0, xValues, trainErrorVector);
    MakePlot(1, xValues, testErrorVector);
    ui->customPlot->replot();
    ui->customPlot->xAxis->setRange(0, epoch);
    ui->labelEpoch->        setText(QString::number(epoch));
    ui->labelTrainError->   setText(QString::number(trainErrorVector.last(), 'g', 3));
    ui->labelTestError->    setText(QString::number(testErrorVector.last(), 'g', 3));
}

QJsonObject PerceptronLearningAlgorithmView::ConvertNetworkParams()
{
    QJsonObject networkStats{
        {"Type",                "Perceptron"},
        {"trainErrorThreshold", ui->spinErrorThreshold->value()},
        {"testErrorThreshold",  ui->spinTestErrorThreshold->value()},
        {"minWeight",           ui->spinMinWeight->value()},
        {"maxWeight",           ui->spinMaxWeight->value()},
        {"maxEpoch",            ui->spinEpoch->value()}
    };
    return networkStats;
}

QJsonObject PerceptronLearningAlgorithmView::ConvertLayerParams(LayerType type, LayerParams &params)
{
    QString typeStr;
    switch (type) {
    case Input:
        typeStr = "Input";
        break;
    case Hidden:
        typeStr = "Hidden";
        break;
    case Output:
        typeStr = "Output";
        break;
    default:
        return QJsonObject();
        break;
    }
    QJsonObject layerStats{
        {"Type",                typeStr},
        {"Bias",                params.Bias},
        {"FuncIndent",          params.FuncIndent},
        {"LearnSpeed",          params.LearnSpeed},
        {"Moment",              params.Moment},
        {"size",                params.size}
    };
    return layerStats;
}

void PerceptronLearningAlgorithmView::on_buttonRunTrain_clicked()
{
    if(!UpdateNetworkStats())
        return;
    ui->checkTrain->setChecked(false);
    ui->checkTest->setChecked(false);
    ui->buttonResumeTraining->setEnabled(true);

    epoch = 0;
    int maxEpoch = ui->spinEpoch->value();
    RunTrainFromEpoch(maxEpoch);
}

void PerceptronLearningAlgorithmView::on_buttonResumeTraining_clicked()
{
    ui->checkTrain->setChecked(false);
    ui->checkTest->setChecked(false);

    int maxEpoch = epoch + ui->spinEpoch->value();
    RunTrainFromEpoch(maxEpoch);
}

void PerceptronLearningAlgorithmView::RunTrainFromEpoch(int maxEpoch)
{
    float trainThreshold = ui->spinErrorThreshold->value();
    float testThreshold = ui->spinTestErrorThreshold->value();
    bool trainSuccess;
    bool testSuccess;
    for(; epoch < maxEpoch; ++epoch)
    {
        trainErrorVector.append(network->RunTrainSet());
        testErrorVector.append(network->RunTestSet());
        ReplotPlot();
        trainSuccess = trainErrorVector.last() < trainThreshold;
        testSuccess = testErrorVector.last() < testThreshold;
        ui->checkTrain->setChecked(trainSuccess);
        ui->checkTest->setChecked(testSuccess);
        if(trainSuccess && testSuccess)
            return;
        QApplication::processEvents();
    }
}



void PerceptronLearningAlgorithmView::on_buttonClose_clicked()
{
    emit onClose(this);
}

void PerceptronLearningAlgorithmView::on_buttonAdd_clicked()
{
    LayerParams newLayer = {1, 0.7, 0.5, 2, 0};
    layersList.append(newLayer);
    QStandardItem *item = new QStandardItem(QString::number(layersList.count()));
    QBrush brush = QBrush(QColor(100+qrand()%20, 100+qrand()%50, 130+qrand()%120));
    item->setBackground(brush);
    itemModel.appendRow(item);
    UpdateLayerStatsGUI();
}

void PerceptronLearningAlgorithmView::on_buttonRemove_clicked()
{
    QModelIndex index = ui->listView->selectionModel()->currentIndex();
    if(index.isValid())
    {
        itemModel.removeRow(index.row());
        layersList.removeAt(index.row());
    }
    UpdateLayerStatsGUI();
}

void PerceptronLearningAlgorithmView::on_listView_clicked(const QModelIndex &index)
{
    UpdateLayerStatsGUI();
}

void PerceptronLearningAlgorithmView::on_spinSize_valueChanged(int arg1)
{
    QModelIndex index = ui->listView->selectionModel()->currentIndex();
    if(!index.isValid())
        return;
    layersList[index.row()].size = arg1;
    MarkNetworkStatsToUpdate();
}

void PerceptronLearningAlgorithmView::on_spinLearnSpeed_valueChanged(double arg1)
{
    QModelIndex index = ui->listView->selectionModel()->currentIndex();
    if(!index.isValid())
        return;
    layersList[index.row()].LearnSpeed = arg1;
    MarkNetworkStatsToUpdate();
}

void PerceptronLearningAlgorithmView::on_spinMoment_valueChanged(double arg1)
{
    QModelIndex index = ui->listView->selectionModel()->currentIndex();
    if(!index.isValid())
        return;
    layersList[index.row()].Moment = arg1;
    MarkNetworkStatsToUpdate();
}

void PerceptronLearningAlgorithmView::on_spinFuncIndent_valueChanged(double arg1)
{
    QModelIndex index = ui->listView->selectionModel()->currentIndex();
    if(!index.isValid())
        return;
    layersList[index.row()].FuncIndent = arg1;
    MarkNetworkStatsToUpdate();
}

void PerceptronLearningAlgorithmView::on_spinBias_valueChanged(double arg1)
{
    QModelIndex index = ui->listView->selectionModel()->currentIndex();
    if(!index.isValid())
        return;
    layersList[index.row()].Bias = arg1;
    MarkNetworkStatsToUpdate();
}

void PerceptronLearningAlgorithmView::on_buttonLoadImage_clicked()
{
    QFileDialog dialog(
                this,
                "Add Image",
                "/home",
                "Image Files (*.png *.jpg *.bmp)");
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);
    QStringList fileNames;
    if(dialog.exec())
    {
        fileNames = dialog.selectedFiles();
        for(int i = 0; i < fileNames.length(); ++i)
        {
            QImage image = QImage(fileNames[i]);
            if(image.isNull()) return;
            trainImages.append(image);
            QStandardItem *item = new QStandardItem(QIcon(QPixmap::fromImage(image)), fileNames[i]);
            trainImagesModel.appendRow(item);
        }
    }
}

void PerceptronLearningAlgorithmView::on_buttonRemoveImages_clicked()
{
    trainImages.clear();
    trainImagesModel.clear();
}

void PerceptronLearningAlgorithmView::on_buttonLoadImage_2_clicked()
{
    QFileDialog dialog(
                this,
                "Add Image",
                "/home",
                "Image Files (*.png *.jpg *.bmp)");
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);
    QStringList fileNames;
    if(dialog.exec())
    {
        fileNames = dialog.selectedFiles();
        for(int i = 0; i < fileNames.length(); ++i)
        {
            QImage image = QImage(fileNames[i]);
            if(image.isNull()) return;
            testImages.append(image);
            QStandardItem *item = new QStandardItem(QIcon(QPixmap::fromImage(image)), fileNames[i]);
            testImagesModel.appendRow(item);
        }
    }
}

void PerceptronLearningAlgorithmView::on_buttonRemoveImages_2_clicked()
{
    testImages.clear();
    testImagesModel.clear();
}

void PerceptronLearningAlgorithmView::on_spinEpoch_editingFinished()
{
    MarkNetworkStatsToUpdate();
}

void PerceptronLearningAlgorithmView::on_spinErrorThreshold_editingFinished()
{
    MarkNetworkStatsToUpdate();
}

void PerceptronLearningAlgorithmView::on_spinMinWeight_editingFinished()
{
    MarkNetworkStatsToUpdate();
}

void PerceptronLearningAlgorithmView::on_spinMaxWeight_editingFinished()
{
    MarkNetworkStatsToUpdate();
}

void PerceptronLearningAlgorithmView::on_spinTestErrorThreshold_editingFinished()
{
    MarkNetworkStatsToUpdate();
}

//void PerceptronNetworkViewPlugin::OnAllSetup()
//{

//}

//QString PerceptronNetworkViewPlugin::GetLastError()
//{

//}

//void PerceptronNetworkViewPlugin::AddModel(QObject *model)
//{
//    myModel = qobject_cast<ILearningAlgorithm*>(model);
//    if(!myModel)
//    {
//        qDebug() << model->objectName() << "is not ITaskListModel.";
//        return;
//    }
//    qDebug() << "ITaskListModel succesfully set.";
//}

//bool PerceptronNetworkViewPlugin::Open(QWidget *parent)
//{
//    qDebug() << "View OPEN" << parent;
//    if(!myModel)
//    {
//        qDebug() << "Model isn't set!";
//        return false;
//    }
//    connect(mainForm, SIGNAL(onClose()), this, SLOT(Close()));
//    parent->layout()->addWidget(mainForm);
//    mainForm->setParent(parent);
//    mainForm->show();
//    mainForm->SetModel(myModel);

//    return true;
//}

//bool PerceptronNetworkViewPlugin::Close()
//{
//    disconnect(mainForm, SIGNAL(onClose()), this, SLOT(Close()));
//    mainForm->hide();
//    myModel->CloseFromView(this);
//    return true;
//}
