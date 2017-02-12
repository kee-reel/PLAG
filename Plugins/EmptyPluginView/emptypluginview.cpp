#include "emptypluginview.h"

EmptyPluginView::EmptyPluginView()
{
    model = NULL;
}

EmptyPluginView::~EmptyPluginView()
{
}

void EmptyPluginView::SetModel(QObject* model)
{
    this->model = qobject_cast<IEmptyPluginModel*>(model);
    if(!this->model)
    {
        qDebug() << model->objectName() << "is not IMainMenuPluginModel.";
    }
    qDebug() << "IMainMenuPluginModel succesfully set.";
}

bool EmptyPluginView::Open(QWidget* parent)
{
    if(!model)
    {
        qDebug() << "Model isnt set!";
        return false;
    }
    qDebug() << "Open empty plugin.";
    return false;
}

bool EmptyPluginView::Close()
{
    if(!model)
    {
        qDebug() << "Model isnt set!";
        return false;
    }
    qDebug() << "Close empty plugin.";
    return true;
}
