#include "pluginloader.h"

#include <QMessageBox>

#include "pluginhandler.h"

PluginLoader::PluginLoader(QWidget *parent) :
    QObject(parent),
    m_corePlugin(nullptr)
{
    this->m_parent = parent;
    m_corePluginHandler = nullptr;
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

    if(!m_internalPluginsPath.exists())
    {
        m_internalPluginsPath.mkdir(m_internalPluginsPath.absolutePath());
    }

    if(!storageDirectoryPath.exists())
    {
        storageDirectoryPath.mkdir(storageDirectoryPath.absolutePath());
    }

    qDebug() << "Storage:" << storageDirectoryPath.absolutePath() << endl << storageDirectoryPath.entryList(
                 QDir::AllEntries);
    qDebug() << "Internal:" << m_internalPluginsPath.absolutePath() << endl << m_internalPluginsPath.entryList(
                 QDir::AllEntries);
    loadFilesFromDirectory(storageDirectoryPath, m_internalPluginsPath);

    for(QString dirPath : storageDirectoryPath.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        QDir subDir(storageDirectoryPath.absolutePath() + "/" + dirPath);
        QDir dstSubDir(m_internalPluginsPath.absolutePath() + "/" + dirPath);

        if(!dstSubDir.exists())
        {
            qDebug() << "Needs to create" << subDir.absolutePath();
            dstSubDir.mkdir(dstSubDir.absolutePath());
        }

        loadFilesFromDirectory(subDir, dstSubDir);
    }

#endif
}

void PluginLoader::loadFilesFromDirectory(QDir directory, QDir dstDirectory)
{
    qDebug() << "LoadFilesFromDirectory" << directory.absolutePath() << endl << directory.entryList(QDir::Files);
    QFile fileToCopy;
    QFile existingFile;

    for(QString file : directory.entryList(QDir::Files))
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

        m_corePluginHandler = plugin;
        break;
    }

    bool isSetupSucceed = m_corePluginHandler != nullptr;
    if(!isSetupSucceed)
    {
        qDebug() << "PluginLoader::setupPlugins: no core plugins loaded, "
                 "application can't be started without core plugin.";
    }

    return isSetupSucceed;
}

void PluginLoader::runCorePlugin()
{
    assert(m_corePluginHandler);

    QVector<QWeakPointer<IPluginHandler>> pluginHandlers(m_pluginHandlers.size());
    for(int i = 0; i < m_pluginHandlers.size(); ++i)
    {
        pluginHandlers[i] = QWeakPointer<IPluginHandler>(m_pluginHandlers[i]);
    }

    qDebug() << "PluginLoader::runCorePlugin: starting core plugin." << endl;
    auto instance = m_corePluginHandler.data()->getInstance();
    m_corePlugin = castToPlugin<ICorePlugin>(instance);
    m_corePlugin->addPlugins(pluginHandlers);
    m_corePlugin->start(m_corePluginHandler, m_parent);
}

bool PluginLoader::closePlugins()
{
    return m_corePlugin->close();
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
