#include "heartratedeviceview.h"

#include "ui_form.h"

HeartRateDeviceView::HeartRateDeviceView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    // myReferencedPlugin = NULL;
    ui->setupUi(this);
}

HeartRateDeviceView::~HeartRateDeviceView()
{
}

void HeartRateDeviceView::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void HeartRateDeviceView::OnAllSetup()
{
}

QString HeartRateDeviceView::GetLastError()
{
}

void HeartRateDeviceView::AddReferencePlugin(PluginInfo *pluginInfo)
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
        case MODELPLUGIN:
        {
            myReferencedPlugin = qobject_cast<IHeartRateDeviceModel*>(pluginInfo->Instance);

            if(!myReferencedPlugin)
            {
                qDebug() << pluginInfo->Meta->Name << "is not IHeartRateDeviceModel.";
                return;
            }

            myReferencedPlugin->AddReferencePlugin(this->pluginInfo);
            qDebug() << "IHeartRateDeviceModel succesfully set.";
            connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
            connect(pluginInfo->Instance, SIGNAL(HeartbeatData(float)), this, SLOT(OnHeartbitData(float)));
            connect(pluginInfo->Instance, SIGNAL(TempoData(float)), this, SLOT(OnTempoData(float)));
        } break;
    }
}

void HeartRateDeviceView::ReferencePluginClosed(PluginInfo *pluginInfo)
{
}

bool HeartRateDeviceView::Open(IModelPlugin *model)
{
    qDebug() << "HeartRateDeviceView open.";

    // If something not set.
    if(false)
    {
        qDebug() << "!HeartRateDeviceView not fully initialized!";
        return false;
    }

    emit OnOpen(this);
    return true;
}

bool HeartRateDeviceView::Close()
{
    qDebug() << "HeartRateDeviceView close.";

    // If view cannot close.
    if(false)
    {
        qDebug() << "!HeartRateDeviceView cannot close right now!";
        return false;
    }

    emit OnClose(pluginInfo);
    emit OnClose();
    return true;
}

void HeartRateDeviceView::on_pushButton_clicked()
{
    Close();
}

void HeartRateDeviceView::OnHeartbitData(float data)
{
    ui->lcdNumber->display(data);
}

void HeartRateDeviceView::OnTempoData(float data)
{
    ui->progressBar->setValue(data);
}

void HeartRateDeviceView::on_horizontalSlider_sliderMoved(int position)
{
    myReferencedPlugin->SetHbO2Data(position);
    ui->label_3->setText(QString::number(position));
}
