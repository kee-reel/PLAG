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

void MainMenuModelPlugin::AddView(QObject *instance, MetaInfo *meta)
{
    IViewPlugin* view = qobject_cast<IViewPlugin*>(instance);
    PluginInfo<IViewPlugin> info = {view, instance, meta};
    views.append(info);
    connect(instance, SIGNAL(OnClose()), SLOT(Close()));
}

void MainMenuModelPlugin::AddDataManager(QObject *dataManager)
{

}

void MainMenuModelPlugin::AddModel(QObject *model, MetaInfo *meta)
{

}

bool MainMenuModelPlugin::Open(IModelPlugin *model, QWidget *parentWidget)
{
    qDebug() << "MainMenuModel runs";

    if(views.count())
    {
        qDebug() << "OPEN" << views.first().meta->Name;
        views.first().plugin->Open(this, parentWidget);
    }

    return true;
}

void MainMenuModelPlugin::Close()
{
    emit OnClose(this);
    emit OnClose();
    QApplication::exit();
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

void MainMenuModelPlugin::OpenChildView()
{
    Open(NULL, parentWidget);
}
