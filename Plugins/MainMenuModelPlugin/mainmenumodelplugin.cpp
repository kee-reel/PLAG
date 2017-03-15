#include "mainmenumodelplugin.h"

MainMenuModelPlugin::MainMenuModelPlugin()
{
    activeViewId = -1;

}

MainMenuModelPlugin::~MainMenuModelPlugin()
{

}

void MainMenuModelPlugin::AddPlugin(QObject *instance, QJsonObject *meta)
{
    pluginLinker.AddNewPlugin(instance, meta);
}

void MainMenuModelPlugin::Open(QWidget *parentWidget)
{
    this->parentWidget = parentWidget;
    pluginLinker.SetupLinks();
    Open(NULL, parentWidget, 0);
}

void MainMenuModelPlugin::OnAllSetup()
{

}

QString MainMenuModelPlugin::GetLastError()
{
    return QString();
}

void MainMenuModelPlugin::AddChildModel(IModelPlugin *model, MetaInfo *meta)
{
    PluginInfo<IModelPlugin> info = {model, meta};
    childModels.append(info);
}

void MainMenuModelPlugin::AddView(IViewPlugin *view, MetaInfo *meta)
{
    PluginInfo<IViewPlugin> info = {view, meta};
    views.append(info);
}

void MainMenuModelPlugin::AddDataManager(QObject *dataManager)
{

}

bool MainMenuModelPlugin::Open(IModelPlugin *parent, QWidget *parentWidget, int id)
{
    qDebug() << "MainMenuModel runs";

    if(views.count())
    {
        qDebug() << "OPEN" << views.first().meta->Name;
        views.first().plugin->Open(0, parentWidget);
    }

    return true;
}

bool MainMenuModelPlugin::Close()
{
    QApplication::exit();
}

void MainMenuModelPlugin::ChildSelfClosed(int id)
{
    Open(NULL, parentWidget, 0);
}

QList<MetaInfo*> MainMenuModelPlugin::GetChildPlugins()
{
    QList<MetaInfo*> tasks;
    for(int i = 0; i < childModels.count(); ++i)
        tasks.append(childModels[i].meta);
    return tasks;
}

void MainMenuModelPlugin::RunPlugin(int pluginId)
{
    if(childModels.count() > pluginId)
    {
        qDebug() << "Open plugin" << childModels[pluginId].meta->Name;
        if(!childModels[pluginId].plugin->Open(this, parentWidget, pluginId))
        {
            qDebug() << "Model wasn't opened";
            Open(NULL, parentWidget, 0);
        }
    }
}
