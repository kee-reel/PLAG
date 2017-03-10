#ifndef MYTREEVIEW_H
#define MYTREEVIEW_H

#include <QDebug>
#include <QTreeView>
#include <QDropEvent>
#include <QDragMoveEvent>

class MyTreeView : public QTreeView
{
public:
    MyTreeView(QWidget *parent);

    // QWidget interface
//protected:
//    void dragMoveEvent(QDragMoveEvent *event) override;
//    void dropEvent(QDropEvent *event) override;
};

#endif // MYTREEVIEW_H
