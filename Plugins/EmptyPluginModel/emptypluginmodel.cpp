#include "emptypluginmodel.h"

EmptyPluginModel::EmptyPluginModel()
{
    activeView = NULL;
}

EmptyPluginModel::~EmptyPluginModel()
{
}

void EmptyPluginModel::AddChildPlugin(IPluginModel *plugin, MetaInfo *meta)
{
    qDebug() << "New child" << meta->Name;
    childPlugins.insert(plugin, meta);
}

void EmptyPluginModel::SetDBTool(QObject *DBTool)
{
    qDebug() << "I dont need DBTool";
}

QString EmptyPluginModel::GetError()
{

}

bool EmptyPluginModel::Open(QWidget *parent)
{
    qDebug() << "EmptyModel runs";
    this->parent = parent;
    if(viewPlugins.count() == 0)
    {
        qDebug() << "I dont have any views!";
        return false;
    }
    if(activeView != NULL)
    {
        bool isClosed = activeView->Close();
        if(!isClosed) return false;
    }
    activeView = viewPlugins.begin().key();
    return activeView->Open(this->parent);
}

bool EmptyPluginModel::Close()
{
    if(activeView != NULL)
        return activeView->Close();
    else
        return true;
}

void EmptyPluginModel::AddView(IPluginView *plugin, MetaInfo *meta)
{
    IPluginView* view = plugin;
    viewPlugins.insert(view, meta);
    view->SetModel(qobject_cast<QObject*>(this));
    qDebug() << "IPluginView succesfully set.";
}

void EmptyPluginModel::TestFunc()
{
    qDebug() << "This is test function. If it prints everything OK c:";
}
