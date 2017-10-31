#include "commonarduinoprotocolmodel.h"


CommonArduinoProtocolModel::CommonArduinoProtocolModel()
{
    // myReferencedPlugin = NULL;
    openedView = NULL;
    openedModel = NULL;
    /*
    ui->setupUi(this);
    */
}

CommonArduinoProtocolModel::~CommonArduinoProtocolModel()
{
}

void CommonArduinoProtocolModel::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void CommonArduinoProtocolModel::OnAllSetup()
{
}

QString CommonArduinoProtocolModel::GetLastError()
{
}

void CommonArduinoProtocolModel::AddReferencePlugin(PluginInfo *pluginInfo)
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
    switch(pluginInfo->Meta->Type)
    {
        case PLUGINVIEW:
            {
                relatedViewPlugins.append(pluginInfo);
                qDebug() << "New IViewPlugin added (" << pluginInfo->Meta->Name << ").";
                connect(pluginInfo->Instance, SIGNAL( OnClose(PluginInfo*) ), SLOT( ReferencePluginClosed(PluginInfo*) ));
            } break;

        case PLUGINMODEL:
            {
                relatedModelPlugins.append(pluginInfo);
                qDebug() << "New IModelPlugin added (" << pluginInfo->Meta->Name << ").";
                connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
            } break;

        case ROOTMODEL:
            {
            } break;

        case DATAMANAGER:
            {
            } break;
    }
}

void CommonArduinoProtocolModel::ReferencePluginClosed(PluginInfo *pluginInfo)
{
}

bool CommonArduinoProtocolModel::Open(IModelPlugin *parent)
{
    qDebug() << "CommonArduinoProtocolModel open.";

    if(relatedViewPlugins.count() == 0)
    {
        qDebug() << "!CommonArduinoProtocolModel hasn't any views!";
        return false;
    }

    openedView = relatedViewPlugins.first();
    qDebug() << "CommonArduinoProtocolModel opens related view " << openedView->Meta->Name;

    if(!openedView->Plugin.view->Open(this))
    {
        qDebug() << "!Can't open first view!";
        openedView = NULL;
        return false;
    }

    return true;
}

void CommonArduinoProtocolModel::Close()
{
    qDebug() << "CommonArduinoProtocolModel close.";

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

bool CommonArduinoProtocolModel::CheckPortProtocolSupport(QObject *portHandler)
{
}

bool CommonArduinoProtocolModel::SetPort(QObject *portHandler)
{
}

void CommonArduinoProtocolModel::ReadData(QByteArray *buffer)
{
    qDebug() << "Read from device:" << (*buffer);
}

void CommonArduinoProtocolModel::SetPinMode(int pin, ICommonArduinoProtocolModel::PinMode pinMode)
{
}

void CommonArduinoProtocolModel::DigitalRead(int pin)
{
}

void CommonArduinoProtocolModel::DigitalWrite(int pin, ICommonArduinoProtocolModel::DigitalValue value)
{
}

void CommonArduinoProtocolModel::AnalogRead(int pin)
{
}

void CommonArduinoProtocolModel::AnalogWrite(int pin, int value)
{
}

void CommonArduinoProtocolModel::TimeSinceDeviceStart()
{
}

void CommonArduinoProtocolModel::SetDelay(int delayIntMills)
{
}

void CommonArduinoProtocolModel::OscilloscopeOn(int pin, int resolution, int trigger)
{
}

void CommonArduinoProtocolModel::OscilloscopeGo(ICommonArduinoProtocolModel::OscilloscopeRepeatMode mode)
{
}

void CommonArduinoProtocolModel::OscilloscopeOff()
{
}
