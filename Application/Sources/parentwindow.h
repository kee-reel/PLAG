#pragma once

#include <QWidget>
#include <QQuickItem>
#include <QQmlContext>
#include <QQuickWidget>

class PluginLoader;

//! \brief Main application widget class.
class ParentWindow : public QQuickWidget
{
	Q_OBJECT
public:
	explicit ParentWindow(QWidget *parent = nullptr);

	// QObject interface
protected:
	void childEvent(QChildEvent* event) override;

	// QWidget interface
protected:
	void resizeEvent(QResizeEvent* event) override;

public:
	void start();

private:
	void init();
	void resizeChildren(int w, int h);

private slots:
	void onUserAsk(const QString& question, const QVariantList& options);
	void onOptionChosen(int index);
	void onReadyToStart();
	void onStartFailed();

private:
	QSharedPointer<PluginLoader> m_pluginManager;
};

