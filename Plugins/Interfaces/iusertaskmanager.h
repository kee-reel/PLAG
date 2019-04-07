#ifndef ITASKLISTMODEL_H
#define ITASKLISTMODEL_H

#include <QtCore>

//!  \defgroup UserTaskManager UserTaskManager
//!      \ingroup Plugins
//! \defgroup UserTaskManager_int Interface
//!     \ingroup UserTaskManager
//! \defgroup UserTaskManager_imp Implementation
//!     \ingroup UserTaskManager
//!  \defgroup UserTaskManager_dep Dependent plugins
//!      \ingroup UserTaskManager

//! \addtogroup UserTaskManager_int
//!  \{
class IUserTaskManager
{
public:
    virtual QAbstractItemModel* GetTreeModel() = 0;

signals:
    void OpenTaskEdit(int id);
};
//!  \}
Q_DECLARE_INTERFACE(IUserTaskManager, "IUserTaskManager v0.1")
#endif // ITASKLISTMODEL_H
