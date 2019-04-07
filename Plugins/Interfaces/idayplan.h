#ifndef IDayPlan_H
#define IDayPlan_H

#include <QtCore>

class QAbstractItemModel;

//!  \defgroup DayPlan DayPlan
//!      \ingroup Plugins
//!  \defgroup DayPlan_int Interface
//!      \ingroup DayPlan
//!  \defgroup DayPlan_imp Implementation
//!      \ingroup DayPlan
//!  \defgroup DayPlan_dep Dependent plugins
//!      \ingroup DayPlan

//!  \addtogroup DayPlan_int
//!  \{
class IDayPlan
{
public:
    virtual QAbstractItemModel* GetTaskModel() = 0;
    virtual QAbstractItemModel* GetDateModel() = 0;
    virtual void SetDataTypeEditor(QWidget *widget) = 0;
};
//!  \}
Q_DECLARE_INTERFACE(IDayPlan, "IDayPlan")
#endif // IDayPlan_H
