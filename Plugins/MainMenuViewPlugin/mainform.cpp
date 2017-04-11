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
    MenuItemGraphicsObject *exitItem = new MenuItemGraphicsObject("Exit");
    connect(exitItem, SIGNAL(OnClicked(IMainMenuPluginModel::MenuItem*, MetaInfo*)),
            this, SIGNAL(OnClose()));
    scene->addItem(exitItem);
    menuItems.append(exitItem);

    AddSubitems(NULL, rootMenuItem);
}

void MainForm::AddSubitems(MenuItemGraphicsObject *ParentMenuItem, IMainMenuPluginModel::MenuItem *ParentMenuItemStruct)
{
    if(!ParentMenuItemStruct->SubItems.count())
        return;

    MenuItemGraphicsObject *menuItem;
    IMainMenuPluginModel::MenuItem *parentMenuItem;
    for(int i = 0; i < ParentMenuItemStruct->SubItems.count(); ++i)
    {
        parentMenuItem = ParentMenuItemStruct->SubItems[i];
        for(int j = 0; j < parentMenuItem->ViewItems.count(); ++j)
        {
            menuItem = new MenuItemGraphicsObject(ParentMenuItem, parentMenuItem, parentMenuItem->ViewItems[j]);
            connect(menuItem, SIGNAL(OnClicked(IMainMenuPluginModel::MenuItem*, MetaInfo*)),
                    this, SIGNAL(OnItemSelected(IMainMenuPluginModel::MenuItem*, MetaInfo*)));
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
