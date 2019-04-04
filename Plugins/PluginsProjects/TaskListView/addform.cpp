#include "addform.h"
#include "ui_addform.h"

#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDateTimeEdit>

AddForm::AddForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddForm)
{
    ui->setupUi(this);
    hide();
    connect(ui->buttonAccept, SIGNAL(clicked(bool)), SLOT(AcceptChanges()));
    connect(ui->buttonCancel, SIGNAL(clicked(bool)), SLOT(CancelChanges()));
    gridLayout = new QGridLayout(ui->scrollAreaWidgetContents);
}

AddForm::~AddForm()
{
    ClearEditors();
    delete gridLayout;
    delete ui;
}

void AddForm::SetModel(QAbstractItemModel *model)
{
    this->model = model;
//    mapper->setModel(model);
//    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

}

void AddForm::ShowModelData(const QModelIndex &index, bool isNew)
{
    show();
//    auto map = mapper->model()->itemData(index);
//    ui->label_2->setText();
    //ui->lineEdit_2->setFocus();
//    mapper->setRootIndex(index.parent());
//    mapper->setCurrentModelIndex(index);
//    if(isNew)
//        ui->lineEdit_2->setText("");
    currentModelIndex = index;
    auto rolesMap = model->itemData(currentModelIndex);
    currentItemMap = rolesMap[Qt::UserRole].toMap();
    auto editorsMap = model->headerData(0, Qt::Horizontal, Qt::UserRole).toMap();
    auto editorsChunkIter = editorsMap.begin();
    int rowCount = 0;
    for(auto chunkIter = currentItemMap.begin(); chunkIter != currentItemMap.end(); ++chunkIter)
    {
        auto valuesMap = chunkIter.value().toMap();
        auto valuesEditorsMap = editorsChunkIter.value().toMap();
        auto valueEditorsIter = valuesEditorsMap.begin();
        for(auto valueIter = valuesMap.begin(); valueIter != valuesMap.end(); ++valueIter)
        {
            auto label = new QLabel(valueIter.key(), this);
            QWidget *editWidget;
            if(valueEditorsIter.value().isValid())
            {
                editWidget = static_cast<QWidget*>(valueEditorsIter.value().value<void*>());
                editWidget->setParent(this);
                editWidget->setObjectName("custom");
                editWidget->setProperty("value", valueIter.value());
            }
            else
            {
                editWidget = GetStandardDataTypeEditor(valueIter.value(), this);
                editWidget->setObjectName(DEFAULT_EDITOR_OBJECT_NAME);
            }
            gridLayout->addWidget(label, rowCount, 0);
            gridLayout->addWidget(editWidget, rowCount, 1);
            editWidgets.append(QPair<QWidget*, QWidget*>(label, editWidget));
            ++rowCount;
            ++valueEditorsIter;
        }
        ++editorsChunkIter;
    }
}

QWidget* AddForm::GetStandardDataTypeEditor(const QVariant& value, QWidget* parent)
{
    switch (value.type())
    {
    case QVariant::String:
    {
        auto widget = new QLineEdit(parent);
        widget->setText(value.toString());
        return widget;
    }
    case QVariant::Int:
    {
        auto widget = new QSpinBox(parent);
        widget->setValue(value.toInt());
        return widget;
    }
    case QVariant::Double:
    {
        auto widget = new QDoubleSpinBox(parent);
        widget->setValue(value.toInt());
        return widget;
    }
    case QVariant::DateTime:
    {
        auto widget = new QDateTimeEdit(parent);
        widget->setDateTime(value.toDateTime());
        return widget;
    }
    default:
    {
        auto widget = new QLineEdit(parent);
        widget->setText(value.toString());
        return widget;
    }
    }
}

void AddForm::ClearEditors()
{
    for(auto value : editWidgets)
    {
        auto label = value.first;
        auto editWidget = value.second;

        gridLayout->removeWidget(label);
        delete label;
        gridLayout->removeWidget(editWidget);
        if(editWidget->objectName() == DEFAULT_EDITOR_OBJECT_NAME)
            delete editWidget;
    }
    editWidgets.clear();
    currentItemMap.clear();
}

void AddForm::AcceptChanges()
{
    qDebug() << "AcceptChanges";
    int rowCount = 0;
    for(auto iter = currentItemMap.begin(); iter != currentItemMap.end(); ++iter)
    {
        qDebug() << "AcceptChanges";
        auto map = iter.value().toMap();
        for(auto mapIter = map.begin(); mapIter != map.end(); ++mapIter)
        {
            qDebug() << "AcceptChanges";
            auto&& editWidgetsPair = editWidgets[rowCount];
            auto&& editWidget = editWidgetsPair.second;
            bool isDefaultEditor = editWidget->objectName() == DEFAULT_EDITOR_OBJECT_NAME;
            map[mapIter.key()] = editWidget->property(isDefaultEditor ? "text" : "value");
            ++rowCount;
        }
        currentItemMap[iter.key()] = QVariant(map);
    }
    QMap<int, QVariant> rolesMap;
    rolesMap.insert(Qt::UserRole, currentItemMap);
    model->setItemData(currentModelIndex, rolesMap);
    qDebug() << "AcceptChanges";
    ClearEditors();
    qDebug() << "ClearEditors";
    CancelChanges();
    qDebug() << "CancelChanges";
}

void AddForm::CancelChanges()
{
    hide();
    ClearEditors();
    emit OnClose();
}

bool AddForm::event(QEvent *event)
{
    switch (event->type()) {
        case QEvent::KeyRelease:{
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            switch (keyEvent->key()) {
            case Qt::Key_Enter:
                AcceptChanges();
                break;
            case Qt::Key_Escape:
                CancelChanges();
                break;
            default:
                return QWidget::event(event);
                break;
            }

        } break;
        default:
            return QWidget::event(event);
            break;
    }
}
