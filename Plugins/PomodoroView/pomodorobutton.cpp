#include "pomodorobutton.h"

PomodoroButton::PomodoroButton(QWidget *parent) :
    QWidget(parent)
{
    qDebug() << "========================Init";
    timer = new QTimer(this);
    timer->setInterval(1000);
    timer->setSingleShot(false);
    timer->setTimerType(Qt::VeryCoarseTimer);
    connect(timer, SIGNAL(timeout()), SLOT(TimerTick()));
    secsTarget = 25;
}

PomodoroButton::~PomodoroButton()
{
    delete timer;
}

void PomodoroButton::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "Press";
    if(!timer->isActive())
    {
        secsPassed = 0;
        repaint();
        timer->start();
    }
    else
    {
        timer->stop();
    }
}

void PomodoroButton::paintEvent(QPaintEvent *event)
{
    QPainter p;
    p.begin(this);
    p.setRenderHint(QPainter::Antialiasing);
    QBrush brush(Qt::black);
    QPen pen(brush, 3);
    p.setBrush(brush);
    p.setPen(pen);

    QRect aspectRect;
    int padding = 3;
    aspectRect.setX(padding);
    aspectRect.setY(padding);
    float newAspect = width() / (float)height();
    if(newAspect < 1)
    {
        aspectRect.setWidth(height());
        aspectRect.setHeight(height());
    }
    else
    {
        aspectRect.setWidth(width());
        aspectRect.setHeight(width());
    }
    aspectRect.setWidth(width()-2*padding);
    aspectRect.setHeight(width()-2*padding);

    int angle = 360 * (secsPassed / (float)secsTarget) * 16;

    int startAngle = 90 * 16;
    p.drawPie(aspectRect, startAngle, -angle);

    p.end();
}

void PomodoroButton::TimerTick()
{
    secsPassed++;
    repaint();
    if(secsPassed >= secsTarget)
    {
        timer->stop();
        emit PomodoroFinished();
    }
}
