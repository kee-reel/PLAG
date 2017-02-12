#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{

}

MainWindow::~MainWindow()
{
}

void MainWindow::AddNewButton(int id, QString task)
{
    DraggableButton* moduleButton = new DraggableButton(this, id, task);
    moduleButton->setGeometry(0, 0, 50, 50);
    modulesButtons.append(moduleButton);
    connect(moduleButton, SIGNAL(OnClicked(int)), this, SIGNAL(OnButtonPressed(int)));
}
