#ifndef ITASKSKETCHMODEL_H
#define ITASKSKETCHMODEL_H

#include <QtCore>

//! \defgroup TaskSketchModel
//!     \ingroup MainMenuPlugin_rel_m
//! \defgroup TaskSketchModel_int Interface
//!     \ingroup TaskSketchModel
//! \defgroup TaskSketchModel_imp Implementation
//!     \ingroup TaskSketchModel

//! \addtogroup TaskSketchModel_int
//! \{
class ITaskSketchModel
{
public:
    virtual QAbstractItemModel* GetModel() = 0;
    virtual QAbstractItemModel* GetInternalModel() = 0;
    virtual void ConvertSketchToTask(int sketchId) = 0;
    virtual void LinkEditorWidget(QWidget*) = 0;
signals:
    void ConvertTaskToSketch(int);
};
//! \}
Q_DECLARE_INTERFACE(ITaskSketchModel, "ITaskSketchModel v0.1")
#endif // ITASKLISTMODEL_H
