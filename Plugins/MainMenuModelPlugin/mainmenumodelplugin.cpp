#include "mainmenumodelplugin.h"

MainMenuModelPlugin::MainMenuModelPlugin()
{
    activeViewId = -1;

}

MainMenuModelPlugin::~MainMenuModelPlugin()
{

}

void MainMenuModelPlugin::AddChildPlugin(IPluginModel *plugin, MetaInfo *meta)
{
    qDebug() << "New child" << meta->Name;
    PluginInfo<IPluginModel> newPlugin = {plugin, meta};
    childModelPlugins.append(newPlugin);
}

void MainMenuModelPlugin::AddView(IPluginView *plugin, MetaInfo *meta)
{
    PluginInfo<IPluginView> newPlugin = {plugin, meta};
    viewPlugins.append(newPlugin);
    newPlugin.plugin->SetModel(qobject_cast<QObject*>(this));
    qDebug() << "IPluginView succesfully set.";
}

void MainMenuModelPlugin::SetDataManager(QObject *DBTool)
{
    qDebug() << "I dont need DBTool";
}

bool MainMenuModelPlugin::Open(IPluginModel *parent, QWidget *parentWidget, int id)
{
    qDebug() << "EmptyModel runs";
    if(viewPlugins.count() == 0){
        qDebug() << "I dont have any views!";
        return false;
    }

    myModelId = id;
    myParent = myParent;
    myParentWidget = parentWidget;
    activeViewId = 0;

    if(!viewPlugins[activeViewId].plugin->Open(activeViewId, myParentWidget)){
        qDebug() << "Can't open first view!";
        return false;
    }

    return true;
}

bool MainMenuModelPlugin::Close()
{
    QApplication::exit();
}

void MainMenuModelPlugin::ChildSelfClosed(int id)
{
    if(!viewPlugins[activeViewId].plugin->Open(activeViewId, myParentWidget)){
        qDebug() << "Can't open first view!";
    }
}

QString MainMenuModelPlugin::GetError()
{

}

QList<MetaInfo*> MainMenuModelPlugin::GetChildPlugins()
{
    QList<MetaInfo*> tasks;
    for(int i = 0; i < childModelPlugins.count(); i++)
        tasks.append(childModelPlugins[i].meta);
    return tasks;
}

void MainMenuModelPlugin::RunPlugin(int pluginId)
{
    if(childModelPlugins.count() > pluginId)
    {
        qDebug() << "Open plugin" << childModelPlugins[pluginId].meta->Name;
        if(!childModelPlugins[pluginId].plugin->Open(this, myParentWidget, pluginId))
        {
            qDebug() << "Model wasn't opened";
            if(!viewPlugins[activeViewId].plugin->Open(activeViewId, myParentWidget)){
                qDebug() << "Can't open first view!";
            }
        }
    }
}
