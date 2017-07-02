#include "tasksketchview.h"

TaskSketchView::TaskSketchView()
{
    mainForm = new MainForm;
    connect(mainForm, SIGNAL(onClose()), this, SLOT(Close()));
    myModel = NULL;
}

TaskSketchView::~TaskSketchView()
{
    delete mainForm;
}

void TaskSketchView::OnAllSetup()
{

}

QString TaskSketchView::GetLastError()
{
    return "";
}

void TaskSketchView::AddModel(QObject* model)
{
    myModel = qobject_cast<ITaskSketchModel*>(model);
    if(!myModel)
    {
        qDebug() << model->objectName() << "is not ITaskListModel.";
        return;
    }
    qDebug() << "ITaskListModel succesfully set.";
    connect(mainForm, SIGNAL(OnItemConvert(int)), model, SIGNAL(OpenTaskEdit(int)));
}

bool TaskSketchView::Open(IModelPlugin *model, QWidget *parent)
{
    qDebug() << "View OPEN" << parent;
    if(!myModel)
    {
        qDebug() << "Model isn't set!";
        return false;
    }
    parent->layout()->addWidget(mainForm);
    mainForm->setParent(parent);
    mainForm->show();
    mainForm->SetModel(myModel);
    return true;
}

bool TaskSketchView::Close()
{
    qDebug() << "CLOSE";
    mainForm->hide();
    emit OnClose(this);
    emit OnClose();
    return true;
}
