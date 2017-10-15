#ifndef EMPTYMODULE_H
#define EMPTYMODULE_H

#include <QLayout>
#include <QObject>
#include <QDebug>

#include "../../interfaces.h"
#include "../../Models/NeuralNetworkModel/ineuralnetworkmodel.h"

#include "mainform.h"

//! \defgroup ARNeuralNetworkView
//!     \ingroup MainMenuPlugin_rel_v
//! \defgroup ARNeuralNetworkView_imp Implementation
//!     \ingroup ARNeuralNetworkView

//! \addtogroup ARNeuralNetworkView_imp
//! \{
class ARNeuralNetworkView : public QObject, IViewPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IViewPlugin)

public:
    ARNeuralNetworkView();
    ~ARNeuralNetworkView();

private:
    INeuralNetworkModel* myModel;
    MainForm *mainForm;

    // IPlugin interface
public:
    void OnAllSetup() override;
    QString GetLastError() override;

    // IViewPlugin interface
public:
    void AddModel(QObject *model) override;
    bool Open(QWidget *parent) override;
public slots:
    bool Close() override;
};
//! \}
#endif // EMPTYMODULE_H
