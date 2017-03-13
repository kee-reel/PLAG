#include "mytreeview.h"

MyTreeView::MyTreeView(QWidget *parent) : QTreeView(parent)
{
    setAnimated(true);
    setWordWrap(true);
    setAutoScroll(true);
    setHeaderHidden(true);
    setDropIndicatorShown(true);
    setAlternatingRowColors(true);
    setExpandsOnDoubleClick(true);
    setDragDropOverwriteMode(false);

    setIndentation(40);
    setAutoExpandDelay(1000);

    setDragDropMode(DragDrop);
    setVerticalScrollMode(ScrollPerPixel);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::ExtendedSelection);

#ifdef Q_OS_ANDROID
    setDragEnabled(false);
    setAcceptDrops(false);
    setFocusPolicy(Qt::NoFocus);
    viewport()->installEventFilter(this);
    viewport()->grabGesture(Qt::TapAndHoldGesture);
    QScroller::grabGesture(viewport(), QScroller::LeftMouseButtonGesture);
#else
    setFocusPolicy(Qt::StrongFocus);
    setDragEnabled(true);
    setAcceptDrops(true);
#endif
}

void MyTreeView::dragMoveEvent(QDragMoveEvent* event)
{
    qDebug() << "dragMoveEvent" << event->type();
    QTreeView::dragMoveEvent(event);
}

void MyTreeView::dropEvent(QDropEvent* event)
{
    selectionModel()->clearSelection();
    QTreeView::dropEvent(event);
}

bool MyTreeView::eventFilter(QObject *obj, QEvent *event)
{
    switch(event->type())
    {
        case QEvent::Gesture:{
            QGestureEvent *gestevent = static_cast<QGestureEvent *>(event);
            if (QGesture *gest = gestevent->gesture(Qt::TapAndHoldGesture)){
                QTapAndHoldGesture *tapgest = static_cast<QTapAndHoldGesture *>(gestevent->gesture(Qt::TapAndHoldGesture));
                setDragEnabled(true);
                setAcceptDrops(true);
                qDebug() << "GRABBED";
                return true;
            }
        }
        break;

//    case QEvent::MouseButtonPress:
//        if(obj == viewport())
//            return true;
//       break;

        case QEvent::Drop:
        case QEvent::MouseButtonRelease:
            setDragEnabled(false);
            setAcceptDrops(false);
            qDebug() << "DROPPED";
        break;
    }
    qDebug() << "grabbed an event" << event->type();
    // standard event processing
    return QTreeView::eventFilter(obj, event); // Parent being MyClass parent type, maybe QDialog or QWidget
}
