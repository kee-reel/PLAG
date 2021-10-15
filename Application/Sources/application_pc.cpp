#include "application.h"

#ifndef IS_CLI_APP
#include <QMessageBox>
#include <QIcon>
#include <QApplication>
#endif

void Application::init()
{
#ifndef IS_CLI_APP
	setWindowIcon(QIcon(QStringLiteral("://Resources/Logo256.png")));
	this->resize(540, 960);
	show();
#endif
}
