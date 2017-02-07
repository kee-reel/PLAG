#include "draggablebutton.h"

DraggableButton::DraggableButton(QWidget *parent) : QWidget(parent)
{

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
    p.end();
}

void DraggableButton::mouseMoveEvent( QMouseEvent* e ) {
    if( e->buttons() | Qt::LeftButton ) {
        setGeometry(
            pos().x() + ( e->x() - dx ),
            pos().y() + ( e->y() - dy ),
            width(),
            height()
        );
    }
}

void DraggableButton::mouseReleaseEvent(QMouseEvent *event)
{
    emit clicked();
}

void DraggableButton::mousePressEvent( QMouseEvent* e ) {
    if( e->button() == Qt::LeftButton ) {
        dx = e->x();
        dy = e->y();
    }
}
