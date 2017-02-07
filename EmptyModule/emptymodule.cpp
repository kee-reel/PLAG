#include "emptymodule.h"

EmptyModule::EmptyModule()
{
    mainWindow = new MainWindow;
}

EmptyModule::~EmptyModule()
{
    delete mainWindow;
}

void EmptyModule::DoSomething()
{

}

void EmptyModule::AddChildPlugin(IPluginModel *plugin, MetaInfo *meta)
{
    qDebug() << "New child" << meta->Name;
    childPlugins.insert(plugin, meta);
}

void EmptyModule::AddDBTool(QObject *DBTool)
{

}

bool EmptyModule::Open(QWidget* parent)
{
    mainWindow->show();

    return true;
}

bool EmptyModule::Close()
{
    mainWindow->close();

    return true;
}

QString EmptyModule::GetError()
{

}
