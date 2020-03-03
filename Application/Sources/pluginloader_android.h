#pragma once


#include "pluginloader.h"

#include <QtAndroid>

class PluginLoaderAndroid : public PluginLoader
{
    Q_OBJECT
    
public:
    explicit PluginLoaderAndroid(QWidget *parentWidget);
    virtual ~PluginLoaderAndroid() override;

public:
    virtual void setup() override;
    
private:
	void loadFilesFromDirectory(QDir srcDirectory, QDir dstDirectory);
	bool loadPluginsToAppDirectory(QDir pluginsPath);
	
	void requestPermissions();
	void requestPermissionsResults(const QtAndroid::PermissionResultMap &ResultMap);
	
	void onPermissionsChecked();

private:
	QDir m_publicStorageDirectory;
};

