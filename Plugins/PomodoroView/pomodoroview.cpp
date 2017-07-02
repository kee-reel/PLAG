#include "pomodoroview.h"
#include "ui_pomodoroview.h"

PomodoroView::PomodoroView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PomodoroView)
{
    ui->setupUi(this);
    connect(ui->buttonExit, SIGNAL(clicked(bool)), SLOT(Close()));
    myModel = NULL;
    button = new PomodoroButton(this);
    connect(button, SIGNAL(PomodoroFinished()), SLOT(OnPomodoroFinished()));
    ui->horizontalLayout->insertWidget(1, button);
    finishedPomodoros = 0;
}

PomodoroView::~PomodoroView()
{
    delete ui;
}

void PomodoroView::OnAllSetup()
{

}

QString PomodoroView::GetLastError()
{

}

void PomodoroView::AddModel(QObject* model)
{
    myModel = qobject_cast<IPomodoroModel*>(model);
    if(!myModel)
    {
        qDebug() << model->objectName() << "is not ITaskListModel.";
        return;
    }
    qDebug() << "ITaskListModel succesfully set.";
}

bool PomodoroView::Open(IModelPlugin *model, QWidget *parent)
{
    qDebug() << "View OPEN" << parent;
    if(!myModel)
    {
        qDebug() << "Model isn't set!";
        return false;
    }
    parent->layout()->addWidget(this);
    setParent(parent);
    show();
    return true;
}

bool PomodoroView::Close()
{
    qDebug() << "CLOSE";
    hide();
    emit OnClose(this);
    emit OnClose();
    return true;
}

void PomodoroView::OnPomodoroFinished()
{
    ++finishedPomodoros;
    ui->pomodoroCountLabel->setText(QString("%1 pomodoros").arg(finishedPomodoros));
}
