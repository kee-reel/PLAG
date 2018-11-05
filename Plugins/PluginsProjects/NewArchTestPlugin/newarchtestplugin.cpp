#include "newarchtestplugin.h"


NewArchTestPlugin::NewArchTestPlugin() :
    PluginBase(nullptr)
{
    qDebug() << "NewArchTestPlugin::NewArchTestPlugin()";
}

NewArchTestPlugin::~NewArchTestPlugin()
{
}

int NewArchTestPlugin::someMethod(int x)
{
    return x * x;
}
