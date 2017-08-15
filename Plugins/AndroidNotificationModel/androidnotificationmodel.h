#ifndef ANDROIDNOTIFICATIONMODEL_H
#define ANDROIDNOTIFICATIONMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "iandroidnotificationmodel.h"
#include "notificationclient.h"

//! addtogroup AndroidNotificationModel_imp
//! {
class AndroidNotificationModel : public QObject, IAndroidNotificationModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
            IModelPlugin
            IAndroidNotificationModel
            )

public:
    AndroidNotificationModel();
    ~AndroidNotificationModel();

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

    // IModelPlugin interface
public slots:
    bool Open(IModelPlugin *model, QWidget *modelWidget) override;
    void Close() override;

    // IAndroidNotificationModel interface
public:
    void PushNotification(QString title, QString message) override;

private:
    QWidget *referenceWidget;
    PluginInfo *pluginInfo;

    PluginInfo *openedModel;
    QList< PluginInfo* > relatedModelPlugins;
    PluginInfo *openedView;
    QList< PluginInfo* > relatedViewPlugins;

    NotificationClient *notificationClient;

private:
    // Write your internal methods here
};
//! }
#endif // ANDROIDNOTIFICATIONMODEL_H
