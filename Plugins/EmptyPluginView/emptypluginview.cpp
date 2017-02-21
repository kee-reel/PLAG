#include "emptypluginview.h"

EmptyPluginView::EmptyPluginView()
{
    mainWindow = new MainWindow;
    mainWindow->setVisible(false);
    myModel = NULL;
}

EmptyPluginView::~EmptyPluginView()
{
}

void EmptyPluginView::SetModel(QObject* model)
{
    this->myModel = qobject_cast<IEmptyPluginModel*>(model);
    if(!this->myModel)
    {
        qDebug() << model->objectName() << "is not IMainMenuPluginModel.";
    }
    qDebug() << "IMainMenuPluginModel succesfully set.";
}

bool EmptyPluginView::Open(int id, QWidget *parent)
{
    myId = id;
    mainWindow->setParent(parent);
    mainWindow->setVisible(true);
    connect(mainWindow, SIGNAL(onClose()), this, SLOT(Close()));
    qDebug() << "Open empty plugin.";
    return true;
}

bool EmptyPluginView::Close()
{
    mainWindow->setVisible(false);
    myModel->Close();
    qDebug() << "Close empty plugin.";
    return true;
}
