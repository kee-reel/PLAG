#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QImage>
#include <QPicture>
#include <QWidget>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QBuffer>

class PaintWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QVariant value READ value WRITE setValue)

public:
    explicit PaintWidget(QWidget *parent = 0);
    QVariant value() const;
    void setValue(const QVariant value);
private:
    QImage image;
    bool isPressed;
    bool isDefaultCanvasChanged;
    QPoint mousePos, prevMousePos;
    QPen pen;

public slots:
    void Clean();

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);

};
#endif // PAINTWIDGET_H
