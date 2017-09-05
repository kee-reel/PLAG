/********************************************************************************
** Form generated from reading UI file 'mainform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *buttonAdd;
    QPushButton *buttonEdit;
    QPushButton *buttonDelete;
    QPushButton *buttonExit;

    void setupUi(QWidget *MainForm)
    {
        if (MainForm->objectName().isEmpty())
            MainForm->setObjectName(QStringLiteral("MainForm"));
        MainForm->setEnabled(true);
        MainForm->resize(368, 633);
        verticalLayout = new QVBoxLayout(MainForm);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        buttonAdd = new QPushButton(MainForm);
        buttonAdd->setObjectName(QStringLiteral("buttonAdd"));
        buttonAdd->setCursor(QCursor(Qt::ArrowCursor));
        buttonAdd->setAutoFillBackground(true);
        QIcon icon;
        icon.addFile(QStringLiteral(":/Res/ic_add_black_24dp.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonAdd->setIcon(icon);
        buttonAdd->setIconSize(QSize(48, 48));
        buttonAdd->setFlat(true);

        horizontalLayout->addWidget(buttonAdd);

        buttonEdit = new QPushButton(MainForm);
        buttonEdit->setObjectName(QStringLiteral("buttonEdit"));
        buttonEdit->setAutoFillBackground(true);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Res/ic_mode_edit_black_24dp.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonEdit->setIcon(icon1);
        buttonEdit->setIconSize(QSize(48, 48));
        buttonEdit->setFlat(true);

        horizontalLayout->addWidget(buttonEdit);

        buttonDelete = new QPushButton(MainForm);
        buttonDelete->setObjectName(QStringLiteral("buttonDelete"));
        buttonDelete->setAutoFillBackground(true);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Res/ic_delete_black_24dp.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonDelete->setIcon(icon2);
        buttonDelete->setIconSize(QSize(48, 48));
        buttonDelete->setFlat(true);

        horizontalLayout->addWidget(buttonDelete);

        buttonExit = new QPushButton(MainForm);
        buttonExit->setObjectName(QStringLiteral("buttonExit"));
        buttonExit->setAutoFillBackground(true);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Res/ic_exit_to_app_black_24dp.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonExit->setIcon(icon3);
        buttonExit->setIconSize(QSize(48, 48));
        buttonExit->setFlat(true);

        horizontalLayout->addWidget(buttonExit);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(MainForm);

        buttonAdd->setDefault(false);


        QMetaObject::connectSlotsByName(MainForm);
    } // setupUi

    void retranslateUi(QWidget *MainForm)
    {
        MainForm->setWindowTitle(QApplication::translate("MainForm", "Form", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        buttonAdd->setToolTip(QApplication::translate("MainForm", "Add", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        buttonAdd->setText(QString());
#ifndef QT_NO_TOOLTIP
        buttonEdit->setToolTip(QApplication::translate("MainForm", "Edit", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        buttonEdit->setText(QString());
#ifndef QT_NO_TOOLTIP
        buttonDelete->setToolTip(QApplication::translate("MainForm", "Delete", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        buttonDelete->setText(QString());
#ifndef QT_NO_TOOLTIP
        buttonExit->setToolTip(QApplication::translate("MainForm", "Exit", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        buttonExit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainForm: public Ui_MainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
