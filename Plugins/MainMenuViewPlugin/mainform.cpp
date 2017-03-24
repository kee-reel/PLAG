#include "mainform.h"
#include "ui_mainform.h"

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
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
    rootMenuItem = RootMenuItem;
    QGraphicsEllipseItem *menuItem;
    QBrush whiteBrush(Qt::white);
    QBrush blackBrush(Qt::black);
    QPen blackPen(Qt::black);
    blackPen.setWidth(3);
    for(int i = 0; i < rootMenuItem->SubItems.count(); ++i)
    {
        menuItem = scene->addEllipse(0+i*10, 0, 100, 100, blackPen, whiteBrush);
        menuItem->setFlag(QGraphicsItem::ItemIsMovable);

        menuItems.append(menuItem);
    }
}

void MainForm::WipeAllItems()
{

}
