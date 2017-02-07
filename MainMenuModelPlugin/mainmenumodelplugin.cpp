#include "mainmenumodelplugin.h"

MainMenuModelPlugin::MainMenuModelPlugin()
{

}

MainMenuModelPlugin::~MainMenuModelPlugin()
{

}

void MainMenuModelPlugin::DoSomething()
{
    qDebug() << "So cool!";
    int i = 0;
    i++;
    qDebug() << i;
}

void MainMenuModelPlugin::AddChildPlugin(IPluginModel *plugin, MetaInfo *meta)
{
    childPlugins.insert(plugin, meta);
}

void MainMenuModelPlugin::AddDBTool(QObject *DBTool)
{
    this->DBTool = qobject_cast<ITaskDBToolPlugin*>(DBTool);
    if(!this->DBTool)
    {
        qDebug() << DBTool->objectName() << "is not ITaskDBToolPlugin.";
    }
    qDebug() << "ITaskDBToolPlugin succesfully set.";
}

QString MainMenuModelPlugin::GetError()
{

}

QStringList MainMenuModelPlugin::GetTasks()
{
    QStringList tasks;
    tasks << "Do" << "DoDo" << "Dooooooo";
    return tasks;
}
