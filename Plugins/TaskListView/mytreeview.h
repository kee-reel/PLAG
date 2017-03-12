#ifndef MYTREEVIEW_H
#define MYTREEVIEW_H

#include <QDebug>
#include <QTreeView>
#include <QScroller>
#include <QDropEvent>
#include <QMouseEvent>
#include <QDragMoveEvent>

class MyTreeView : public QTreeView
{
public:
    MyTreeView(QWidget *parent);

protected:
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;


private:

};

#endif // MYTREEVIEW_H
