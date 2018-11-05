#include "uniquepushbutton.h"

UniquePushButton::UniquePushButton(int id, QString name, QWidget *parent) : QPushButton(parent)
{
    this->m_id = id;
    setText(name);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setFocusPolicy(Qt::NoFocus);
}

int UniquePushButton::getId()
{
    return m_id;
}

void UniquePushButton::mouseReleaseEvent(QMouseEvent *event)
{
    emit OnMenuItemSelected(this);
    QPushButton::mouseReleaseEvent(event);
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
