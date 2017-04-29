#ifndef POMODOROVIEW_H
#define POMODOROVIEW_H

#include <QApplication>
#include <QDebug>
#include <QLayout>
#include <QWidget>

#include "../PomodoroModel/ipomodoromodel.h"
#include "pomodorobutton.h"

namespace Ui {
class PomodoroView;
}

class PomodoroView : public QWidget, IViewPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IViewPlugin)

public:
    explicit PomodoroView(QWidget *parent = 0);
    ~PomodoroView();

private:
    Ui::PomodoroView *ui;
    IPomodoroModel *myModel;
    PomodoroButton *button;
    int finishedPomodoros;

    // IPlugin interface
public:
    void OnAllSetup() override;
    QString GetLastError() override;

    // IPluginView interface
public:
    void SetModel(QObject* model) override;
    bool Open(QWidget* parent) override;

public slots:
    bool Close() override;

private slots:
    void OnPomodoroFinished();
};

#endif // TASKLISTVIEW_H
