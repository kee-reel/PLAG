#include "mainmenumodelplugin.h"

MainMenuModelPlugin::MainMenuModelPlugin()
{
    activeViewId = -1;
    rootMenuItem = new MenuItem();
}

MainMenuModelPlugin::~MainMenuModelPlugin()
{

}

void MainMenuModelPlugin::AddPlugin(QObject *instance, QJsonObject *meta)
{
    pluginLinker.AddNewPlugin(instance, meta);
}

void MainMenuModelPlugin::Run(QWidget *parentWidget)
{
    widgetStack = new WidgetStack(parentWidget);
    pluginLinker.SetupLinks();
    foreach (auto plugin, pluginLinker.pluginsInfo) {
        if(plugin->Meta->Type == VIEWPLUGIN)
        {
            connect(plugin->Instance, SIGNAL(OnOpen(QWidget*)), widgetStack, SLOT(Push(QWidget*)));
            connect(plugin->Instance, SIGNAL(OnClose()), widgetStack, SLOT(Pop()));
        }
    }
    Open(NULL);
}

void MainMenuModelPlugin::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
    rootMenuItem->meta = this->pluginInfo->Meta;
}

void MainMenuModelPlugin::OnAllSetup()
{
    qDebug() << "OnAllSetup";
}

QString MainMenuModelPlugin::GetLastError()
{
    return QString();
}

void MainMenuModelPlugin::AddReferencePlugin(PluginInfo *pluginInfo)
{
    switch(pluginInfo->Meta->Type)
    {
    case COREPLUGIN:
        break;
    case MODELPLUGIN:
        childModels.append(pluginInfo);
        rootMenuItem->Items.append(pluginInfo->Meta);
        connect(pluginInfo->Instance, SIGNAL(OnClose(PluginInfo*)), SLOT(ReferencePluginClosed(PluginInfo*)));
        break;
    case VIEWPLUGIN:
        qDebug() << "AddReference" << pluginInfo->Meta->Name;
        views.append(pluginInfo);
        connect(pluginInfo->Instance, SIGNAL(OnClose(PluginInfo*)), SLOT(ReferencePluginClosed(PluginInfo*)));
        break;
    case DATASOURCEPLUGIN:
        break;
    case DATAMANAGERPLUGIN:
        break;
    }
}

void MainMenuModelPlugin::ReferencePluginClosed(PluginInfo *pluginInfo)
{
//    switch(pluginInfo->Meta->Type)
//    {
//    case PLUGINMODEL:
//        Open(NULL);
//        break;
//    case PLUGINVIEW:
//        Close();
//        break;
//    }
}

bool MainMenuModelPlugin::Open(IModelPlugin *model)
{
    qDebug() << "MainMenuModel runs";

    if(views.count())
    {
        qDebug() << "OPEN" << views.first()->Meta->Name;
        views.first()->Plugin.view->Open(this);
    }
    else
    {
        qDebug() << "!Model have no views!";
    }
    return true;
}

void MainMenuModelPlugin::Close()
{
    QApplication::exit();
}

IMainMenuModel::MenuItem *MainMenuModelPlugin::GetRootMenuItem()
{
    return rootMenuItem;
}

void MainMenuModelPlugin::RunItem(IMainMenuModel::MenuItem *item, MetaInfo *itemMeta)
{
    foreach (auto iter, childModels){
        if(iter->Meta == itemMeta){
            qDebug() << "Open plugin" << iter->Meta->Name;
            if(!iter->Plugin.model->Open(this)){
                qDebug() << "Model wasn't opened";
            }
        }
    }
}

void MainMenuModelPlugin::OpenChildView()
{
    Open(NULL);
}
