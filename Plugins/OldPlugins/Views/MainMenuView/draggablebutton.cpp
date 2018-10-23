#include "draggablebutton.h"

DraggableButton::DraggableButton(QWidget *parent, int id, QString buttonName) : QWidget(parent)
{
    this->id = id;
    this->buttonName = buttonName;
    isPressed = false;
}

void DraggableButton::paintEvent(QPaintEvent *)
{
    QPainter p;
    p.begin(this);

    p.setRenderHint(QPainter::Antialiasing);

    QFont m_font;
    m_font.setBold(true);
    p.setPen(QPen(QColor(Qt::black), 2));
    p.drawEllipse(borderShift/2, borderShift/2, width()-borderShift, height()-borderShift);
    p.setFont(QFont("Arial", width()/15));
    p.drawText(rect(), Qt::AlignCenter, buttonName);

    p.end();
}

void DraggableButton::mouseMoveEvent( QMouseEvent* e ) {
    if( e->buttons() | Qt::LeftButton ) {
        dx = ( e->x() - startX );
        dy = ( e->y() - startY );
        mouseShiftBuf += dx + dy;
        setGeometry(
            pos().x() + dx,
            pos().y() + dy,
            width(),
            height()
        );
    }
}

void DraggableButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(mouseShiftBuf <= pixelsShiftToClick)
        emit OnClicked(id);
    isPressed = false;
    qDebug() << "Released!";
}

void DraggableButton::mousePressEvent( QMouseEvent* e ) {
    if( e->button() == Qt::LeftButton && !isPressed ) {
        mouseShiftBuf = 0;
        isPressed = true;
        qDebug() << "Pressed!";
        startX = e->x();
        startY = e->y();
    }
}
