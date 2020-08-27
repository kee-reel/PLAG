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

	// IApplication interface
public:
	QWidget *getParentWidget() override;
	const QVector<IPluginHandlerPtr> &getPlugins() override;
	IPluginHandlerPtr makePluginHandler(const QString &path) override;
	quint32 askUser(const QString& question, const QVariantList& options) override;

signals:
	void onUserAnswered(quint32 askId, quint16 optionIndex);

public:
	virtual void setup();
	void start(QWeakPointer<IApplication> app);
	bool stop();

signals:
	void userAsked(QString, QVariantList);
	void readyToStart();
	void startFailed();

public slots:
	void userAnswered(int optionIndex);

protected:
	bool initPlugins();

private slots:
	void onAnswered(quint32 askId, quint16 optionIndex);

private:
	void registerPlugin(const QSharedPointer<PluginHandler>& handler);
	template<class Type>
	Type *castToPlugin(QObject *possiblePlugin);

protected:
	struct UserAskData
	{
		quint32 askId;
		QString question;
		QVariantList options;
	};

	QWidget *m_parentWidget;
	QDir m_pluginsPath;
	QSharedPointer<PluginHandler> m_corePluginHandler;
	QSharedPointer<QPair<ICore*, quint32>> m_corePluginInstance;
	quint32 m_pluginUidGeneratorCounter;
	bool m_userAsked;
	QList<UserAskData> m_askQueue;
	quint32 m_askUidGeneratorCounter;
	quint32 m_internalAskId;

	QVector<QSharedPointer<PluginHandler>> m_pluginHandlers;
	QVector<IPluginHandlerPtr> m_rawPluginHandlers;
	QVector<QSharedPointer<PluginHandler>> m_corePluginHandlers;
};

