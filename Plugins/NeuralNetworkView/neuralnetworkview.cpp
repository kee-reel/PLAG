#include "neuralnetworkview.h"

NeuralNetworkView::NeuralNetworkView()
{
    mainWindow = new MainWindow;
    mainWindow->setVisible(false);
    myModel = NULL;
}

NeuralNetworkView::~NeuralNetworkView()
{
}

void NeuralNetworkView::OnAllSetup()
{

}

QString NeuralNetworkView::GetLastError()
{

}

void NeuralNetworkView::SetModel(QObject *model)
{
    myModel = qobject_cast<INeuralNetworkModel*>(model);
    if(!myModel)
    {
        qDebug() << model->objectName() << "is not ITaskListModel.";
        return;
    }
    qDebug() << "ITaskListModel succesfully set.";
}

bool NeuralNetworkView::Open(int id, QWidget *parent)
{
    qDebug() << "View OPEN" << parent;
    if(!myModel)
    {
        qDebug() << "Model isn't set!";
        return false;
    }
    connect(mainWindow, SIGNAL(onClose()), this, SLOT(Close()));
    myId = id;
    parent->layout()->addWidget(mainWindow);
    mainWindow->setParent(parent);
    mainWindow->show();
    return true;
}

bool NeuralNetworkView::Close()
{
    disconnect(mainWindow, SIGNAL(onClose()), this, SLOT(Close()));
    mainWindow->hide();
    myModel->Close();
    return true;
}
