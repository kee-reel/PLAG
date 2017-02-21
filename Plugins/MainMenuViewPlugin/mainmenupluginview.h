#ifndef MAINMENUPLUGINVIEW_H
#define MAINMENUPLUGINVIEW_H

#include <QObject>
#include <QDebug>

#include "../MainMenuModelPlugin/imainmenumodule.h"
#include "mainwindow.h"

class MainMenuPluginView : public QObject, IPluginView
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IPluginView)

public:
    MainMenuPluginView();
    ~MainMenuPluginView();

private:
    IMainMenuPluginModel *myModel;
    int myId;
    MainWindow* mainWindow;


    // IPluginView interface
public:
    virtual void SetModel(QObject *model);
    bool Open(int id, QWidget* parent) override;
    bool Close() override;

private slots:
    void OpenChildPlugin(int id);
};

#endif // MAINMENUPLUGINVIEW_H
