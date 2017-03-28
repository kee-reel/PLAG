#ifndef MAINFORM_H
#define MAINFORM_H

#include <QDebug>
#include <QWidget>
#include <QPainter>
#include <QAbstractItemModel>
#include <QResizeEvent>

#include "../TaskSketchModel/itasksketchmodel.h"

namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();
    void SetModel(ITaskSketchModel *model);

private:
    Ui::MainForm *ui;
    ITaskSketchModel *myModel;

    void resizeEvent(QResizeEvent *event);

signals:
    void onClose();

};

#endif // MAINFORM_H
