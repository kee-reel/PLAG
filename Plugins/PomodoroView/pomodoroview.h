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

//! \defgroup PomodoroView
//!     \ingroup MainMenuPlugin_rel_v
//! \defgroup PomodoroView_imp Implementation
//!     \ingroup PomodoroView

//! \addtogroup PomodoroView_imp
//! \{
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
    PluginInfo *pluginInfo;

    // IPlugin interface
public:
    void SetPluginInfo(PluginInfo *pluginInfo) override;
    void OnAllSetup() override;
    QString GetLastError() override;
    void AddReferencePlugin(PluginInfo *pluginInfo) override;

public slots:
    void ReferencePluginClosed(PluginInfo *pluginInfo) override;

    // IViewPlugin interface
public slots:
    bool Open(IModelPlugin *model, QWidget *parent) override;
    bool Close() override;

signals:
    void OnClose(PluginInfo*);
    void OnClose();

private slots:
    void OnPomodoroFinished();
};
//! \}
#endif // TASKLISTVIEW_H
