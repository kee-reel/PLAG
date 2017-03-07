#include "mainmenupluginview.h"

MainMenuPluginView::MainMenuPluginView()
{
    myModel = NULL;
    mainWindow = new MainWindow;
    connect(mainWindow, SIGNAL(OnButtonPressed(int)), this, SLOT(OpenChildPlugin(int)));
}

MainMenuPluginView::~MainMenuPluginView()
{
    delete mainWindow;
}

void MainMenuPluginView::OnAllSetup()
{

}

QString MainMenuPluginView::GetLastError()
{

}

void MainMenuPluginView::SetModel(QObject *model)
{
    myModel = qobject_cast<IMainMenuPluginModel*>(model);
    if(!myModel)
    {
        qDebug() << model->objectName() << "is not IMainMenuPluginModel.";
        return;
    }
    qDebug() << "IMainMenuPluginModel succesfully set.";
}

bool MainMenuPluginView::Open(int id, QWidget* parent)
{
    if(!myModel)
    {
        qDebug() << "My model isn't set!";
        return false;
    }

    myId = id;
    parent->layout()->addWidget(mainWindow);
    mainWindow->setParent(parent);
    mainWindow->setVisible(true);
    QList<MetaInfo*> list = myModel->GetChildPlugins();
    for(int i = 0; i < list.count(); i++)
    {
        qDebug() << list[i]->Name;
        mainWindow->AddNewButton(i, list[i]->Name);
    }
    mainWindow->AddNewButton(0, "Test");
    return true;
}

bool MainMenuPluginView::Close()
{
    mainWindow->setVisible(false);
    mainWindow->WipeAllButtons();
    disconnect(mainWindow, SIGNAL(OnButtonPressed(int)), this, SLOT(OpenChildPlugin(int)));
    return true;
}

void MainMenuPluginView::OpenChildPlugin(int id)
{
    qDebug() << "Open plugin" << id;
    mainWindow->setVisible(false);
    myModel->RunPlugin(id);
}
