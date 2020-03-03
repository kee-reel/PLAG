#include "parentwindow.h"

#include <QMessageBox>
#include <QIcon>
#include <QApplication>

void ParentWindow::init()
{
    setWindowIcon(QIcon(QStringLiteral("://Resources/Logo256.png")));
    layout = new QVBoxLayout(this);
    this->setLayout(layout);
    QScreen *screen = QApplication::primaryScreen();
//    this->resize(screen->size().width()/3, screen->size().height()/2);
	this->resize(540, 960);
}
