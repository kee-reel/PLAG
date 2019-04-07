#ifndef ITaskSketchManager_H
#define ITaskSketchManager_H

#include <QtCore>

//!  \defgroup TaskSketchManager TaskSketchManager
//!      \ingroup Plugins
//! \defgroup TaskSketchManager_int Interface
//!     \ingroup TaskSketchManager
//! \defgroup TaskSketchManager_imp Implementation
//!     \ingroup TaskSketchManager
//!  \defgroup TaskSketchManager_dep Dependent plugins
//!      \ingroup TaskSketchManager

//! \addtogroup TaskSketchManager_int
//!  \{
class ITaskSketchManager
{
public:
    virtual QAbstractItemModel* GetModel() = 0;
    virtual QAbstractItemModel* GetInternalModel() = 0;
    virtual void ConvertSketchToTask(int sketchId) = 0;
    virtual void LinkEditorWidget(QWidget*) = 0;
signals:
    void ConvertTaskToSketch(int);
};
//!  \}
Q_DECLARE_INTERFACE(ITaskSketchManager, "ITaskSketchManager v0.1")
#endif // ITASKLISTMODEL_H
