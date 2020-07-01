#include "parentwindow.h"

#include <QMessageBox>
#include <QIcon>
#include <QApplication>

void ParentWindow::init()
{
	setWindowIcon(QIcon(QStringLiteral("://Resources/Logo256.png")));
	this->resize(540, 960);
}
