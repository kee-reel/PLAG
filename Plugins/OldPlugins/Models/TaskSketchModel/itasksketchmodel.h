#ifndef ITASKSKETCHMODEL_H
#define ITASKSKETCHMODEL_H

#include "../../interfaces.h"

template <class A>
class QVector;
class QAbstractItemModel;

//! \defgroup TaskSketchModel
//!     \ingroup MainMenuPlugin_rel_m
//! \defgroup TaskSketchModel_int Interface
//!     \ingroup TaskSketchModel
//! \defgroup TaskSketchModel_imp Implementation
//!     \ingroup TaskSketchModel

//! \addtogroup TaskSketchModel_int
//! \{
class ITaskSketchModel: public IModelPlugin
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
