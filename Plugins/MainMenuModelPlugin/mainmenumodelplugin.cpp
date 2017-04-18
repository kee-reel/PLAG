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
    rootMenuItem = pluginLinker.SetupLinks();
    Open(NULL, parentWidget);
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

void MainMenuModelPlugin::AddParentModel(QObject *model, MetaInfo *meta)
{

}

bool MainMenuModelPlugin::Open(IModelPlugin *parent, QWidget *parentWidget)
{
    qDebug() << "MainMenuModel runs";

    if(views.count())
    {
        qDebug() << "OPEN" << views.first().meta->Name;
        views.first().plugin->Open(parentWidget);
    }

    return true;
}

bool MainMenuModelPlugin::CloseFromView(IViewPlugin *view)
{
    QApplication::exit();
}

void MainMenuModelPlugin::ChildSelfClosed(IModelPlugin *child)
{
    Open(NULL, parentWidget);
}

IMainMenuPluginModel::MenuItem *MainMenuModelPlugin::GetRootMenuItem()
{
    return rootMenuItem;
}

void MainMenuModelPlugin::RunItem(IMainMenuPluginModel::MenuItem *item, MetaInfo *viewMeta)
{
    QMap<IModelPlugin*, MetaInfo*>::Iterator i = pluginLinker.modelMap.begin();
    while(i != pluginLinker.modelMap.end())
    {
        if(i.value() == item->meta)
        {
            qDebug() << "Open plugin" << item->meta->Name;
            if(!i.key()->Open(this, parentWidget))
            {
                qDebug() << "Model wasn't opened";
                Open(NULL, parentWidget);
            }
            return;
        }
        ++i;
    }

    qDebug() << "Model wasn't opened";
    Open(NULL, parentWidget);
}
