#include "mainmenupluginview.h"

MainMenuPluginView::MainMenuPluginView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    myModel = nullptr;
    ui->setupUi(this);
    rootMenuItem = nullptr;
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    sceneScale = 1;
    ui->graphicsView->scale(sceneScale, sceneScale);

    zoomAnimTimer = new QTimer(this);
    zoomAnimTimer->setInterval(50);
    connect(zoomAnimTimer, SIGNAL(timeout()),
            SLOT(ZoomAnimation()));
    connect(this, SIGNAL(OnItemSelected(IMainMenuModel::MenuItem*,MetaInfo*)),
            SLOT(OpenChildPlugin(IMainMenuModel::MenuItem*,MetaInfo*)));
}

MainMenuPluginView::~MainMenuPluginView()
{
    delete zoomAnimTimer;
    delete ui;
    for(int i = 0; i < menuItems.count(); ++i)
        delete menuItems[i];
    menuItems.clear();

    WipeAllItems();
}

void MainMenuPluginView::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void MainMenuPluginView::OnAllSetup()
{

}

QString MainMenuPluginView::GetLastError()
{
    return "";
}

void MainMenuPluginView::AddReferencePlugin(PluginInfo *pluginInfo)
{
    if(pluginInfo->Meta->InterfaceName == "IMAINMENUMODEL")
    {
        myModel = qobject_cast<IMainMenuModel*>(pluginInfo->Instance);
        myModel->AddReferencePlugin(this->pluginInfo);
        connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
    }
}

void MainMenuPluginView::ReferencePluginClosed(PluginInfo *pluginInfo)
{

}

//void MainMenuPluginView::AddModel(QObject *model)
//{
//    myModel = qobject_cast<IMainMenuModel*>(model);
//    if(!myModel)
//    {
//        qDebug() << model->objectName() << "is not IMainMenuPluginModel.";
//        return;
//    }
//    qDebug() << "IMainMenuPluginModel succesfully set.";
//}

bool MainMenuPluginView::Open(IModelPlugin *model)
{
    if(!myModel)
    {
        qDebug() << "My model isn't set!";
        return false;
    }

    if(!rootMenuItem)
    {
        rootMenuItem = myModel->GetRootMenuItem();
        SetRootMenuItem(rootMenuItem);
    }

    emit OnOpen(this);
    return true;
}

bool MainMenuPluginView::Close()
{
//    hide();
    setVisible(false);
    return true;
}

void MainMenuPluginView::OpenChildPlugin(IMainMenuModel::MenuItem *menuItem, MetaInfo *viewMeta)
{
    qDebug() << "Open plugin" << menuItem->meta->Name;
    Close();
    myModel->RunItem(menuItem, viewMeta);
}

void MainMenuPluginView::CloseMainMenu()
{
    Close();
    emit OnClose(pluginInfo);
    emit OnClose();
}

void MainMenuPluginView::SetRootMenuItem(IMainMenuModel::MenuItem *RootMenuItem)
{
    if(!rootMenuItem)
        return;

    rootMenuItem = RootMenuItem;
    MenuItemGraphicsObject *exitItem = new MenuItemGraphicsObject("Exit");
    connect(exitItem, SIGNAL(OnClicked(MenuItemGraphicsObject*)),
            SLOT(CloseMainMenu()));
    scene->addItem(exitItem);
    menuItems.append(exitItem);

    MenuItemGraphicsObject *menuItem;
    for(int j = 0; j < rootMenuItem->Items.count(); ++j)
    {
        if(rootMenuItem->Items[j] == this->pluginInfo->Meta)
            continue;
        menuItem = new MenuItemGraphicsObject(nullptr, rootMenuItem, rootMenuItem->Items[j]);
        connect(menuItem, SIGNAL(OnClicked(MenuItemGraphicsObject*)),
                SLOT(OnItemSelected(MenuItemGraphicsObject*)));
        scene->addItem(menuItem);
        menuItems.append(menuItem);
    }

    AddSubitems(nullptr, rootMenuItem);
}

void MainMenuPluginView::AddSubitems(MenuItemGraphicsObject *ParentMenuItem, IMainMenuModel::MenuItem *ParentMenuItemStruct)
{
    if(!ParentMenuItemStruct->SubItems.count())
        return;

    MenuItemGraphicsObject *menuItem;
    IMainMenuModel::MenuItem *parentMenuItem;
    for(int i = 0; i < ParentMenuItemStruct->SubItems.count(); ++i)
    {
        parentMenuItem = ParentMenuItemStruct->SubItems[i];
        for(int j = 0; j < parentMenuItem->Items.count(); ++j)
        {
            menuItem = new MenuItemGraphicsObject(ParentMenuItem, parentMenuItem, parentMenuItem->Items[j]);
            connect(menuItem, SIGNAL(OnClicked(MenuItemGraphicsObject*)),
                    SLOT(OnItemSelected(MenuItemGraphicsObject*)));
            scene->addItem(menuItem);
            menuItems.append(menuItem);
        }
        AddSubitems(menuItem, ParentMenuItemStruct->SubItems[i]);
    }
}

void MainMenuPluginView::WipeAllItems()
{
    for(int i = 0; i < menuItems.count(); ++i)
        delete menuItems[i];
    menuItems.clear();
}

void MainMenuPluginView::OnItemSelected(MenuItemGraphicsObject *menuItem)
{
//    sceneScale = 1.05;
//    scaleIter = 0;
//    zoomAnimTimer->start();

    emit OnItemSelected(menuItem->menuItem, menuItem->viewPluginMeta);
}

void MainMenuPluginView::ZoomAnimation()
{
    if(++scaleIter > 20)
        zoomAnimTimer->stop();

    ui->graphicsView->scale(sceneScale, sceneScale);
}
