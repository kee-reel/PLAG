#include "notificationmanagermodel.h"

#include <QDebug>

NotificationManagerModel::NotificationManagerModel()
{
    openedView = NULL;
    openedModel = NULL;
    //    NotificationManagerModel::SetInstance(this);
}

NotificationManagerModel::~NotificationManagerModel()
{
}

void NotificationManagerModel::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

QString NotificationManagerModel::GetLastError()
{
}

void NotificationManagerModel::AddReferencePlugin(PluginInfo *pluginInfo)
{
    switch(pluginInfo->Meta->Type)
    {
        case VIEWPLUGIN:
        {
            relatedViewPlugins.append(pluginInfo);
            qDebug() << "New IViewPlugin added (" << pluginInfo->Meta->Name << ").";
            connect(pluginInfo->Instance, SIGNAL( OnClose(PluginInfo*) ), SLOT( ReferencePluginClosed(PluginInfo*) ));
        } break;

        case MODELPLUGIN:
        {
            relatedModelPlugins.append(pluginInfo);
            qDebug() << "New IModelPlugin added (" << pluginInfo->Meta->Name << ").";
            connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
        } break;

        case COREPLUGIN:
        {
            pluginInfo->Plugin.model->AddReferencePlugin(this->pluginInfo);
        } break;

        case DATAMANAGERPLUGIN:
        {
        } break;
    }
}

void NotificationManagerModel::ReferencePluginClosed(PluginInfo *pluginInfo)
{
}

bool NotificationManagerModel::Open(IModelPlugin *parent)
{
    qDebug() << "AndroidNotificationModel open.";

    if(relatedViewPlugins.count() == 0)
    {
        qDebug() << "!AndroidNotificationModel hasn't any views!";
        return false;
    }

    openedView = relatedViewPlugins.first();
    qDebug() << "AndroidNotificationModel opens related view " << openedView->Meta->Name;

    if(!openedView->Plugin.view->Open(this))
    {
        qDebug() << "!Can't open first view!";
        openedView = NULL;
        return false;
    }

    return true;
}

void NotificationManagerModel::Close()
{
    qDebug() << "AndroidNotificationModel close.";

    if(openedView != NULL && !openedView->Plugin.view->Close())
    {
        qDebug() << "View plugin" << openedView->Meta->Name
                 << "not closed, but model closing anyway.";
    }

    if(openedModel != NULL)
        openedView->Plugin.view->Close();

    openedView = NULL;
    openedModel = NULL;
    emit OnClose(pluginInfo);
    emit OnClose();
}
