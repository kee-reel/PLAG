#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    image = QImage(size(), QImage::Format_RGB32);
    isPressed = false;
    image.fill(Qt::white);
    pen = QPen(QBrush(Qt::black), 3);
}

void PaintWidget::Clean()
{
    image.fill(Qt::white);
    repaint();
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "mousePressEvent";
    isPressed = true;
    mousePos = prevMousePos = event->pos();
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
    isPressed = false;
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(!isPressed) return;
    prevMousePos = mousePos;
    mousePos = event->pos();
    repaint();
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    if(isPressed)
    {
        painter.begin(&image);
        painter.setPen(pen);
        painter.drawLine(mousePos, prevMousePos);
        painter.end();
    }
    painter.begin(this);
    painter.drawImage(0, 0, image);
    painter.end();
}

void PaintWidget::resizeEvent(QResizeEvent *event)
{
    QImage newImage = image.scaled(event->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    if(!newImage.isNull())
        image = newImage;
}
