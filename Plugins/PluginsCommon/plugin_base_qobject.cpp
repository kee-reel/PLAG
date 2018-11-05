#if defined(PLUGIN_BASE_QOBJECT)
#include "plugin_base.h"

PluginBase::PluginBase(QObject *parent) :
    QObject(parent)
{
    constructorInit();
}
#endif
