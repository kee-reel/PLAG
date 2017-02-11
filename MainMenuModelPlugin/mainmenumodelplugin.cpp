#include "mainmenumodelplugin.h"

MainMenuModelPlugin::MainMenuModelPlugin()
{
    activeView = NULL;
}

MainMenuModelPlugin::~MainMenuModelPlugin()
{

}

void MainMenuModelPlugin::AddChildPlugin(IPluginModel *plugin, MetaInfo *meta)
{
    childPlugins.insert(plugin, meta);
}

void MainMenuModelPlugin::SetDBTool(QObject *DBTool)
{
    this->DBTool = qobject_cast<ITaskDBToolPlugin*>(DBTool);
    if(!this->DBTool)
    {
        qDebug() << DBTool->objectName() << "is not ITaskDBToolPlugin.";
        return;
    }
    qDebug() << "ITaskDBToolPlugin succesfully set.";
}

void MainMenuModelPlugin::AddView(IPluginView *plugin, MetaInfo *meta)
{
    IPluginView* view = plugin;
    viewPlugins.insert(view, meta);
    view->SetModel(qobject_cast<QObject*>(this));
    qDebug() << "IPluginView succesfully set.";
}

bool MainMenuModelPlugin::Open(QWidget *parent)
{
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
    DBTool->CreateNewTask();
    return activeView->Open(this->parent);
}

bool MainMenuModelPlugin::Close()
{
    if(activeView != NULL)
        return activeView->Close();
    else
        return true;
}

QString MainMenuModelPlugin::GetError()
{

}

QList<MetaInfo*> MainMenuModelPlugin::GetChildPlugins()
{
    QList<MetaInfo*> tasks = childPlugins.values();
    return tasks;
}

void MainMenuModelPlugin::RunPlugin(int pluginId)
{
    QList<IPluginModel*> plugins = childPlugins.keys();
    if(plugins.count() > pluginId)
        plugins[pluginId]->Open(parent);
}
