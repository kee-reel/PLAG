#include "mainform.h"
#include "ui_mainform.h"

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
    rootMenuItem = NULL;
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
}

MainForm::~MainForm()
{
    delete ui;
    for(int i = 0; i < menuItems.count(); ++i)
        delete menuItems[i];
    menuItems.clear();
}

void MainForm::SetRootMenuItem(IMainMenuPluginModel::MenuItem *RootMenuItem)
{
    if(rootMenuItem)
        return;

    rootMenuItem = RootMenuItem;
    MenuItemGraphicsObject *menuItem = new MenuItemGraphicsObject(NULL, rootMenuItem);
    connect(menuItem, SIGNAL(OnClicked(IMainMenuPluginModel::MenuItem*)), this, SIGNAL(OnClose()));
    scene->addItem(menuItem);
    menuItems.append(menuItem);

    AddSubitems(NULL, rootMenuItem);
}

void MainForm::AddSubitems(MenuItemGraphicsObject *ParentMenuItem, IMainMenuPluginModel::MenuItem *ParentMenuItemStruct)
{
    if(!ParentMenuItemStruct->SubItems.count())
        return;

    MenuItemGraphicsObject *menuItem;
    for(int i = 0; i < ParentMenuItemStruct->SubItems.count(); ++i)
    {
        menuItem = new MenuItemGraphicsObject(ParentMenuItem, ParentMenuItemStruct->SubItems[i]);
        connect(menuItem, SIGNAL(OnClicked(IMainMenuPluginModel::MenuItem*)), this, SIGNAL(OnItemSelected(IMainMenuPluginModel::MenuItem*)));
        scene->addItem(menuItem);
        menuItems.append(menuItem);
        AddSubitems(menuItem, ParentMenuItemStruct->SubItems[i]);
    }
}

void MainForm::WipeAllItems()
{
    for(int i = 0; i < menuItems.count(); ++i)
        delete menuItems[i];
    menuItems.clear();
}
