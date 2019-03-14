#include "plugin_base.h"

#include <QtCore>
#include <QObject>
#include <QWeakPointer>


bool PluginBase::addReferencePlugin(const IPlugin *referencePlugin)
{
    connect(this, &PluginBase::onClose, static_cast<const PluginBase*>(referencePlugin), &PluginBase::referencePluginClosed);
    return true;
}

bool PluginBase::open(const IPlugin *openedByPlugin)
{
    return true;
}

bool PluginBase::close(const IPlugin *closedByPlugin)
{
    emit onClose(this);
    return true;
}

void PluginBase::referencePluginClosed(const PluginBase *closedReference)
{
    disconnect(this, &PluginBase::onClose, closedReference, &PluginBase::referencePluginClosed);
}
