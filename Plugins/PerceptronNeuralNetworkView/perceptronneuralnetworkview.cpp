#include "perceptronneuralnetworkview.h"

PerceptronNetworkViewPlugin::PerceptronNetworkViewPlugin()
{
    mainForm = new MainForm;
    mainForm->setVisible(false);
    myModel = NULL;
}

PerceptronNetworkViewPlugin::~PerceptronNetworkViewPlugin()
{

}

void PerceptronNetworkViewPlugin::OnAllSetup()
{

}

QString PerceptronNetworkViewPlugin::GetLastError()
{

}

void PerceptronNetworkViewPlugin::SetModel(QObject *model)
{
    myModel = qobject_cast<INeuralNetworkModel*>(model);
    if(!myModel)
    {
        qDebug() << model->objectName() << "is not ITaskListModel.";
        return;
    }
    qDebug() << "ITaskListModel succesfully set.";
}

bool PerceptronNetworkViewPlugin::Open(QWidget *parent)
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

bool PerceptronNetworkViewPlugin::Close()
{
    disconnect(mainForm, SIGNAL(onClose()), this, SLOT(Close()));
    mainForm->hide();
    myModel->CloseFromView(this);
    return true;
}
