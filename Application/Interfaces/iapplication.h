#pragma once

#include <QtGlobal>
#include <QObject>

#include "ipluginhandler.h"

class IApplication
{
public:
	virtual QWidget* getParentWidget() = 0;

	virtual const QVector<IPluginHandlerPtr> &getPlugins() = 0;

	virtual IPluginHandlerPtr makePluginHandler(const QString &path) = 0;

	virtual QStringList getCommandLineArguments() = 0;

	virtual quint32 askUser(const QString& question, const QVariantList& options) = 0;

signals:
	void onUserAnswered(quint32 askId, quint16 optionIndex);

protected:
	virtual ~IApplication() = default;
};
Q_DECLARE_INTERFACE(IApplication, "IApplication/1.0")
