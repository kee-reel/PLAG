#ifndef ITASKLISTMODEL_H
#define ITASKLISTMODEL_H

#include <QtCore>

//! \defgroup TaskTreeModel
//!     \ingroup MainMenuPlugin_rel_m
//! \defgroup TaskTreeModel_int Interface
//!     \ingroup TaskTreeModel
//! \defgroup TaskTreeModel_imp Implementation
//!     \ingroup TaskTreeModel

//! \addtogroup TaskTreeModel_int
//! \{
class ITaskTreeModel
{
public:
    virtual QAbstractItemModel* GetTreeModel() = 0;

signals:
    void OpenTaskEdit(int id);
};
//! \}
Q_DECLARE_INTERFACE(ITaskTreeModel, "ITaskTreeModel v0.1")
#endif // ITASKLISTMODEL_H
