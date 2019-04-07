#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    image = QImage(size(), QImage::Format_RGB32);
    isPressed = false;
    image.fill(Qt::white);
    pen = QPen(QBrush(Qt::black), 3);
}

QVariant PaintWidget::value() const
{
    QByteArray ba;
    if(isDefaultCanvasChanged)
    {
        QBuffer buffer(&ba);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "PNG");
        buffer.close();
    }
    return QVariant(ba);
}

void PaintWidget::setValue(const QVariant value)
{
    if(!value.isValid() || value.type() != QVariant::ByteArray)
    {
        Clean();
        isDefaultCanvasChanged = false;
        return;
    }

    QByteArray array = value.toByteArray();
    if(array.length() == 0)
    {
        image = QImage(size(), QImage::Format_RGB32);
        image.fill(Qt::white);
        isDefaultCanvasChanged = false;
    }
    else
    {
        image.loadFromData(value.toByteArray());
        isDefaultCanvasChanged = true;
    }
}

void PaintWidget::Clean()
{
    image.fill(Qt::white);
    repaint();
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    isPressed = true;
    isDefaultCanvasChanged = true;
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
