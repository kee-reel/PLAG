#include "worktimermodel.h"


WorkTimerModel::WorkTimerModel()
{
    // myReferencedPlugin = NULL;
    openedView = NULL;
    openedModel = NULL;
    ReadStatsFromFile();
    SetupTiming();
    SetupNotification();
    pomodoroState = PomodoroState::Lesure;
}

WorkTimerModel::~WorkTimerModel()
{
}

void WorkTimerModel::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void WorkTimerModel::OnAllSetup()
{

}

QString WorkTimerModel::GetLastError()
{

}

void WorkTimerModel::AddReferencePlugin(PluginInfo *pluginInfo)
{
    /* Select your reference plugin case and get it. For example:
        case PLUGINMODEL:{
            myReferencedPlugin = qobject_cast<ISomePlugin*>(pluginInfo->Instance);
            if(!myReferencedPlugin)
            {
                qDebug() << pluginInfo->Meta->Name << "is not ISomePlugin.";
                return;
            }
            qDebug() << "ISomePlugin succesfully set.";
            connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
        } break;
    */

    switch(pluginInfo->Meta->Type){
    case VIEWPLUGIN:{
        relatedViewPlugins.append(pluginInfo);
        qDebug() << "New IViewPlugin added (" << pluginInfo->Meta->Name << ").";
        connect(pluginInfo->Instance, SIGNAL( OnClose(PluginInfo*) ), SLOT( ReferencePluginClosed(PluginInfo*) ));
    } break;

    case MODELPLUGIN:{
        relatedModelPlugins.append(pluginInfo);
        qDebug() << "New IModelPlugin added (" << pluginInfo->Meta->Name << ").";
        connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
    } break;

    case COREPLUGIN:{
    } break;

    case DATAMANAGERPLUGIN:{
    }break;
    }
}

void WorkTimerModel::ReferencePluginClosed(PluginInfo *pluginInfo)
{

}

bool WorkTimerModel::Open(IModelPlugin *parent)
{
    qDebug() << "WorkTimerModel open.";
    if(relatedViewPlugins.count() == 0){
        qDebug() << "!WorkTimerModel hasn't any views!";
        return false;
    }

    openedView = relatedViewPlugins.first();
    qDebug() << "WorkTimerModel opens related view " << openedView->Meta->Name;
    if(!openedView->Plugin.view->Open(this)){
        qDebug() << "!Can't open first view!";
        openedView = NULL;
        return false;
    }
    return true;
}

void WorkTimerModel::Close()
{
    qDebug() << "WorkTimerModel close.";
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

