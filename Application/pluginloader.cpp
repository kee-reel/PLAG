#include "pluginloader.h"

#include <QMessageBox>

#include "pluginhandler.h"

PluginLoader::PluginLoader(QWidget *parent) : QObject(parent)
{
    this->m_parent = parent;
    m_corePlugin = nullptr;
}

PluginLoader::~PluginLoader()
{
}

void PluginLoader::loadPluginsToHome()
{
    qDebug() << "PluginLoader::loadPluginsToHome: home path:" << QDir::homePath() << endl <<
             "PluginLoader::loadPluginsToHome: root path:" << QDir::rootPath() << endl <<
             "PluginLoader::loadPluginsToHome: current path:" << QDir::currentPath() << endl <<
             "PluginLoader::loadPluginsToHome: temp path:" << QDir::tempPath();
    m_internalPluginsPath = QDir(QString("%1/%2/").arg(QDir::currentPath()).arg(pluginsSubdirName));
    QApplication::addLibraryPath(m_internalPluginsPath.absolutePath());
    qDebug() << "PluginLoader::loadPluginsToHome: library paths:" << QApplication::libraryPaths();
    //TODO: DT entry
#ifdef Q_OS_ANDROID
    QDir storageDirectoryPath("/storage/emulated/0/Android/data/" + packageName);

    if(!internalPluginsPath.exists())
    {
        internalPluginsPath.mkdir(internalPluginsPath.absolutePath());
    }

    qDebug() << "Storage:" << storageDirectoryPath.absolutePath() << endl << storageDirectoryPath.entryList(
                 QDir::AllEntries);
    qDebug() << "Internal:" << internalPluginsPath.absolutePath() << endl << internalPluginsPath.entryList(
                 QDir::AllEntries);
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

void PluginLoader::loadFilesFromDirectory(QDir directory, QDir dstDirectory)
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

bool PluginLoader::setupPlugins()
{
    loadPluginsToHome();
    QDir libsDir(m_internalPluginsPath);
    qDebug() << "PluginLoader::setupPlugins: loading plugins by path:" << libsDir.absolutePath();
    QApplication::addLibraryPath(m_internalPluginsPath.absolutePath());

    foreach (QString file, libsDir.entryList(QDir::Files))
    {
        setupPlugin(libsDir.absolutePath() + "/" + file);
    }

    qDebug() << "PluginLoader::setupPlugins:" << m_corePluginHandlers.count() << "core plugins found, trying to load.";

    for(const auto& plugin : m_corePluginHandlers)
    {
        if(!plugin.data()->load())
        {
            continue;
        }

        auto instance = plugin.data()->getInstance();
        auto *corePluginPtr = castToPlugin<ICorePlugin>(instance);
        if(!corePluginPtr)
        {
            qDebug() << "PluginLoader::setupPlugins:" << m_corePluginHandlers.count() << "core plugins found, trying to load.";
            plugin.data()->unload();
            continue;
        }

        m_corePlugin = plugin;
        break;
    }

    bool isSetupSucceed = m_corePlugin != nullptr;
    if(!isSetupSucceed)
    {
        qDebug() << "PluginLoader::setupPlugins: no core plugins loaded, "
                 "application can't be started without core plugin.";
    }

    return isSetupSucceed;
}

void PluginLoader::runCorePlugin()
{
    assert(m_corePlugin);

    QVector<QWeakPointer<IPluginHandler>> pluginHandlers(m_pluginHandlers.size());
    for(int i = 0; i < m_pluginHandlers.size(); ++i)
    {
        pluginHandlers[i] = QWeakPointer<IPluginHandler>(m_pluginHandlers[i]);
    }

    qDebug() << "PluginLoader::runCorePlugin: starting core plugin." << endl;
    auto instance = m_corePlugin.data()->getInstance();
    auto *corePluginPtr = castToPlugin<ICorePlugin>(instance);
    corePluginPtr->addPlugins(pluginHandlers);
    corePluginPtr->start(m_corePlugin, m_parent);
}

bool PluginLoader::setupPlugin(QString pluginName)
{
    if(!QLibrary::isLibrary(pluginName))
    {
        qCritical() << QString("PluginLoader: can't load plugin '%1': not a library.").arg(pluginName);
        return false;
    }

    auto handler = new PluginHandler(pluginName);
    auto handlerInterface = QSharedPointer<IPluginHandler>(handler);

    if(handler->isCorePlugin())
    {
        m_corePluginHandlers.append(handlerInterface);
    }
    else
    {
        m_pluginHandlers.append(handlerInterface);
    }

    return true;
}

template <class Type>
Type *PluginLoader::castToPlugin(QObject *possiblePlugin)
{
    Type *plugin = qobject_cast<Type *>(possiblePlugin);

    if(!plugin)
    {
        qDebug() << "PluginLoader::castToPlugin: can't cast the plugin " << possiblePlugin->objectName() << ": wrong type.";
    }

    return plugin;
}
