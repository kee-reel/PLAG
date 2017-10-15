#include "hardwaredatamanager.h"

HardwareDataManager::HardwareDataManager()
{
/*
    ui->setupUi(this);
    */
}

HardwareDataManager::~HardwareDataManager()
{
}

void HardwareDataManager::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void HardwareDataManager::OnAllSetup()
{

}

QString HardwareDataManager::GetLastError()
{

}

void HardwareDataManager::AddReferencePlugin(PluginInfo *pluginInfo)
{
    // Select your plugin case and get it. For example:
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
    } break;

    case PLUGINMODEL:{
    } break;

    case ROOTMODEL:{
    } break;

    case DATAMANAGER:{
    }break;
    }
}

void HardwareDataManager::ReferencePluginClosed(PluginInfo *pluginInfo)
{

}


