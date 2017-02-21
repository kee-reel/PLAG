#include "emptypluginmodel.h"

EmptyPluginModel::EmptyPluginModel()
{
    activeViewId = -1;
}

EmptyPluginModel::~EmptyPluginModel()
{
}

void EmptyPluginModel::AddChildPlugin(IPluginModel *plugin, MetaInfo *meta)
{
    qDebug() << "New child" << meta->Name;
    PluginInfo<IPluginModel> newPlugin = {plugin, meta};
    childModelPlugins.append(newPlugin);
}

void EmptyPluginModel::AddView(IPluginView *plugin, MetaInfo *meta)
{
    PluginInfo<IPluginView> newPlugin = {plugin, meta};
    viewPlugins.append(newPlugin);
    newPlugin.plugin->SetModel(qobject_cast<QObject*>(this));
    qDebug() << "IPluginView succesfully set.";
}

void EmptyPluginModel::SetDataManager(QObject *DBTool)
{
    qDebug() << "I dont need DBTool";
}

bool EmptyPluginModel::Open(IPluginModel* parent, QWidget* parentWidget, int id)
{
    qDebug() << "EmptyModel runs";
    if(viewPlugins.count() == 0){
        qDebug() << "I dont have any views!";
        return false;
    }

    myModelId = id;
    myParent = parent;
    myParentWidget = parentWidget;
    activeViewId = 0;

    if(!viewPlugins[activeViewId].plugin->Open(activeViewId, myParentWidget)){
        qDebug() << "Can't open first view!";
        return false;
    }

    return true;
}

/// Only view can call
bool EmptyPluginModel::Close()
{
    activeViewId = -1;
    myParent->ChildSelfClosed(myModelId);
    return true;
}

void EmptyPluginModel::ChildSelfClosed(int id)
{

}

QString EmptyPluginModel::GetError()
{

}

void EmptyPluginModel::TestFunc()
{
    qDebug() << "This is test function. If it prints everything OK c:";
}
