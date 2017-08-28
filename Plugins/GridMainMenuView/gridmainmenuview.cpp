#include "gridmainmenuview.h"
#include "ui_gridmainmenuview.h"

GridMainMenuView::GridMainMenuView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    openedView = NULL;
    openedModel = NULL;
    mainMenu = NULL;
    rootMenuItem = NULL;
    ui->setupUi(this);
    layout = new AspectAwareGridLayout(this);
    ui->verticalLayout->insertLayout(0, layout);
}

GridMainMenuView::~GridMainMenuView()
{
}

void GridMainMenuView::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void GridMainMenuView::OnAllSetup()
{

}

QString GridMainMenuView::GetLastError()
{

}

void GridMainMenuView::AddReferencePlugin(PluginInfo *pluginInfo)
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
        mainMenu = qobject_cast<IMainMenuModel*>(pluginInfo->Instance);
        if(mainMenu == NULL){
            qDebug() << "Can't cast" << pluginInfo->Meta->Name << "to IMainMenuModel.";
            return;
        }
        pluginInfo->Plugin.model->AddReferencePlugin(this->pluginInfo);
    } break;

    case DATAMANAGER:{

    }break;
    }
}

void GridMainMenuView::ReferencePluginClosed(PluginInfo *pluginInfo)
{

}

bool GridMainMenuView::Open(IModelPlugin *model)
{
    qDebug() << "GridMainMenuView open.";

    // If something not set.
    if(false){
        qDebug() << "!GridMainMenuView not fully initialized!";
        return false;
    }

    if(rootMenuItem == NULL)
    {
        rootMenuItem = mainMenu->GetRootMenuItem();

        int rowCapacity = 2;
        for(int j = 0; j < rootMenuItem->Items.count(); ++j)
        {
            MenuItem* item = new MenuItem(j, FormatMenuItemName(rootMenuItem->Items[j]->Name), this);
            connect(item, SIGNAL(OnMenuItemSelected(int)), SLOT(RunMenuItem(int)));
            items.append(item);
            layout->addWidget(item, j/rowCapacity, j%rowCapacity);
        }
        MenuItem* exitItem = new MenuItem(items.length(), "Exit", this);
        connect(exitItem, SIGNAL(OnMenuItemSelected(int)), SLOT(RunMenuItem(int)));
        items.append(exitItem);
        layout->addWidget(exitItem);
    }
    emit OnOpen(this);
}

bool GridMainMenuView::Close()
{
    qDebug() << "GridMainMenuView close.";
    // If view cannot close.
    if(false){
        qDebug() << "!GridMainMenuView cannot close right now!";
        return false;
    }
    openedView = NULL;
    openedModel = NULL;
    emit OnClose();
    emit OnClose(pluginInfo);
    return true;
}

void GridMainMenuView::RunMenuItem(int id)
{
    if(id == items.length()-1)
        Close();
    else
    {
        mainMenu->RunItem(rootMenuItem, rootMenuItem->Items[id]);
    }
}

QString GridMainMenuView::FormatMenuItemName(QString name)
{
    QRegExp regExp = QRegExp("([A-Z]+[a-z]+)");
    regExp.setCaseSensitivity(Qt::CaseSensitive);
    int pos = 0;
    QStringList list;
    while(pos >= 0)
    {
        pos = regExp.indexIn(name, pos);
        if(pos == -1) break;
        list.append(regExp.cap(0));
        pos += list.last().length();
    }

    QString itemMenuName;
    for(int i = 0; i < list.count(); ++i)
    {
        if(i == 0)
            itemMenuName += list[i];
        else if(i == list.count()-1)
        {
            if(list[i].toLower() == "model") break;
            itemMenuName += "\r\n" + list[i];
        }
        else
            itemMenuName += "\r\n" + list[i];
    }
    return itemMenuName;
}
