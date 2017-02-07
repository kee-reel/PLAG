#include "mainmenupluginview.h"

MainMenuPluginView::MainMenuPluginView()
{
    mainWindow = new MainWindow;
}

MainMenuPluginView::~MainMenuPluginView()
{
    delete mainWindow;
}

void MainMenuPluginView::SetModel(QObject * model)
{
    this->model = qobject_cast<IMainMenuPluginModel*>(model);
    if(!this->model)
    {
        qDebug() << model->objectName() << "is not IMainMenuPluginModel.";
    }
    qDebug() << "IMainMenuPluginModel succesfully set.";
}

bool MainMenuPluginView::Open(QWidget* parent)
{
    mainWindow->setParent(parent);
    mainWindow->setGeometry(parent->geometry());
    return true;
}

bool MainMenuPluginView::Close()
{
    return true;
}
