#include "parentwindow.h"

ParentWindow::ParentWindow(QWidget *parent) : QWidget(parent)
{
    pluginManager = new PluginManager(this);
    QScreen *screen = QApplication::screens().at(0);
    this->resize(screen->size().width(),
        screen->size().height());

    pluginManager->SetupPlugins();
}

void ParentWindow::paintEvent(QPaintEvent *)
{
    QPainter p;
    p.begin(this);

    p.setRenderHint(QPainter::Antialiasing);

    QFont m_font;
    m_font.setBold(true);

    p.setPen(QPen(QColor(Qt::black), 2));
    QString s = "";
    foreach (QString libPath, QApplication::libraryPaths())
    {
        QDir path(libPath);
        s += libPath + '\n';
        foreach (QString file, path.entryList(QDir::Files))
        {
            s += file + '\n';
        }
    }
    s += "/data/app/" + '\n';
    QDir path("/data/app/");
    foreach (QString file, path.entryList(QDir::Files))
    {
        s += file + '\n';
    }

    p.setFont(QFont("Arial", 9));
    p.drawText(rect(), Qt::AlignCenter, s);

    p.end();
}
