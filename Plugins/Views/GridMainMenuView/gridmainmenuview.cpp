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
    exitItem = NULL;

//    quickView = new QQuickView();
//    container = QWidget::createWindowContainer(quickView, this);
//    quickView->setSource(QUrl(QStringLiteral("qrc:///Menu.qml")));
//    ui->verticalLayout->addWidget(container);

    ui->setupUi(this);
    layout = new AspectAwareGridLayout(this);
    ui->scrollAreaWidgetContents->setLayout(layout);
#ifdef Q_OS_ANDROID
    ui->scrollArea->grabGesture(Qt::TapAndHoldGesture);
    QScroller::grabGesture(ui->scrollArea, QScroller::LeftMouseButtonGesture);
#endif
}

GridMainMenuView::~GridMainMenuView()
{
    for(int i = 0; i < items.length(); ++i)
        delete items[i];
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
        mainMenu = qobject_cast<IMainMenuModel*>(pluginInfo->Instance);
        if(mainMenu == NULL){
            qDebug() << "Can't cast" << pluginInfo->Meta->Name << "to IMainMenuModel.";
            return;
        }
        pluginInfo->Plugin.model->AddReferencePlugin(this->pluginInfo);
    } break;

    case DATAMANAGERPLUGIN:{

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
        if(rootMenuItem->Items.count() != 0)
        {
            int itemMinHeight = (height() / rootMenuItem->Items.count()) * 1.2;
            layout->setSpacing(itemMinHeight * 0.3);
            int rowCapacity = 1;
            QSpacerItem *topSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
            layout->addItem(topSpacer);
            for(int j = 0; j < rootMenuItem->Items.count(); ++j)
            {
                MenuItem* item = new MenuItem(j, FormatMenuItemName(rootMenuItem->Items[j]->Name), this);
                item->setMinimumHeight(itemMinHeight);
                connect(item, SIGNAL(OnMenuItemSelected(int)), SLOT(RunMenuItem(int)));
                items.append(item);
                layout->addWidget(item);// j/rowCapacity, j%rowCapacity);
            }
        }
#ifndef Q_OS_ANDROID
        QSpacerItem *bottomSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
        layout->addItem(bottomSpacer);

        MenuItem* exitItem = new MenuItem(items.length(), "Exit", this);
        connect(exitItem, SIGNAL(OnMenuItemSelected(int)), SLOT(RunMenuItem(int)));
        items.append(exitItem);
        layout->addWidget(exitItem);
#endif
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
    if(items[id]->text() == "Exit")
        Close();
    else
        mainMenu->RunItem(rootMenuItem, rootMenuItem->Items[id]);
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
            itemMenuName += list[i];
        }
        else
            itemMenuName += list[i];
    }
    return itemMenuName;
}

void GridMainMenuView::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
//    container->resize(size());
}
