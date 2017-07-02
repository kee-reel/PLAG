/********************************************************************************
** Form generated from reading UI file 'pomodoroview.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PomodoroView
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *pomodoroCountLabel;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
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

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout->addItem(verticalSpacer);

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
        PomodoroView->setWindowTitle(QApplication::translate("PomodoroView", "Form", 0));
        label->setText(QApplication::translate("PomodoroView", "Today completed", 0));
        pomodoroCountLabel->setText(QApplication::translate("PomodoroView", "0 pomodoros", 0));
        buttonExit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PomodoroView: public Ui_PomodoroView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POMODOROVIEW_H
