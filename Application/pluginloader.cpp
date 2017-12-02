#include "pluginloader.h"

#include <QMessageBox>

PluginLoader::PluginLoader(QWidget* parent) : QObject(parent)
{
    this->parent = parent;
    corePlugin = NULL;
}

PluginLoader::~PluginLoader()
{
    QList<QObject*> keys = pluginInstances.keys();

    for(int i = 0; i < keys.count(); ++i)
        delete keys[i];
}

void PluginLoader::LoadPluginsToHome()
{
    qDebug() << QDir::homePath() << "===" << QDir::rootPath() << "===" << QDir::currentPath() << "===" << QDir::tempPath();
    internalPluginsPath = QDir(QString("%1/%2/")
                               .arg(QDir::currentPath())
                               .arg(pluginsSubdirName)
                              );
    QApplication::addLibraryPath(internalPluginsPath.absolutePath());
    qDebug() << "Library paths:" << QApplication::libraryPaths();
    //TODO: DT entry
#ifdef Q_OS_ANDROID
    QDir storageDirectoryPath("/storage/emulated/0/Android/data/" + packageName);

    if(!internalPluginsPath.exists())
        internalPluginsPath.mkdir(internalPluginsPath.absolutePath());

    qDebug() << "Storage:" << storageDirectoryPath.absolutePath() << endl << storageDirectoryPath.entryList(QDir::AllEntries);
    qDebug() << "Internal:" << internalPluginsPath.absolutePath() << endl << internalPluginsPath.entryList(QDir::AllEntries);
    LoadFilesFromDirectory(storageDirectoryPath, internalPluginsPath);

    foreach (QString dirPath, storageDirectoryPath.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        QDir subDir(storageDirectoryPath.absolutePath() + "/" + dirPath);
        QDir dstSubDir(internalPluginsPath.absolutePath() + "/" + dirPath);

        if(!dstSubDir.exists())
        {
            qDebug() << "Needs to create" << subDir.absolutePath();
            dstSubDir.mkdir(dstSubDir.absolutePath());
        }

        LoadFilesFromDirectory(subDir, dstSubDir);
    }

#endif
}

void PluginLoader::LoadFilesFromDirectory(QDir directory, QDir dstDirectory)
{
    qDebug() << "LoadFilesFromDirectory" << directory.absolutePath() << endl << directory.entryList(QDir::AllEntries);
    QFile fileToCopy;
    QFile existingFile;

    foreach (QString file, directory.entryList(QDir::Files))
    {
        qDebug() << "File" << file;
        // If internal file already exists - delete it
        existingFile.setFileName(dstDirectory.absolutePath() + "/" + file);

        if(existingFile.exists())
        {
            qDebug() << "Already exists. Overriding.";
            existingFile.remove();
        }

        // Copy storage file to internal storage
        QDir storagePluginPath(directory.absolutePath() + "/" + file);
        fileToCopy.setFileName(storagePluginPath.absolutePath());
        fileToCopy.open(QIODevice::ReadOnly);
        fileToCopy.copy(dstDirectory.absolutePath() + "/" + file);
        fileToCopy.close();
        //        qDebug() << fileToCopy.remove();
        //        qDebug() << storagePluginPath.absolutePath() << fileToCopy.isOpen() << fileToCopy.errorString();
        //        qDebug() << internalPluginsPath.absolutePath() + file << fileToCopy.errorString();
        fileToCopy.close();
    }
}

bool PluginLoader::SetupPlugins()
{
    LoadPluginsToHome();
    QDir libsDir(internalPluginsPath);
    qDebug() << "Path" << libsDir.absolutePath();
    QApplication::addLibraryPath(internalPluginsPath.absolutePath());

    foreach (QString file, libsDir.entryList(QDir::Files))
    {
        SetupPlugin(libsDir.absolutePath() + "/" + file);
    }

    return SetupPluginsConnections();
}

void PluginLoader::RunCorePlugin()
{
    QMap<QObject*, QJsonObject>::Iterator instancesIter = pluginInstances.begin();

    while(instancesIter != pluginInstances.end())
    {
        corePlugin->AddPlugin(instancesIter.key(), &instancesIter.value());
        ++instancesIter;
    }

    corePlugin->Run(parent);
}

bool PluginLoader::SetupPlugin(QString pluginName)
{
    qDebug() << endl << "=====" << pluginName << "=====";
    QPluginLoader* loader = LoadPlugin(pluginName);

    if(!loader)
        return false;

    QObject* possiblePlugin = GetPluginInstance(loader);

    if(!possiblePlugin)
        return false;

    BindPluginToSystem(possiblePlugin, loader);
    return true;
}

QPluginLoader *PluginLoader::LoadPlugin(QString pluginName)
{
    qDebug() << "Load plugin";

    if(!QLibrary::isLibrary(pluginName))
    {
        qDebug() << "Can't load the plugin" << pluginName << ": not a library file.";
        return NULL;
    }

    QPluginLoader* loader = new QPluginLoader(pluginName);

    if(!loader)
        qDebug() << "Load null.";

    return loader;
}

QObject* PluginLoader::GetPluginInstance(QPluginLoader* loader)
{
    qDebug() << "Get instance";
    QObject* possiblePlugin = loader->instance();

    if(!possiblePlugin)
        qDebug() << "Can't load the plugin" << loader->fileName() << ": not a plugin." << "Error:" + loader->errorString();

    return possiblePlugin;
}

void PluginLoader::BindPluginToSystem(QObject* instance, QPluginLoader* loader)
{
    qDebug() << "Bind plugin to system";
    ICorePlugin* plugin = CastToPlugin<ICorePlugin>(instance);

    if(plugin)
    {
        qDebug() << instance->metaObject()->className();
        corePlugins.insertMulti(instance->metaObject()->className(), plugin);
    }

    pluginInstances.insert(instance, loader->metaData());
}

bool PluginLoader::SetupPluginsConnections()
{
    qDebug() << "You have" << corePlugins.count() << "main plugins.";

    if(corePlugins.count() == 0)
    {
        QMessageBox messageBox;
        messageBox.setWindowTitle("Application will not run");
        messageBox.setText(QString("Can't find any core plugin in \"%1\" directory.")
                           .arg(internalPluginsPath.dirName()));
        messageBox.exec();
        return false;
    }
    else if(corePlugins.count() > 1)
    {
        QMessageBox messageBox;
        auto corePluginsNames = corePlugins.keys();
        messageBox.setWindowTitle("Choose");
        messageBox.setText(QString("There are several core plugins. Actually, this part of code doesn't implemented"
                                   ", so only one of them will be used (%1).").arg(corePluginsNames.first()));
        messageBox.exec();
    }

    corePlugin = corePlugins.first();
    return true;
}

template <class Type>
Type *PluginLoader::CastToPlugin(QObject* possiblePlugin)
{
    Type* plugin = qobject_cast<Type*>(possiblePlugin);

    if(!plugin)
    {
        qDebug() << "Can't load the plugin " << possiblePlugin->objectName() << ": wrong type.";
    }

    return plugin;
}
