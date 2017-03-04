#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QApplication>
#include <QDebug>
#include <QString>
#include <QWidget>
#include <QObject>
#include <QPluginLoader>
#include <QDir>
#include <QStandardPaths>
#include <QtSql>

#include "rootinterface.h"

class PluginLoader : QObject
{
    Q_OBJECT
    QString packageName = "com.MASS";
public:
    explicit PluginLoader(QWidget *parent = 0);
    ~PluginLoader();

private:
    QWidget* parent;
    IRootModelPlugin* rootModel;

    QList<IRootModelPlugin*> rootModes;
    QMap<QObject*, QJsonObject> pluginInstances;

    QDir internalPluginsPath;

    void LoadPluginsToHome();
    bool SetupPlugin(QString pluginName);
    QPluginLoader* LoadPlugin(QString pluginName);
    QObject* GetPluginInstance(QPluginLoader* loader);   
    void BindPluginToSystem(QObject* instance, QPluginLoader* loader);

    template<class Type>
    Type *CastToPlugin(QObject* possiblePlugin);

    void SetupPluginsConnections();

public slots:
    void SetupPlugins();
};

#endif // PLUGINMANAGER_H
