#include "mytreeview.h"

MyTreeView::MyTreeView(QWidget *parent) : QTreeView(parent)
{
    setAnimated(true);
    setWordWrap(true);
    setAutoScroll(true);
    setDragEnabled(true);
    setAcceptDrops(true);
    setHeaderHidden(true);
    setAutoExpandDelay(1000);
    setDragDropMode(DragDrop);
    setDropIndicatorShown(true);
    setAlternatingRowColors(true);
    setDragDropOverwriteMode(false);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::ExtendedSelection);


    QScroller::grabGesture(viewport(), QScroller::TouchGesture);
#ifdef Q_OS_ANDROID
    setFocusPolicy(Qt::NoFocus);
    QScroller::grabGesture(viewport(), QScroller::Dragging);
#else
    setFocusPolicy(Qt::StrongFocus);
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
