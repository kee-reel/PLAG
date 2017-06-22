#ifndef EMPTYMODULE_H
#define EMPTYMODULE_H

#include <QLayout>
#include <QObject>
#include <QDebug>

#include "../NeuralNetworkModel/ineuralnetworkmodel.h"
#include "../MainMenuModelPlugin/interfaces.h"
#include "mainform.h"

//! \defgroup PerceptronNetworkViewPlugin
//!     \ingroup MainMenuPlugin_rel_v
//! \defgroup PerceptronNetworkViewPlugin_imp Implementation
//!     \ingroup PerceptronNetworkViewPlugin

//! \addtogroup PerceptronNetworkViewPlugin_imp
//! \{
class PerceptronNetworkViewPlugin : public QObject, IViewPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IViewPlugin)


public:
    PerceptronNetworkViewPlugin();
    ~PerceptronNetworkViewPlugin();

private:
    INeuralNetworkModel* myModel;
    MainForm *mainForm;

    // IPlugin interface
public:
    void OnAllSetup() override;
    QString GetLastError() override;

    // IViewPlugin interface
public:
    void SetModel(QObject *model) override;
    bool Open(QWidget *parent) override;
public slots:
    bool Close() override;
};

#endif // EMPTYMODULE_H
