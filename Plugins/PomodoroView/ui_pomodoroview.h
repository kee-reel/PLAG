/********************************************************************************
** Form generated from reading UI file 'pomodoroview.ui'
**
<<<<<<< HEAD
** Created by: Qt User Interface Compiler version 5.9.1
=======
** Created by: Qt User Interface Compiler version 5.2.1
>>>>>>> a2445897c806490964d364d39f2b23b415a47371
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POMODOROVIEW_H
#define UI_POMODOROVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "pomodorobutton.h"

QT_BEGIN_NAMESPACE

class Ui_PomodoroView
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *pomodoroCountLabel;
<<<<<<< HEAD
    PomodoroButton *pomodoroButton;
=======
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QTreeView *treeView;
>>>>>>> a2445897c806490964d364d39f2b23b415a47371
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *buttonExit;

    void setupUi(QWidget *PomodoroView)
    {
        if (PomodoroView->objectName().isEmpty())
            PomodoroView->setObjectName(QStringLiteral("PomodoroView"));
        PomodoroView->resize(465, 497);
        verticalLayout = new QVBoxLayout(PomodoroView);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(PomodoroView);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QStringLiteral("Khmer UI"));
        font.setPointSize(20);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        pomodoroCountLabel = new QLabel(PomodoroView);
        pomodoroCountLabel->setObjectName(QStringLiteral("pomodoroCountLabel"));
        sizePolicy.setHeightForWidth(pomodoroCountLabel->sizePolicy().hasHeightForWidth());
        pomodoroCountLabel->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamily(QStringLiteral("Khmer UI"));
        font1.setPointSize(18);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setWeight(50);
        font1.setStrikeOut(false);
        pomodoroCountLabel->setFont(font1);
        pomodoroCountLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(pomodoroCountLabel);

        pomodoroButton = new PomodoroButton(PomodoroView);
        pomodoroButton->setObjectName(QStringLiteral("pomodoroButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pomodoroButton->sizePolicy().hasHeightForWidth());
        pomodoroButton->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(pomodoroButton);

        treeView = new QTreeView(PomodoroView);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setRootIsDecorated(false);
        treeView->setHeaderHidden(true);

        verticalLayout->addWidget(treeView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        buttonExit = new QPushButton(PomodoroView);
        buttonExit->setObjectName(QStringLiteral("buttonExit"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Res/ic_exit_to_app_black_24dp.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonExit->setIcon(icon);
        buttonExit->setIconSize(QSize(48, 48));
        buttonExit->setFlat(true);

        horizontalLayout_2->addWidget(buttonExit);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(PomodoroView);

        QMetaObject::connectSlotsByName(PomodoroView);
    } // setupUi

    void retranslateUi(QWidget *PomodoroView)
    {
        PomodoroView->setWindowTitle(QApplication::translate("PomodoroView", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("PomodoroView", "Today completed", Q_NULLPTR));
        pomodoroCountLabel->setText(QApplication::translate("PomodoroView", "0 pomodoros", Q_NULLPTR));
        buttonExit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PomodoroView: public Ui_PomodoroView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POMODOROVIEW_H
