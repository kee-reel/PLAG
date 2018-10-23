#include "newarchtestplugin.h"


NewArchTestPlugin::NewArchTestPlugin()
{
    qDebug() << "NewArchTestPlugin::NewArchTestPlugin()";
}

NewArchTestPlugin::~NewArchTestPlugin()
{
}

bool NewArchTestPlugin::addReferencePlugin(const IPlugin *referencePlugin)
{
    return PluginBase::addReferencePlugin(referencePlugin);
}

int NewArchTestPlugin::someMethod(int x)
{
    return x*x;
}
