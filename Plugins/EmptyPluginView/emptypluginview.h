#ifndef EMPTYMODULE_H
#define EMPTYMODULE_H

#include <QObject>
#include <QDebug>

#include "iemptypluginmodel.h"
#include "mainwindow.h"

class EmptyPluginView : public QObject, IPluginView
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IPluginView)

public:
    EmptyPluginView();
    ~EmptyPluginView();

private:
    IEmptyPluginModel* myModel;
    int myId;

    MainWindow *mainWindow;

    // IPluginView interface
public slots:
    virtual void SetModel(QObject* myModel);
    virtual bool Open(int id, QWidget *parent);
    virtual bool Close();
};

#endif // EMPTYMODULE_H
