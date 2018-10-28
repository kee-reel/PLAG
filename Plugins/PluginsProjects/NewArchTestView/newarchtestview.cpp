#include "newarchtestview.h"

NewArchTestView::NewArchTestView() :
    PluginBase(nullptr)
{
}

NewArchTestView::~NewArchTestView()
{
}

bool NewArchTestView::addReferencePlugin(const IPlugin *referencePlugin)
{
    return PluginBase::addReferencePlugin(referencePlugin);
}
