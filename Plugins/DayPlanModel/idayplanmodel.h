#ifndef IDAYPLANMODEL_H
#define IDAYPLANMODEL_H

#include "../MainMenuModelPlugin/interfaces.h"

class QAbstractItemModel;

//! defgroup DayPlanModel
//!     ingroup MainMenuPlugin_rel_m
//! defgroup DayPlanModel_int Interface
//!     ingroup DayPlanModel
//! defgroup DayPlanModel_imp Implementation
//!     ingroup DayPlanModel

//! addtogroup DayPlanModel_int
//! {
class IDayPlanModel :
        public IModelPlugin
{
public:
    virtual QAbstractItemModel* GetModel() = 0;
    virtual void SetDataTypeEditor(QWidget *widget) = 0;
};
//! }
Q_DECLARE_INTERFACE(IDayPlanModel, "IDayPlanModel")
#endif // IDAYPLANMODEL_H
