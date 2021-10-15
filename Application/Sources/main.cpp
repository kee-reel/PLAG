#include "application.h"
#ifndef IS_CLI_APP
#include <QApplication>
#else
#include <QCoreApplication>
#endif

int main(int argc, char *argv[])
{
#ifndef IS_CLI_APP
	QApplication qtApp(argc, argv);
#else
	QCoreApplication qtApp(argc, argv);
#endif
	Application app;
	app.start();
	return qtApp.exec();
}
