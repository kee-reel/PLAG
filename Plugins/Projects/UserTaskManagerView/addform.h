#ifndef ADDFORM_H
#define ADDFORM_H

#include <QDebug>
#include <QWidget>
#include <QDataWidgetMapper>
#include <QAbstractItemModel>
#include <QKeyEvent>
#include <QMap>
#include <QGridLayout>

namespace Ui {
class AddForm;
}

class AddForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddForm(QWidget *parent = nullptr);
    ~AddForm();

    void SetModel(QAbstractItemModel *model);
    void ShowModelData(const QModelIndex &index, bool isNew = false);

signals:
    void OnClose();

private:
    Ui::AddForm *ui;
    QList< QPair<QWidget*, QWidget*> > editWidgets;
    QAbstractItemModel *model;
    QGridLayout *gridLayout;
    QMap<QString, QVariant> currentItemMap;
    QModelIndex currentModelIndex;
    const QString DEFAULT_EDITOR_OBJECT_NAME = "defaultEditor";

    void ClearEditors();

    QWidget *GetStandardDataTypeEditor(const QVariant &value, QWidget *parent);
private slots:
    void AcceptChanges();
    void CancelChanges();

    // QObject interface
public:
    bool event(QEvent *event) override;
};
#endif // ADDFORM_H
