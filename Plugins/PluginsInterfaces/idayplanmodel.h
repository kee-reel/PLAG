#ifndef IDAYPLANMODEL_H
#define IDAYPLANMODEL_H

#include <QtCore>

class QAbstractItemModel;

//! defgroup DayPlanModel_int Interface
//!     ingroup DayPlanModel
//! defgroup DayPlanModel_imp Implementation
//!     ingroup DayPlanModel

//! addtogroup DayPlanModel_int
//! {
class IDayPlanModel
{
public:
    virtual QAbstractItemModel* GetTaskModel() = 0;
    virtual QAbstractItemModel* GetDateModel() = 0;
    virtual void SetDataTypeEditor(QWidget *widget) = 0;
};
//! }
Q_DECLARE_INTERFACE(IDayPlanModel, "IDayPlanModel")
#endif // IDAYPLANMODEL_H
