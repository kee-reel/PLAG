#include "mainmenupluginview.h"

MainMenuPluginView::MainMenuPluginView()
{
    mainWindow = new MainWindow;
}

MainMenuPluginView::~MainMenuPluginView()
{
    delete mainWindow;
}

void MainMenuPluginView::SetModel(QObject *model)
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
    qDebug() << "===============" << parent->geometry();
    QList<MetaInfo*> list = model->GetChildPlugins();
    for(int i = 0; i < list.count(); i++)
    {
        qDebug() << list[i]->Name;
        mainWindow->AddNewButton(i, list[i]->Name);
    }
    connect(mainWindow, SIGNAL(OnButtonPressed(int)), this, SLOT(OpenChildPlugin(int)));
    return true;
}

bool MainMenuPluginView::Close()
{
    disconnect(mainWindow, SIGNAL(OnButtonPressed(int)), this, SLOT(OpenChildPlugin(int)));
    return true;
}

void MainMenuPluginView::OpenChildPlugin(int id)
{
    qDebug() << "Open plugin" << id;
    model->RunPlugin(id);
}
