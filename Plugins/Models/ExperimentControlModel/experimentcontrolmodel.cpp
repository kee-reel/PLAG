#include "experimentcontrolmodel.h"


ExperimentControlModel::ExperimentControlModel()
{
    // myReferencedPlugin = NULL;
    openedView = NULL;
    openedModel = NULL;
    /*
    ui->setupUi(this);
    */
}

ExperimentControlModel::~ExperimentControlModel()
{
}

void ExperimentControlModel::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void ExperimentControlModel::OnAllSetup()
{

}

QString ExperimentControlModel::GetLastError()
{

}

void ExperimentControlModel::AddReferencePlugin(PluginInfo *pluginInfo)
{
    // Select your referenced plugin case and get it. For example:
    /*
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
        if(pluginInfo->Meta->InterfaceName == "IMAINMENUMODEL")
        {
            pluginInfo->Plugin.model->AddReferencePlugin(this->pluginInfo);
        }
    } break;

    case DATAMANAGER:{
    }break;
    }
}

void ExperimentControlModel::ReferencePluginClosed(PluginInfo *pluginInfo)
{

}

bool ExperimentControlModel::Open(IModelPlugin *parent)
{
    qDebug() << "ExperimentControlModel open.";
    if(relatedViewPlugins.count() == 0){
        qDebug() << "!ExperimentControlModel hasn't any views!";
        return false;
    }

    openedView = relatedViewPlugins.first();
    qDebug() << "ExperimentControlModel opens related view " << openedView->Meta->Name;
    if(!openedView->Plugin.view->Open(this)){
        qDebug() << "!Can't open first view!";
        openedView = NULL;
        return false;
    }
    return true;
}

void ExperimentControlModel::Close()
{
    qDebug() << "ExperimentControlModel close.";
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
