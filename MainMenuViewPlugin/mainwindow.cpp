#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{

}

MainWindow::~MainWindow()
{
}

void MainWindow::AddNewModuleView(MetaInfo *meta)
{
    DraggableButton* moduleButton = new DraggableButton(this);
    modulesButtons.append(moduleButton);
}
