#include "application.h"

#ifndef IS_CLI_APP
#include <QMessageBox>
#include <QIcon>
#include <QApplication>
#endif

void Application::init()
{
#if defined(_WIN32) || defined(WIN32)
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);
#endif

#ifndef IS_CLI_APP
	setWindowIcon(QIcon(QStringLiteral("://Resources/Logo256.png")));
	this->resize(540, 960);
	show();
#endif
}
