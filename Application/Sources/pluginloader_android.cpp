#include "pluginloader_android.h"

#include <QAndroidJniEnvironment>
#include <QMessageBox>
#include <QDesktopServices>

const QString PACKAGE_NAME = "com.mass";

PluginLoaderAndroid::PluginLoaderAndroid(QWidget *parentWidget) :
	PluginLoader(parentWidget),
	m_publicStorageDirectory("/storage/emulated/0/Android/data/" + PACKAGE_NAME)
{	
}

PluginLoaderAndroid::~PluginLoaderAndroid()
{
	
}

void PluginLoaderAndroid::setup()
{
	requestPermissions();
}

void PluginLoaderAndroid::requestPermissions()
{
	if(QtAndroid::androidSdkVersion() >= 23)
	{
		const QString PermissionID("android.permission.READ_EXTERNAL_STORAGE");
		if(QtAndroid::checkPermission(PermissionID) != QtAndroid::PermissionResult::Granted)
		{
			QMessageBox::information(m_parentWidget, "Confirmation", "This application consists entirely from plugins that you combine between each other. You need to grant storage permission to load these plugins.");
			QtAndroid::requestPermissions(QStringList() << PermissionID, std::bind(&PluginLoaderAndroid::requestPermissionsResults, this, std::placeholders::_1));
			return;
		}
	}
	onPermissionsChecked();
}

void PluginLoaderAndroid::requestPermissionsResults(const QtAndroid::PermissionResultMap &ResultMap)
{
	if(ResultMap["android.permission.READ_EXTERNAL_STORAGE"] == QtAndroid::PermissionResult::Granted)
		onPermissionsChecked();
	else
		emit startFailed();
}

void PluginLoaderAndroid::onPermissionsChecked()
{
	loadPluginsToAppDirectory(m_pluginsPath);
	
	if(initPlugins())
	{
		emit readyToStart();
	}
	else
	{
		int res = QMessageBox::question(m_parentWidget, "No plugins", 
										QString("No required plugins found in directory %1. Open wiki page with more information?")
										.arg(m_publicStorageDirectory.absolutePath()));
		if(res == QMessageBox::Yes)
		{
			QDesktopServices::openUrl(QUrl("https://gitlab.com/c4rb0n_un1t/MASS/wikis/home", QUrl::TolerantMode));
		}
		else
		{
			emit startFailed();
		}
	}
}

void PluginLoaderAndroid::loadFilesFromDirectory(QDir srcDirectory, QDir dstDirectory)
{
	//	qDebug() << "LoadFilesFromDirectory" << directory.absolutePath() << endl << directory.entryList(QDir::Files);
	QFile fileToCopy;
	
	for(QString file : srcDirectory.entryList(QDir::Files))
	{
		// If internal file already exists - delete it
		QFile targetFile(dstDirectory.absolutePath() + "/" + file);
		if(targetFile.exists())
		{
			qDebug() << "Already exists. Overriding.";
			targetFile.remove();
		}
		
		// Copy storage file to internal storage
		fileToCopy.setFileName(srcDirectory.absolutePath() + "/" + file);
		fileToCopy.open(QIODevice::ReadOnly);
		fileToCopy.copy(targetFile.fileName());
		fileToCopy.remove();
		fileToCopy.close();
		//        qDebug() << fileToCopy.remove();
		//        qDebug() << storagePluginPath.absolutePath() << fileToCopy.isOpen() << fileToCopy.errorString();
		//        qDebug() << internalPluginsPath.absolutePath() + file << fileToCopy.errorString();
	}
}

bool PluginLoaderAndroid::loadPluginsToAppDirectory(QDir pluginsPath)
{
	//	qDebug() << "PluginLoader::loadPluginsToHome: home path:" << QDir::homePath() << endl <<
	//				"root path:" << QDir::rootPath() << endl <<
	//				"current path:" << QDir::currentPath() << endl <<
	//				"temp path:" << QDir::tempPath();
	
	qDebug() << pluginsPath.mkpath(pluginsPath.absolutePath());
	QApplication::addLibraryPath(pluginsPath.absolutePath());
	//    qDebug() << "PluginLoader::loadPluginsToHome: library paths:" << QApplication::libraryPaths();
	//TODO: DT entry
	
	m_publicStorageDirectory.mkpath(m_publicStorageDirectory.absolutePath());
	
	//	qDebug() << "Storage:" << m_publicStorageDirectory.absolutePath() << endl << m_publicStorageDirectory.entryList(
	//					QDir::AllEntries);
	//	qDebug() << "Internal:" << pluginsPath.absolutePath() << endl << pluginsPath.entryList(
	//					QDir::AllEntries);
	
	loadFilesFromDirectory(m_publicStorageDirectory, pluginsPath);
	
	for(QString dirPath : m_publicStorageDirectory.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
	{
		QDir subDir(m_publicStorageDirectory.absolutePath() + "/" + dirPath);
		QDir dstSubDir(pluginsPath.absolutePath() + "/" + dirPath);
		
		dstSubDir.mkpath(dstSubDir.absolutePath());
		loadFilesFromDirectory(subDir, dstSubDir);
	}
	return true;
}

