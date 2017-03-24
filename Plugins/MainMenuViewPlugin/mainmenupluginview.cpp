#include "mainmenupluginview.h"

MainMenuPluginView::MainMenuPluginView()
{
    myModel = NULL;
    mainForm = new MainForm;
    connect(mainForm, SIGNAL(OnButtonPressed(int)), this, SLOT(OpenChildPlugin(int)));
}

MainMenuPluginView::~MainMenuPluginView()
{
    delete mainForm;
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

bool MainMenuPluginView::Open(QWidget* parent)
{
    if(!myModel)
    {
        qDebug() << "My model isn't set!";
        return false;
    }

    parent->layout()->addWidget(mainForm);
    mainForm->setParent(parent);
    mainForm->show();
    rootMenuItem = myModel->GetRootMenuItem();
    mainForm->SetRootMenuItem(rootMenuItem);
    return true;
}

bool MainMenuPluginView::Close()
{
    mainForm->hide();
    mainForm->WipeAllItems();
    //myModel->CloseFromView(this);
    return true;
}

void MainMenuPluginView::OpenChildPlugin(int id)
{
    qDebug() << "Open plugin" << id;
    Close();
    myModel->RunItem(rootMenuItem->SubItems[id]);
}
