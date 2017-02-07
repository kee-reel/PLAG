#ifndef MAINMENUPLUGINVIEW_H
#define MAINMENUPLUGINVIEW_H

#include <QObject>
#include <QDebug>

#include "imainmenumodule.h"
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
    MainWindow* mainWindow;
    IMainMenuPluginModel* model;

    // IPluginView interface
public:
    virtual void SetModel(QObject *model);

    bool Open(QWidget*) override;
    bool Close() override;
};

#endif // MAINMENUPLUGINVIEW_H
