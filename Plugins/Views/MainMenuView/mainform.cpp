#include "mainform.h"
#include "ui_mainform.h"

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
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
}

MainForm::~MainForm()
{
    delete zoomAnimTimer;
    delete ui;
    for(int i = 0; i < menuItems.count(); ++i)
        delete menuItems[i];
    menuItems.clear();
}

void MainForm::SetRootMenuItem(IMainMenuModel::MenuItem *RootMenuItem)
{
    if(rootMenuItem)
        return;

    rootMenuItem = RootMenuItem;
    MenuItemGraphicsObject *exitItem = new MenuItemGraphicsObject("Exit");
    connect(exitItem, SIGNAL(OnClicked(MenuItemGraphicsObject*)),
            SIGNAL(OnClose()));
    scene->addItem(exitItem);
    menuItems.append(exitItem);

    MenuItemGraphicsObject *menuItem;
    for(int j = 0; j < rootMenuItem->Items.count(); ++j)
    {
        // TODO: Bind MainForm with MainMenuPluginView if(rootMenuItem->ViewItems[j] == )
        menuItem = new MenuItemGraphicsObject(nullptr, rootMenuItem, rootMenuItem->Items[j]);
        connect(menuItem, SIGNAL(OnClicked(MenuItemGraphicsObject*)),
                SLOT(OnItemSelected(MenuItemGraphicsObject*)));
        scene->addItem(menuItem);
        menuItems.append(menuItem);
    }

    AddSubitems(nullptr, rootMenuItem);
}

void MainForm::AddSubitems(MenuItemGraphicsObject *ParentMenuItem, IMainMenuModel::MenuItem *ParentMenuItemStruct)
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

void MainForm::WipeAllItems()
{
    for(int i = 0; i < menuItems.count(); ++i)
        delete menuItems[i];
    menuItems.clear();
}

void MainForm::OnItemSelected(MenuItemGraphicsObject *menuItem)
{
//    sceneScale = 1.05;
//    scaleIter = 0;
//    zoomAnimTimer->start();

    emit OnItemSelected(menuItem->menuItem, menuItem->viewPluginMeta);
}

void MainForm::ZoomAnimation()
{
    if(++scaleIter > 20)
        zoomAnimTimer->stop();

    ui->graphicsView->scale(sceneScale, sceneScale);
}
