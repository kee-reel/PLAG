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

void MainMenuModelPlugin::Open(QWidget *parentWidget)
{
    this->parentWidget = parentWidget;
    pluginLinker.SetupLinks();
    Open(NULL, parentWidget);
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
    case ROOTMODEL:
        break;
    case PLUGINMODEL:
        childModels.append(pluginInfo);
        rootMenuItem->Items.append(pluginInfo->Meta);
        break;
    case PLUGINVIEW:
        qDebug() << "AddReference" << pluginInfo->Meta->Name;
        views.append(pluginInfo);
        connect(pluginInfo->Instance, SIGNAL(OnClose(PluginInfo*)), SLOT(ReferencePluginClosed(PluginInfo*)));
        break;
    case DATASOURCE:
        break;
    case DATAMANAGER:
        break;
    }
}

void MainMenuModelPlugin::ReferencePluginClosed(PluginInfo *pluginInfo)
{
    switch(pluginInfo->Meta->Type)
    {
    case PLUGINMODEL:
        Open(NULL, parentWidget);
        break;
    case PLUGINVIEW:
        Close();
        break;
    }
}

//void MainMenuModelPlugin::AddView(QObject *instance, MetaInfo *meta)
//{
//    //IViewPlugin* view = qobject_cast<IViewPlugin*>(instance);
//    //PluginInfo<IViewPlugin> info = {view, instance, meta};
//    //views.append(info);
//    //connect(instance, SIGNAL(OnClose(IViewPlugin*)), SLOT(RelatedViewClosed(IViewPlugin*)));
//}

//void MainMenuModelPlugin::AddDataManager(QObject *dataManager)
//{

//}

//void MainMenuModelPlugin::AddModel(QObject *model, MetaInfo *meta)
//{

//}

bool MainMenuModelPlugin::Open(IModelPlugin *model, QWidget *parentWidget)
{
    qDebug() << "MainMenuModel runs";

    if(views.count())
    {
        qDebug() << "OPEN" << views.first()->Meta->Name;
        views.first()->Plugin.view->Open(this, parentWidget);
    }
    return true;
}

//void MainMenuModelPlugin::RelatedModelClosed(IModelPlugin *model)
//{
//    Open(NULL, parentWidget);
//}

//void MainMenuModelPlugin::RelatedViewClosed(IViewPlugin *view)
//{
//    Close();
//}

void MainMenuModelPlugin::Close()
{
    //emit OnClose(pluginInfo);
    //emit OnClose();
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
            if(!iter->Plugin.model->Open(this, parentWidget)){
                qDebug() << "Model wasn't opened";
                Open(NULL, parentWidget);
            }
        }
    }
//    QMap<MetaInfo*, PluginInfo*>::Iterator i = pluginLinker.menuItems.begin();
//    while(i != pluginLinker.menuItems.end())
//    {
//        if(viewMeta == i.key())
//        {
//            qDebug() << "Open plugin" << viewMeta->Name;
//            if(!i.value()->Plugin.view->Open(this, parentWidget))
//            {
//                qDebug() << "Model wasn't opened";
//                Open(NULL, parentWidget);
//            }
//            return;
//        }
//        ++i;
//    }
}

void MainMenuModelPlugin::OpenChildView()
{
    Open(NULL, parentWidget);
}
