#ifndef EMPTYMODULE_H
#define EMPTYMODULE_H

#include <QLayout>
#include <QObject>
#include <QDebug>

#include "../NeuralNetworkModel/ineuralnetworkmodel.h"
#include "../MainMenuModelPlugin/interfaces.h"
#include "mainform.h"

class NeuralNetworkView : public QObject, IViewPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IViewPlugin)

public:
    NeuralNetworkView();
    ~NeuralNetworkView();

private:
    INeuralNetworkModel* myModel;
    int myId;

    MainForm *mainForm;

    // IPlugin interface
public:
    void OnAllSetup() override;
    QString GetLastError() override;

    // IViewPlugin interface
public:
    void SetModel(QObject *model) override;
    bool Open(int id, QWidget *parent) override;
public slots:
    bool Close() override;
};

#endif // EMPTYMODULE_H
