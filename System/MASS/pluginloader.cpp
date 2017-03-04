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
    //TODO: DT entry
#ifdef Q_OS_ANDROID
    QDir storageDirectoryPath("/storage/emulated/0/Android/data/" + packageName);
    if(!internalPluginsPath.exists())
    {
        internalPluginsPath.mkdir(internalPluginsPath.absolutePath());
    }
    qDebug() << "Paths" << storageDirectoryPath.absolutePath() << internalPluginsPath;
//    foreach (QString file, storageDirectoryPath.entryList(QDir::AllEntries))
//    {
//        qDebug() << file;
//    }

    QFile fileToCopy;
    QFile existingFile;
    foreach (QString file, storageDirectoryPath.entryList(QDir::Files))
    {
        // If internal file already exists - delete it
        existingFile.setFileName(internalPluginsPath.absolutePath() + "/" + file);
        if(existingFile.exists())
        {
            existingFile.remove();
        }

        // Copy storage file to internal storage
        QDir storagePluginPath(storageDirectoryPath.absolutePath() + "/" + file);
        fileToCopy.setFileName(storagePluginPath.absolutePath());
        fileToCopy.open(QIODevice::ReadOnly);
        fileToCopy.copy(internalPluginsPath.absolutePath() + "/" + file);
        fileToCopy.close();
        qDebug() << fileToCopy.remove();
        qDebug() << storagePluginPath.absolutePath() << fileToCopy.isOpen() << fileToCopy.errorString();
        qDebug() << internalPluginsPath.absolutePath() + file << fileToCopy.errorString();
        fileToCopy.close();
    }

    QApplication::addLibraryPath(internalPluginsPath.absolutePath());

    QDir path(internalPluginsPath);
    qDebug() << "Path" << path.absolutePath();
    foreach (QString file, path.entryList(QDir::Files))
    {
        qDebug() << file;
    }
#endif
}

void PluginLoader::SetupPlugins()
{
    LoadPluginsToHome();

    QDir libsDir(internalPluginsPath);
    qDebug() << "Path" << libsDir.absolutePath();
    QApplication::addLibraryPath(internalPluginsPath.absolutePath());
    foreach (QString file, libsDir.entryList(QDir::Files))
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
