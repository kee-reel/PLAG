/********************************************************************************
** Form generated from reading UI file 'galleryform.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GALLERYFORM_H
#define UI_GALLERYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GalleryForm
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout;
    QPushButton *buttonDelete;
    QPushButton *buttonConvertToTask;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonClose;

    void setupUi(QWidget *GalleryForm)
    {
        if (GalleryForm->objectName().isEmpty())
            GalleryForm->setObjectName(QStringLiteral("GalleryForm"));
        GalleryForm->resize(334, 455);
        GalleryForm->setAutoFillBackground(true);
        verticalLayout = new QVBoxLayout(GalleryForm);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        scrollArea = new QScrollArea(GalleryForm);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 314, 373));
        verticalLayout_8 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        buttonDelete = new QPushButton(GalleryForm);
        buttonDelete->setObjectName(QStringLiteral("buttonDelete"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonDelete->sizePolicy().hasHeightForWidth());
        buttonDelete->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QStringLiteral(":/Res/ic_delete_black_24dp.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonDelete->setIcon(icon);
        buttonDelete->setIconSize(QSize(48, 48));
        buttonDelete->setFlat(true);

        horizontalLayout->addWidget(buttonDelete);

        buttonConvertToTask = new QPushButton(GalleryForm);
        buttonConvertToTask->setObjectName(QStringLiteral("buttonConvertToTask"));
        sizePolicy.setHeightForWidth(buttonConvertToTask->sizePolicy().hasHeightForWidth());
        buttonConvertToTask->setSizePolicy(sizePolicy);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Res/sketch_to_task_24dp.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonConvertToTask->setIcon(icon1);
        buttonConvertToTask->setIconSize(QSize(80, 48));
        buttonConvertToTask->setFlat(true);

        horizontalLayout->addWidget(buttonConvertToTask);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonClose = new QPushButton(GalleryForm);
        buttonClose->setObjectName(QStringLiteral("buttonClose"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Res/ic_cancel_black_24dp.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonClose->setIcon(icon2);
        buttonClose->setIconSize(QSize(48, 48));
        buttonClose->setFlat(true);

        horizontalLayout->addWidget(buttonClose);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(GalleryForm);

        QMetaObject::connectSlotsByName(GalleryForm);
    } // setupUi

    void retranslateUi(QWidget *GalleryForm)
    {
        GalleryForm->setWindowTitle(QApplication::translate("GalleryForm", "Form", Q_NULLPTR));
        buttonDelete->setText(QString());
        buttonConvertToTask->setText(QString());
        buttonClose->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GalleryForm: public Ui_GalleryForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GALLERYFORM_H
