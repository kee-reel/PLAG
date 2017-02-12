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
    qDebug() << "NEW=====================" << meta->Name;
    childPlugins.insert(plugin, meta);
}

void MainMenuModelPlugin::SetDBTool(QObject *DBTool)
{
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
    qDebug() << "MainMenuModel runs";
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
    {
        qDebug() << "Open plugin" << childPlugins[plugins[pluginId]]->Name;
        plugins[pluginId]->Open(parent);
    }
}
