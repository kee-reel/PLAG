#pragma once


#include <QApplication>
#include <QDebug>
#include <QString>
#include <QWidget>
#include <QObject>
#include <QPluginLoader>
#include <QDir>
#include <QStandardPaths>
#include <QtSql>

#include "../Interfaces/iapplication.h"
#include "../Interfaces/icore.h"
#include "../Interfaces/ipluginhandler.h"

class PluginHandler;

//! \brief Loads all files from directory and tries to specify
//! between them plugin with interface RootModel and initialize it.
class PluginLoader : public QObject, public IApplication
{
	Q_OBJECT
	Q_INTERFACES(IApplication)
	
public:
	explicit PluginLoader(QWidget *parentWidget);
	
public:
	virtual void setup();
	void start(QWeakPointer<IApplication> app);
	bool stop();
	
Q_SIGNALS:
	void readyToStart();
	void startFailed();
	
	// IApplication interface
public:
	QWidget *getParentWidget() override;
	const QVector<IPluginHandlerPtr> &getPlugins() override;
	IPluginHandlerPtr makePluginHandler(const QString &path) override;
	
protected:
	bool initPlugins();
	
private:
	void registerPlugin(const QSharedPointer<PluginHandler>& handler);
	template<class Type>
	Type *castToPlugin(QObject *possiblePlugin);
	
private:
	QWidget *m_parentWidget;
	QDir m_pluginsPath;
	QSharedPointer<PluginHandler> m_corePluginHandler;
	ICore* m_corePluginInstance;
	quint32 m_uidGeneratorCounter;
	
	QVector<QSharedPointer<PluginHandler>> m_pluginHandlers;
	QVector<IPluginHandlerPtr> m_rawPluginHandlers;
	QVector<QSharedPointer<PluginHandler>> m_corePluginHandlers;
};

