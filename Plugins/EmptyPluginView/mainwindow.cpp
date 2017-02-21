#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter p;
    p.begin(this);

    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(QPen(QColor(Qt::black), 5));
    p.drawRect(rect());

    QFont m_font;
    m_font.setBold(true);

    p.setFont(QFont("Arial", 9));
    p.drawText(rect(), Qt::AlignCenter, "EmptyPlugin");

    p.end();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    emit onClose();
}
