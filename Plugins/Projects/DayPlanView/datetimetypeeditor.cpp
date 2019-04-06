#include "datetimetypeeditor.h"

DateTimeTypeEditor::DateTimeTypeEditor(QWidget *parent) : QDateTimeEdit(parent)
{
    setMinimumDate(QDate::currentDate().addDays(-365));
    setMaximumDate(QDate::currentDate().addDays(365));
    //setCalendarPopup(true);
}

QVariant DateTimeTypeEditor::value() const
{
    return QVariant(dateTime().toString((Qt::ISODate)));
}

void DateTimeTypeEditor::setValue(const QVariant value)
{
    if(!value.isValid())
        return;
    QDateTime dateTime;
    if(value.type() == QVariant::String)
        dateTime.fromString(value.toString(), Qt::ISODate);
    else
        dateTime = value.toDateTime();
    setDateTime(dateTime);
}

void DateTimeTypeEditor::keyPressEvent(QKeyEvent *event)
{
    QDateTimeEdit::keyPressEvent(event);
    auto calendar = calendarWidget();
    calendar->show();
}
