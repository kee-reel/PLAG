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
    explicit DraggableButton(QWidget *parent = 0, int id = 0, QString buttonName = "");

    int id;
    QString buttonName;
private:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    int startX, startY, dx, dy, mouseShiftBuf;
    bool isPressed;
    static const int borderShift = 4;
    static const int pixelsShiftToClick = 0;
signals:
    void OnClicked(int);

public slots:
};

#endif // CUSTOMWIDGET_H
