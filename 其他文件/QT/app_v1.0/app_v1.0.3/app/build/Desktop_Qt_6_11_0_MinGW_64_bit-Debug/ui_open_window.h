/********************************************************************************
** Form generated from reading UI file 'open_window.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPEN_WINDOW_H
#define UI_OPEN_WINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainWindow
{
public:
    QAction *action;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_4;
    QComboBox *open_serailCb;
    QSpacerItem *horizontalSpacer;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *open_btnSerialCheck;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *open_openBt;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *open_freq;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *send_button;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QSpinBox *open_times;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *advanced_setting_button;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *mainWindow)
    {
        if (mainWindow->objectName().isEmpty())
            mainWindow->setObjectName("mainWindow");
        mainWindow->resize(430, 340);
        mainWindow->setMinimumSize(QSize(430, 340));
        mainWindow->setMaximumSize(QSize(430, 340));
        action = new QAction(mainWindow);
        action->setObjectName("action");
        centralwidget = new QWidget(mainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        widget_6 = new QWidget(centralwidget);
        widget_6->setObjectName("widget_6");
        horizontalLayout_4 = new QHBoxLayout(widget_6);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(-1, 0, -1, 0);
        open_serailCb = new QComboBox(widget_6);
        open_serailCb->setObjectName("open_serailCb");
        open_serailCb->setMinimumSize(QSize(180, 50));
        open_serailCb->setMaximumSize(QSize(180, 16777215));
        QFont font;
        font.setPointSize(15);
        open_serailCb->setFont(font);

        horizontalLayout_4->addWidget(open_serailCb);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        widget = new QWidget(widget_6);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(0, 0));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        horizontalLayout->setContentsMargins(0, -1, 0, -1);
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        open_btnSerialCheck = new QPushButton(widget);
        open_btnSerialCheck->setObjectName("open_btnSerialCheck");
        open_btnSerialCheck->setMinimumSize(QSize(80, 50));
        open_btnSerialCheck->setMaximumSize(QSize(80, 50));
        open_btnSerialCheck->setFont(font);

        horizontalLayout->addWidget(open_btnSerialCheck);

        horizontalSpacer_5 = new QSpacerItem(30, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        open_openBt = new QPushButton(widget);
        open_openBt->setObjectName("open_openBt");
        open_openBt->setMinimumSize(QSize(80, 50));
        open_openBt->setMaximumSize(QSize(80, 50));
        open_openBt->setFont(font);

        horizontalLayout->addWidget(open_openBt);


        horizontalLayout_4->addWidget(widget);


        verticalLayout_3->addWidget(widget_6);

        widget_5 = new QWidget(centralwidget);
        widget_5->setObjectName("widget_5");
        verticalLayout_2 = new QVBoxLayout(widget_5);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(-1, 0, -1, 0);
        label = new QLabel(widget_5);
        label->setObjectName("label");
        label->setFont(font);

        verticalLayout_2->addWidget(label);

        widget_2 = new QWidget(widget_5);
        widget_2->setObjectName("widget_2");
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, -1, 0, -1);
        open_freq = new QSpinBox(widget_2);
        open_freq->setObjectName("open_freq");
        open_freq->setMinimumSize(QSize(180, 50));
        open_freq->setMaximumSize(QSize(180, 50));
        open_freq->setFont(font);
        open_freq->setMaximum(1000);
        open_freq->setValue(500);

        horizontalLayout_2->addWidget(open_freq);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        send_button = new QPushButton(widget_2);
        send_button->setObjectName("send_button");
        send_button->setMinimumSize(QSize(180, 50));
        send_button->setMaximumSize(QSize(180, 50));
        send_button->setFont(font);

        horizontalLayout_2->addWidget(send_button);


        verticalLayout_2->addWidget(widget_2);


        verticalLayout_3->addWidget(widget_5);

        widget_4 = new QWidget(centralwidget);
        widget_4->setObjectName("widget_4");
        verticalLayout = new QVBoxLayout(widget_4);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(-1, 0, -1, 0);
        label_2 = new QLabel(widget_4);
        label_2->setObjectName("label_2");
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);

        widget_3 = new QWidget(widget_4);
        widget_3->setObjectName("widget_3");
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, -1, 0, -1);
        open_times = new QSpinBox(widget_3);
        open_times->setObjectName("open_times");
        open_times->setMinimumSize(QSize(180, 50));
        open_times->setMaximumSize(QSize(180, 50));
        open_times->setFont(font);
        open_times->setMaximum(20);
        open_times->setValue(8);

        horizontalLayout_3->addWidget(open_times);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        advanced_setting_button = new QPushButton(widget_3);
        advanced_setting_button->setObjectName("advanced_setting_button");
        advanced_setting_button->setEnabled(true);
        advanced_setting_button->setMinimumSize(QSize(180, 50));
        advanced_setting_button->setMaximumSize(QSize(180, 50));
        advanced_setting_button->setFont(font);

        horizontalLayout_3->addWidget(advanced_setting_button);


        verticalLayout->addWidget(widget_3);


        verticalLayout_3->addWidget(widget_4);

        mainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(mainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 430, 20));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        mainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(mainWindow);
        statusbar->setObjectName("statusbar");
        mainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(action);

        retranslateUi(mainWindow);

        QMetaObject::connectSlotsByName(mainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *mainWindow)
    {
        mainWindow->setWindowTitle(QCoreApplication::translate("mainWindow", "Serial Port Assistant", nullptr));
        action->setText(QCoreApplication::translate("mainWindow", "\345\205\263\344\272\216", nullptr));
        open_btnSerialCheck->setText(QCoreApplication::translate("mainWindow", "\345\210\267\346\226\260", nullptr));
        open_openBt->setText(QCoreApplication::translate("mainWindow", "\350\277\236\346\216\245", nullptr));
        label->setText(QCoreApplication::translate("mainWindow", "\351\242\221\347\216\207", nullptr));
        send_button->setText(QCoreApplication::translate("mainWindow", "\345\217\221\351\200\201", nullptr));
        label_2->setText(QCoreApplication::translate("mainWindow", "\344\270\252\346\225\260", nullptr));
        advanced_setting_button->setText(QCoreApplication::translate("mainWindow", "\351\253\230\347\272\247\350\256\276\347\275\256", nullptr));
        menu->setTitle(QCoreApplication::translate("mainWindow", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainWindow: public Ui_mainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPEN_WINDOW_H
