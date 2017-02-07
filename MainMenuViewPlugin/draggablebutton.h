#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>

class DraggableButton : public QWidget
{
    Q_OBJECT
public:
    explicit DraggableButton(QWidget *parent = 0);
private:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    int dx, dy;
    static const int borderShift = 4;

signals:
    void clicked();

public slots:
};

#endif // CUSTOMWIDGET_H
