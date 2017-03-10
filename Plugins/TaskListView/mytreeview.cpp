#include "mytreeview.h"

MyTreeView::MyTreeView(QWidget *parent) : QTreeView(parent)
{
//    this->setSelectionMode(QAbstractItemView::SingleSelection);
//    this->setDragEnabled(true);
//    this->setAcceptDrops(true);
//    this->setAnimated(true);
//    this->setDragDropOverwriteMode(true);
//    this->viewport()->setAcceptDrops(true);
//    this->setExpandsOnDoubleClick(false);
//    this->setDragDropMode(QAbstractItemView::DragDrop);

    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setDragEnabled(true);
    setAcceptDrops(true);
    setDragDropMode(DragDrop);
    setDropIndicatorShown(true);
    setAnimated(true);
    setAutoScroll(true);
    setWordWrap(true);
    setAlternatingRowColors(true);
    setAutoScroll(true);
}

//void MyTreeView::dragMoveEvent(QDragMoveEvent* event)
//{
//    setDropIndicatorShown(true);
//    QTreeView::dragMoveEvent(event);
//}

//void MyTreeView::dropEvent(QDropEvent* event)
//{

//    bool dropOK = false;
//    DropIndicatorPosition dropIndicator = dropIndicatorPosition();
//    switch (dropIndicator)
//    {
//    case QAbstractItemView::AboveItem:
//        dropOK = true;
//        break;
//    case QAbstractItemView::BelowItem:
//        dropOK = true;
//        break;
//    case QAbstractItemView::OnItem:
//        dropOK = true;
//        break;
//    case QAbstractItemView::OnViewport:
//        dropOK = false;
//        break;
//    }
//    qDebug() << "dropEvent" << dropOK;
//    if(dropOK)
//    {
//        event->accept();
//        QTreeView::dropEvent(event);
//    }
//    setDropIndicatorShown(false);
//}
