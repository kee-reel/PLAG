#include "androidnotificationmodel.h"

AndroidNotificationModel::AndroidNotificationModel()
{
    openedView = NULL;
    openedModel = NULL;
    notificationClient = new NotificationClient();
}

AndroidNotificationModel::~AndroidNotificationModel()
{
}

void AndroidNotificationModel::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void AndroidNotificationModel::OnAllSetup()
{

}

QString AndroidNotificationModel::GetLastError()
{

}

void AndroidNotificationModel::AddReferencePlugin(PluginInfo *pluginInfo)
{
    switch(pluginInfo->Meta->Type){
    case PLUGINVIEW:{
        relatedViewPlugins.append(pluginInfo);
        qDebug() << "New IViewPlugin added (" << pluginInfo->Meta->Name << ").";
        connect(pluginInfo->Instance, SIGNAL( OnClose(PluginInfo*) ), SLOT( ReferencePluginClosed(PluginInfo*) ));
    } break;

    case PLUGINMODEL:{
        relatedModelPlugins.append(pluginInfo);
        qDebug() << "New IModelPlugin added (" << pluginInfo->Meta->Name << ").";
        connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
    } break;

    case ROOTMODEL:{
        pluginInfo->Plugin.model->AddReferencePlugin(this->pluginInfo);
    } break;

    case DATAMANAGER:{

    }break;
    }
}

void AndroidNotificationModel::ReferencePluginClosed(PluginInfo *pluginInfo)
{

}

bool AndroidNotificationModel::Open(IModelPlugin *parent, QWidget *referenceWidget)
{
    qDebug() << "AndroidNotificationModel open.";
    PushNotification("Hi there");
    if(relatedViewPlugins.count() == 0){
        qDebug() << "!AndroidNotificationModel hasn't any views!";
        return false;
    }

    this->referenceWidget = referenceWidget;
    openedView = relatedViewPlugins.first();
    qDebug() << "AndroidNotificationModel opens related view " << openedView->Meta->Name;
    if(!openedView->Plugin.view->Open(this, this->referenceWidget)){
        qDebug() << "!Can't open first view!";
        openedView = NULL;
        return false;
    }
    return true;
}

void AndroidNotificationModel::Close()
{
    qDebug() << "AndroidNotificationModel close.";
    if(openedView != NULL && !openedView->Plugin.view->Close()){
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

void AndroidNotificationModel::PushNotification(QString message)
{
    notificationClient->setNotification(message);
}
