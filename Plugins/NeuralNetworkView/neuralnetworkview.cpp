#include "neuralnetworkview.h"

NeuralNetworkView::NeuralNetworkView()
{
    mainForm = new MainForm;
    mainForm->setVisible(false);
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

bool NeuralNetworkView::Open(QWidget *parent)
{
    qDebug() << "View OPEN" << parent;
    if(!myModel)
    {
        qDebug() << "Model isn't set!";
        return false;
    }
    connect(mainForm, SIGNAL(onClose()), this, SLOT(Close()));
    parent->layout()->addWidget(mainForm);
    mainForm->setParent(parent);
    mainForm->show();
    mainForm->SetModel(myModel);

    return true;
}

bool NeuralNetworkView::Close()
{
    disconnect(mainForm, SIGNAL(onClose()), this, SLOT(Close()));
    mainForm->hide();
    myModel->CloseFromView(this);
    return true;
}
