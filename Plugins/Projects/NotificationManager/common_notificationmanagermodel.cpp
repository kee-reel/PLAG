#include "notificationmanager.h"

#include <QDebug>

NotificationManager::NotificationManager() :
    PluginBase()
{
    //    NotificationManagerModel::SetInstance(this);
}

NotificationManager::~NotificationManager()
{
}

void NotificationManager::onAllReferencesSet()
{
    PluginBase::onAllReferencesSet();
}

void NotificationManager::onAllReferencesReady()
{
    PluginBase::onAllReferencesReady();
}
