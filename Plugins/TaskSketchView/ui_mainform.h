/********************************************************************************
** Form generated from reading UI file 'mainform.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "paintwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainForm
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    PaintWidget *widgetPaint;
    QHBoxLayout *horizontalLayout;
    QPushButton *buttonClear;
    QPushButton *buttonSave;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonOpenGallery;
    QPushButton *buttonClose;

    void setupUi(QWidget *MainForm)
    {
        if (MainForm->objectName().isEmpty())
            MainForm->setObjectName(QStringLiteral("MainForm"));
        MainForm->setEnabled(true);
        MainForm->resize(334, 455);
        MainForm->setAutoFillBackground(true);
        verticalLayout = new QVBoxLayout(MainForm);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        frame = new QFrame(MainForm);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setStyleSheet(QStringLiteral("border-color: rgb(0, 0, 0);"));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Plain);
        frame->setLineWidth(2);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        widgetPaint = new PaintWidget(frame);
        widgetPaint->setObjectName(QStringLiteral("widgetPaint"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widgetPaint->sizePolicy().hasHeightForWidth());
        widgetPaint->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(widgetPaint);


        verticalLayout->addWidget(frame);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        buttonClear = new QPushButton(MainForm);
        buttonClear->setObjectName(QStringLiteral("buttonClear"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Res/ic_file_restore_black_24dp.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonClear->setIcon(icon);
        buttonClear->setIconSize(QSize(48, 48));
        buttonClear->setFlat(true);

        horizontalLayout->addWidget(buttonClear);

        buttonSave = new QPushButton(MainForm);
        buttonSave->setObjectName(QStringLiteral("buttonSave"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Res/ic_content_save_black_24dp.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonSave->setIcon(icon1);
        buttonSave->setIconSize(QSize(48, 48));
        buttonSave->setFlat(true);

        horizontalLayout->addWidget(buttonSave);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonOpenGallery = new QPushButton(MainForm);
        buttonOpenGallery->setObjectName(QStringLiteral("buttonOpenGallery"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Res/ic_image_multiple_black_24dp.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonOpenGallery->setIcon(icon2);
        buttonOpenGallery->setIconSize(QSize(48, 48));
        buttonOpenGallery->setFlat(true);

        horizontalLayout->addWidget(buttonOpenGallery);

        buttonClose = new QPushButton(MainForm);
        buttonClose->setObjectName(QStringLiteral("buttonClose"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Res/ic_cancel_black_24dp.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonClose->setIcon(icon3);
        buttonClose->setIconSize(QSize(48, 48));
        buttonClose->setFlat(true);

        horizontalLayout->addWidget(buttonClose);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(MainForm);

        QMetaObject::connectSlotsByName(MainForm);
    } // setupUi

    void retranslateUi(QWidget *MainForm)
    {
        MainForm->setWindowTitle(QApplication::translate("MainForm", "Form", Q_NULLPTR));
        buttonClear->setText(QString());
        buttonSave->setText(QString());
        buttonOpenGallery->setText(QString());
        buttonClose->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainForm: public Ui_MainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
