#pragma once

#include <QtCore>
#include <QObject>

#ifndef IS_CLI_APP
#include <QWidget>
#include <QQuickItem>
#include <QQmlContext>
#include <QQuickWidget>
#endif

class PluginLoader;

class Application : 
#ifdef IS_CLI_APP
	public QObject
#else
	public QQuickWidget
#endif
{
	Q_OBJECT
public:
	explicit Application();

	// QObject interface
protected:
	void childEvent(QChildEvent* event) override;
	
#ifndef IS_CLI_APP
	// QWidget interface
protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	void resizeChildren(int w, int h);
#endif

public:
	void start();

private:
	void init();

private slots:
	void onUserAsk(const QString& question, const QVariantList& options);
	void onOptionChosen(int index);
	void onReadyToStart();
	void onStartFailed();

private:
	QSharedPointer<PluginLoader> m_pluginManager;
};

