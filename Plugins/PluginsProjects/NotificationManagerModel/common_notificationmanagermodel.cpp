#include "notificationmanagermodel.h"

#include <QDebug>

NotificationManagerModel::NotificationManagerModel() :
    PluginBase()
{
    //    NotificationManagerModel::SetInstance(this);
}

NotificationManagerModel::~NotificationManagerModel()
{
}

void NotificationManagerModel::onAllReferencesSet()
{
    PluginBase::onAllReferencesSet();
}

void NotificationManagerModel::onAllReferencesReady()
{
    PluginBase::onAllReferencesReady();
}
