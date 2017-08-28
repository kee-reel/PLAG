#include "menuitem.h"

MenuItem::MenuItem(int id, QString name, QWidget *parent) : QPushButton(parent)
{
    this->id = id;
    setText(name);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

void MenuItem::mouseReleaseEvent(QMouseEvent *event)
{
    emit OnMenuItemSelected(id);
}

//void MenuItem::resizeEvent(QResizeEvent *event)
//{
//    auto newSize = event->size();
//    float size = (newSize.width() > newSize.height()) ? newSize.width() : newSize.height();
//    newSize.setWidth(size);
//    newSize.setHeight(size);
//    setMinimumSize(newSize);
//    setMaximumSize(newSize);
//    auto changedEvent = QResizeEvent(event->oldSize(), newSize);
//    QPushButton::resizeEvent(&changedEvent);
//}
