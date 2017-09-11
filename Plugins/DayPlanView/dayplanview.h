#ifndef DAYPLANVIEW_H
#define DAYPLANVIEW_H

#include <QWidget>
#include <QDebug>
#include <QString>
#include <QAbstractItemModel>

#include "idayplanview.h"
#include "../DayPlanModel/idayplanmodel.h"

namespace Ui {
class Form;
}

//! addtogroup DayPlanView_imp
//! {
class DayPlanView : public QWidget, IDayPlanView
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
            IViewPlugin
            IDayPlanView
            )

public:
    explicit DayPlanView(QWidget *parent = 0);
    ~DayPlanView();

    // IPlugin interface
public:
    void SetPluginInfo(PluginInfo *pluginInfo) override;
    void OnAllSetup() override;
    QString GetLastError() override;
    void AddReferencePlugin(PluginInfo *pluginInfo) override;

public slots:
    void ReferencePluginClosed(PluginInfo *pluginInfo) override;

signals:
    void OnClose(PluginInfo*);
    void OnClose();

    // IViewPlugin interface
public slots:
    bool Open(IModelPlugin *model) override;
    bool Close() override;

signals:
    void OnOpen(QWidget *);

private:
    QWidget *referenceWidget;
    PluginInfo *pluginInfo;

    PluginInfo *openedModel;
    QList< PluginInfo* > relatedModelPlugins;
    PluginInfo *openedView;
    QList< PluginInfo* > relatedViewPlugins;

private:
    Ui::Form *ui;
    IDayPlanModel *dayPlanModel;
    QAbstractItemModel * itemModel;
};
//! }
#endif // DAYPLANVIEW_H
