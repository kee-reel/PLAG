#include "mainmenupluginview.h"

MainMenuPluginView::MainMenuPluginView()
{
    myModel = NULL;
    mainForm = new MainForm;
    connect(mainForm, SIGNAL(OnItemSelected(IMainMenuPluginModel::MenuItem*,MetaInfo*)),
            this, SLOT(OpenChildPlugin(IMainMenuPluginModel::MenuItem*,MetaInfo*)));
    connect(mainForm, SIGNAL(OnClose()), this, SLOT(CloseMainMenu()));
}

MainMenuPluginView::~MainMenuPluginView()
{
    mainForm->WipeAllItems();
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
    return true;
}

void MainMenuPluginView::OpenChildPlugin(IMainMenuPluginModel::MenuItem *menuItem, MetaInfo *viewMeta)
{
    qDebug() << "Open plugin" << menuItem->meta->Name;
    Close();
    myModel->RunItem(menuItem, viewMeta);
}

void MainMenuPluginView::CloseMainMenu()
{
    Close();
    myModel->CloseFromView(this);
}
