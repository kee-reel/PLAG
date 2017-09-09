#include "widgetstack.h"

WidgetStack::WidgetStack(QWidget *parent) : QObject(parent)
{
    parent->installEventFilter(this);
    parent->layout()->setMargin(0);
}

void WidgetStack::Pop()
{
    qDebug() << "Pop" << widgetStack.last()->objectName();
    if(Count() != 1)
    {
        widgetStack.last()->setVisible(false);
        widgetStack.removeLast();
        widgetStack.last()->setVisible(true);
    }
    else
    {
       QApplication::exit();
    }
}

void WidgetStack::Push(QWidget *widget)
{
    qDebug() << "Push" << widget->objectName();
    if(Count() != 0)
    {
        auto last = widgetStack.last();
        last->setVisible(false);
    }
    widgetStack.append(widget);
    QWidget *parentWidget = qobject_cast<QWidget*>(parent());
    widget->setParent(parentWidget);
    parentWidget->layout()->addWidget(widget);
    widget->installEventFilter(this);
    widget->setVisible(true);
}

int WidgetStack::Count()
{
    return widgetStack.length();
}

QWidget *WidgetStack::GetTop()
{
    return widgetStack.last();
}

bool WidgetStack::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::KeyRelease)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if(keyEvent->key() == Qt::Key_Back)
        {
            Pop();
            return true;
        }
    }
    return QObject::eventFilter(watched, event);
}
