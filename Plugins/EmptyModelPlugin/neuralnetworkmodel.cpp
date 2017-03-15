#include "neuralnetworkmodel.h"

NeuralNetworkModel::NeuralNetworkModel()
{
    tableName = "TaskTree";
    activeViewId = -1;
    dataManager = NULL;
}

NeuralNetworkModel::~NeuralNetworkModel()
{
}

void NeuralNetworkModel::OnAllSetup()
{

}

QString NeuralNetworkModel::GetLastError()
{

}

void NeuralNetworkModel::AddChildModel(IModelPlugin *model, MetaInfo *meta)
{
    qDebug() << "New child" << meta->Name;
    PluginInfo<IModelPlugin> newPlugin = {model, meta};
    childModelPlugins.append(newPlugin);
}

void NeuralNetworkModel::AddView(IViewPlugin *view, MetaInfo *meta)
{
    PluginInfo<IViewPlugin> newPlugin = {view, meta};
    viewPlugins.append(newPlugin);
    qDebug() << "IPluginView succesfully set.";
}

void NeuralNetworkModel::AddDataManager(QObject *dataManager)
{
    qDebug() <<  "is not IExtendableDataBaseManagerPlugin.";
    this->dataManager = qobject_cast<IExtendableDataBaseManagerPlugin*>(dataManager);
    if(!this->dataManager)
    {
        qDebug() << dataManager->objectName() << "is not IExtendableDataBaseManagerPlugin.";
        return;
    }
    qDebug() << "IExtendableDataBaseManagerPlugin succesfully set.";
}

bool NeuralNetworkModel::Open(IModelPlugin *parent, QWidget *parentWidget, int id)
{
    qDebug() << "TaskListModel runs";
    if(viewPlugins.count() == 0){
        qDebug() << "I dont have any views!";
        return false;
    }
    myModelId = id;
    myParent = parent;
    myParentWidget = parentWidget;
    activeViewId = 0;

    qDebug() << viewPlugins[activeViewId].meta->Name;
    qDebug() << viewPlugins[activeViewId].plugin->Close();
    if(!viewPlugins[activeViewId].plugin->Open(activeViewId, myParentWidget))
    {
        qDebug() << "Can't open first view!";
        return false;
    }

    return true;
}

bool NeuralNetworkModel::Close()
{
    if(activeViewId != -1)
    {
        if(!viewPlugins[activeViewId].plugin->Close())
        {
            qDebug() << "My view can't close!";
            return false;
        }
        else
        {
            activeViewId = -1;
            myParent->ChildSelfClosed(myModelId);
            return true;
        }
    }
    else
        return true;
}

void NeuralNetworkModel::ChildSelfClosed(int id)
{

}

void NeuralNetworkModel::TestFunc()
{

}
