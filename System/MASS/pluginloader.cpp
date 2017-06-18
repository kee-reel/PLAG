#include "pluginloader.h"

PluginLoader::PluginLoader(QWidget* parent) : QObject(parent)
{
    this->parent = parent;
    rootModel = NULL;
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
    internalPluginsPath = QDir(QDir::currentPath() + "/Modules/");
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

void PluginLoader::SetupPlugins()
{
    LoadPluginsToHome();

    QDir libsDir(internalPluginsPath);
    qDebug() << "Path" << libsDir.absolutePath();
    QApplication::addLibraryPath(internalPluginsPath.absolutePath());
    foreach (QString file, libsDir.entryList(QDir::AllEntries))
    {
        SetupPlugin(libsDir.absolutePath() + "/" + file);
    }
    SetupPluginsConnections();
    qDebug() << "Everything done." << endl;
}

bool PluginLoader::SetupPlugin(QString pluginName)
{
    qDebug() << endl << "=====" << pluginName << "=====";
    QPluginLoader* loader = LoadPlugin(pluginName);
    if(!loader) return false;

    QObject* possiblePlugin = GetPluginInstance(loader);
    if(!possiblePlugin) return false;

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
    IRootModelPlugin* plugin = CastToPlugin<IRootModelPlugin>(instance);
    if(plugin)
    {
        qDebug() << instance->metaObject()->className();
        rootModes.append(plugin);
    }
    pluginInstances.insert(instance, loader->metaData());
}

void PluginLoader::SetupPluginsConnections()
{
    qDebug() << "Setup connections";
    qDebug() << "You have" << rootModes.count() << "main plugins.";
    if(rootModes.count() == 1)
        rootModel = rootModes.first();
    else
        return;

    QMap<QObject*, QJsonObject>::Iterator instancesIter = pluginInstances.begin();
    while(instancesIter != pluginInstances.end()){
        rootModel->AddPlugin(instancesIter.key(), &instancesIter.value());
        ++instancesIter;
    }

    rootModel->Open(parent);

    qDebug() << "-----Linking finished-----" << endl;
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
