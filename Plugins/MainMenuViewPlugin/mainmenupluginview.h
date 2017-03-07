#ifndef MAINMENUPLUGINVIEW_H
#define MAINMENUPLUGINVIEW_H

#include <QLayout>
#include <QObject>
#include <QDebug>

#include "../MainMenuModelPlugin/imainmenumodule.h"
#include "mainwindow.h"

class MainMenuPluginView : public QObject, IViewPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IViewPlugin)

private:
    IMainMenuPluginModel *myModel;
    int myId;
    MainWindow* mainWindow;


public:
    MainMenuPluginView();
    ~MainMenuPluginView();

    void OnAllSetup() override;
    QString GetLastError() override;

    void SetModel(QObject *model) override;
    bool Open(int id, QWidget* parent) override;
    bool Close() override;

private slots:
    void OpenChildPlugin(int id);

};

#endif // MAINMENUPLUGINVIEW_H
