#include "dayplanview.h"
#include "ui_form.h"

DayPlanView::DayPlanView(QWidget *parent) :
    PluginBase(parent)
{
    dayPlanModel = nullptr;
    itemModel = nullptr;
    connect(ui->buttonExit, &QPushButton::clicked, [this](){
        emit onClose(this);
    });
}

DayPlanView::~DayPlanView()
{
}

void DayPlanView::onAllReferencesSet()
{
    for(auto iter = m_referencesMap.begin(); iter != m_referencesMap.end(); ++iter)
    {
        auto&& interfaceName = iter.key();
        auto&& plugin = iter.value();
        if(!QString::compare(interfaceName, "IDayPlanModel", Qt::CaseInsensitive))
        {
            auto instance = plugin->getObject();
            dayPlanModel = qobject_cast<IDayPlanModel*>(instance);
        }
    }
    PluginBase::onAllReferencesSet();
}

void DayPlanView::onAllReferencesReady()
{
    dayPlanModel->SetDataTypeEditor(new DateTimeTypeEditor());

    auto model = dayPlanModel->GetTaskModel();
    itemModel = new DesignProxyModel(model);
    ui->treeView->setModel(itemModel);
    model = dayPlanModel->GetDateModel();
    itemModel = new DesignProxyModel(model);
    ui->treeView_2->setModel(itemModel);

    PluginBase::onAllReferencesReady();
}

//void DayPlanView::SetPluginInfo(PluginInfo *pluginInfo)
//{
//    this->pluginInfo = pluginInfo;
//}

//void DayPlanView::OnAllSetup()
//{
//    if(dayPlanModel == nullptr) return;
//    dayPlanModel->SetDataTypeEditor(new DateTimeTypeEditor());
//}

//QString DayPlanView::GetLastError()
//{

//}

//void DayPlanView::AddReferencePlugin(PluginInfo *pluginInfo)
//{
//    switch(pluginInfo->Meta->Type){
//    case VIEWPLUGIN:{
//        relatedViewPlugins.append(pluginInfo);
//        qDebug() << "New IViewPlugin added (" << pluginInfo->Meta->Name << ").";
//        connect(pluginInfo->Instance, SIGNAL( OnClose(PluginInfo*) ), SLOT( ReferencePluginClosed(PluginInfo*) ));
//    } break;

//    case MODELPLUGIN:{
//        relatedModelPlugins.append(pluginInfo);
//        qDebug() << "New IModelPlugin added (" << pluginInfo->Meta->Name << ").";
//        connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));

//        if(dayPlanModel = qobject_cast<IDayPlanModel*>(pluginInfo->Instance))
//        {
//            qDebug() << "IDayPlanModel Binded";
//            pluginInfo->Plugin.model->AddReferencePlugin(this->pluginInfo);
//        }
//    } break;

//    case COREPLUGIN:{

//    } break;

//    case DATAMANAGERPLUGIN:{

//    }break;
//    }
//}

//void DayPlanView::ReferencePluginClosed(PluginInfo *pluginInfo)
//{

//}

//bool DayPlanView::Open(IModelPlugin *model)
//{
//    qDebug() << "DayPlanView open.";

//    // If something not set.
//    if(false){
//        qDebug() << "!DayPlanView not fully initialized!";
//        return false;
//    }

//    if(dayPlanModel)
//    {
//        auto model = dayPlanModel->GetTaskModel();
//        itemModel = new DesignProxyModel(model);
//        ui->treeView->setModel(itemModel);
//        model = dayPlanModel->GetDateModel();
//        itemModel = new DesignProxyModel(model);
//        ui->treeView_2->setModel(itemModel);
//    }

//    emit OnOpen(this);
//    return true;
//}

//bool DayPlanView::Close()
//{
//    qDebug() << "DayPlanView close.";
//    // If view cannot close.
//    if(false){
//        qDebug() << "!DayPlanView cannot close right now!";
//        return false;
//    }
//    openedView = nullptr;
//    openedModel = nullptr;
//    emit OnClose(pluginInfo);
//    emit OnClose();
//    return true;
//}
