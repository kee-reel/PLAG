#include "uimanager.h"

UIManager::UIManager() :
    PluginBase(nullptr)
{
}

UIManager::~UIManager()
{
}

bool UIManager::addReferencePlugin(const IPlugin *referencePlugin)
{
    return PluginBase::addReferencePlugin(referencePlugin);
}
