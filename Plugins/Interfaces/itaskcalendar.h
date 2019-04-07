#ifndef ITASKCALENDAR_H
#define ITASKCALENDAR_H

#include <QtCore>

//!  \defgroup TaskCalendar TaskCalendar
//!      \ingroup Plugins
//!  \defgroup TaskCalendar_int Interface
//!      \ingroup TaskCalendar
//!  \defgroup TaskCalendar_imp Implementation
//!      \ingroup TaskCalendar
//!  \defgroup TaskCalendar_dep Dependent plugins
//!      \ingroup TaskCalendar

//!  \addtogroup TaskCalendar_int
//!  \{
class ITaskCalendar
{
public:
    virtual void LinkEditorWidget(QWidget*) = 0;

};
//!  \}
Q_DECLARE_INTERFACE(ITaskCalendar, "ITaskCalendar")
#endif // ITASKCALENDAR_H
