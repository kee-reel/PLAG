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

    setStyleSheet(
    "QTreeView::item:selected{                                                                          "
    "    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #D9E5E6, stop: 1 #C4D0D0);     "
    "}                                                                                                  "
    );

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
    qDebug() << "dragMoveEvent";
    QTreeView::dragMoveEvent(event);
}

void MyTreeView::dropEvent(QDropEvent* event)
{
    selectionModel()->clearSelection();
    QTreeView::dropEvent(event);
}

// For Android drag and drop handling
bool MyTreeView::eventFilter(QObject *obj, QEvent *event)
{
    switch(event->type())
    {
        case QEvent::Gesture:{
            QGestureEvent *gestevent = static_cast<QGestureEvent *>(event);
            if (gestevent->gesture(Qt::TapAndHoldGesture)){
                setDragEnabled(true);
                setAcceptDrops(true);
                qDebug() << "GRABBED";
                setStyleSheet(
                "QTreeView::item:selected{                                                                         "
                "    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #7C8282, stop: 1 #C9D3D3);    "
                "}                                                                                                 "
                );
                return true;
            }
        }
        break;

        case QEvent::Drop:
        case QEvent::MouseButtonRelease:
            setDragEnabled(false);
            setAcceptDrops(false);
            qDebug() << "DROPPED";
            setStyleSheet(
            "QTreeView::item:selected{                                                                         "
            "    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #D9E5E6, stop: 1 #C4D0D0);    "
            "}                                                                                                 "
            );
        break;
    }
    // standard event processing
    return QTreeView::eventFilter(obj, event); // Parent being MyClass parent type, maybe QDialog or QWidget
}
