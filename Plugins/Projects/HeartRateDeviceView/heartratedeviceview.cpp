#include "heartratedeviceview.h"
#include "ui_form.h"

HeartRateDeviceView::HeartRateDeviceView(QWidget *parent) :
    PluginBase(parent),
    myReferencedPlugin(nullptr),
    dataIndex(0)
{
    connect(ui->buttonStart, SIGNAL(clicked()), SLOT(on_buttonStart_clicked()));
    connect(ui->buttonStop, SIGNAL(clicked()), SLOT(on_buttonStop_clicked()));
    connect(ui->buttonClose, SIGNAL(clicked()), SLOT(on_buttonClose_clicked()));
    connect(ui->sliderSPo2, SIGNAL(sliderMoved(int)), SLOT(on_horizontalSlider_sliderMoved(int)));
    connect(ui->spinDataIndex, SIGNAL(valueChanged(int)), SLOT(on_spinDataIndex_valueChanged(int)));
}

HeartRateDeviceView::~HeartRateDeviceView()
{
}

void HeartRateDeviceView::onAllReferencesSet()
{
    for(auto iter = m_referencesMap.begin(); iter != m_referencesMap.end(); ++iter)
    {
        auto&& interfaceName = iter.key();
        auto&& plugin = iter.value();
        if(!QString::compare(interfaceName, "IHeartRateDevice", Qt::CaseInsensitive))
        {
            auto instance = plugin->getObject();
            myReferencedPlugin = qobject_cast<IHeartRateDevice*>(instance);
            connect(instance, SIGNAL(HeartbeatData(float)), this, SLOT(OnHeartbitData(float)));
            connect(instance, SIGNAL(TempoData(float)), this, SLOT(OnTempoData(float)));
        }
    }
    PluginBase::onAllReferencesSet();
}

void HeartRateDeviceView::onAllReferencesReady()
{
}

void HeartRateDeviceView::OnHeartbitData(float data)
{
    ui->lcdHR->display(data);
}

void HeartRateDeviceView::OnTempoData(float data)
{
    ui->progressBarTempo->setValue(data);
}

void HeartRateDeviceView::on_buttonStart_clicked()
{
    myReferencedPlugin->ChooseDataIndex(dataIndex);
    myReferencedPlugin->StartTracking();
}

void HeartRateDeviceView::on_buttonStop_clicked()
{
    myReferencedPlugin->StopTracking();
}

void HeartRateDeviceView::on_buttonClose_clicked()
{
    emit onClose(this);
}

void HeartRateDeviceView::on_horizontalSlider_sliderMoved(int position)
{
    myReferencedPlugin->SetHbO2Data(position);
    ui->label_3->setText(QString::number(position));
}

void HeartRateDeviceView::on_spinDataIndex_valueChanged(int position)
{
    dataIndex = position;
    myReferencedPlugin->ChooseDataIndex(dataIndex);
}
