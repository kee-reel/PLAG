#ifndef ADDFORM_H
#define ADDFORM_H

#include <QDebug>
#include <QWidget>
#include <QDataWidgetMapper>
#include <QAbstractItemModel>
#include <QKeyEvent>
#include <QMap>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>

namespace Ui {
class AddForm;
}
//! \addtogroup TaskListView_imp
//! \{
class AddForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddForm(QWidget *parent = 0);
    ~AddForm();

    void SetModel(QAbstractItemModel *model);
    void ShowModelData(const QModelIndex &index, bool isNew = false);

signals:
    void OnClose();

private:
    Ui::AddForm *ui;
//    QDataWidgetMapper *mapper;
    QList<QLabel*> labelsList;
    QList<QLineEdit*> lineEdits;
    QAbstractItemModel *model;
    QGridLayout *gridLayout;
    QMap<QString, QVariant> currentItemMap;
    QModelIndex currentModelIndex;

    void ClearEditors();

private slots:
    void AcceptChanges();
    void CancelChanges();

    // QObject interface
public:
    bool event(QEvent *event) override;
};
//! \}
#endif // ADDFORM_H
