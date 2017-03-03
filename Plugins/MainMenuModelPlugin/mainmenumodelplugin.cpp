#include "mainmenumodelplugin.h"

MainMenuModelPlugin::MainMenuModelPlugin()
{
    activeViewId = -1;

}

MainMenuModelPlugin::~MainMenuModelPlugin()
{

}

void MainMenuModelPlugin::OnAllSetup()
{


    //PluginInfo<IPluginView> newPlugin = {plugin, meta};
    //newPlugin.plugin->SetModel(qobject_cast<QObject*>(this));
}

QString MainMenuModelPlugin::GetLastError()
{

}

void MainMenuModelPlugin::AddDataSource(IDataSourcePlugin *view, QObject *instance, MetaInfo *meta)
{

}

void MainMenuModelPlugin::AddDataManager(IDataManagerPlugin *view, QObject *instance, MetaInfo *meta)
{

}

void MainMenuModelPlugin::AddView(IDataSourcePlugin *view, QObject *instance, MetaInfo *meta)
{

}

void MainMenuModelPlugin::AddModel(IDataManagerPlugin *view, QObject *instance, MetaInfo *meta)
{

}

void MainMenuModelPlugin::AddDataSource(IDataSourcePlugin *model, MetaInfo *meta)
{
    dataSourceMap.insert(model, meta);
}

void MainMenuModelPlugin::AddDataManager(IDataManagerPlugin *model, MetaInfo *meta)
{
    dataManagerMap.insert(model, meta);
}

void MainMenuModelPlugin::AddChildModel(IModelPlugin *plugin, MetaInfo *meta)
{
    qDebug() << "New child" << meta->Name;
    modelMap.insert(plugin, meta);
}

void MainMenuModelPlugin::AddView(IViewPlugin *plugin, MetaInfo *meta)
{
    viewMap.insert(plugin, meta);
    qDebug() << "IPluginView succesfully set.";
}

bool MainMenuModelPlugin::Open(IModelPlugin *parent, QWidget *parentWidget, int id)
{
    qDebug() << "EmptyModel runs";
//    if(viewPlugins.count() == 0){
//        qDebug() << "I dont have any views!";
//        return false;
//    }

    myModelId = id;
    myParent = myParent;
    myParentWidget = parentWidget;
    activeViewId = 0;

//    if(!viewPlugins[activeViewId].plugin->Open(activeViewId, myParentWidget)){
//        qDebug() << "Can't open first view!";
//        return false;
//    }

    return true;
}

bool MainMenuModelPlugin::Close()
{
    QApplication::exit();
}

void MainMenuModelPlugin::ChildSelfClosed(int id)
{
//    if(!viewPlugins[activeViewId].plugin->Open(activeViewId, myParentWidget)){
//        qDebug() << "Can't open first view!";
//    }
}

QList<MetaInfo*> MainMenuModelPlugin::GetChildPlugins()
{
    QList<MetaInfo*> tasks;
//    for(int i = 0; i < childModelPlugins.count(); i++)
//        tasks.append(childModelPlugins[i].meta);
//    return tasks;
}

void MainMenuModelPlugin::RunPlugin(int pluginId)
{
//    if(childModelPlugins.count() > pluginId)
//    {
//        qDebug() << "Open plugin" << childModelPlugins[pluginId].meta->Name;
//        if(!childModelPlugins[pluginId].plugin->Open(this, myParentWidget, pluginId))
//        {
//            qDebug() << "Model wasn't opened";
//            if(!viewPlugins[activeViewId].plugin->Open(activeViewId, myParentWidget)){
//                qDebug() << "Can't open first view!";
//            }
//        }
//    }
}
