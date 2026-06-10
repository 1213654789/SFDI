/********************************************************************************
** Form generated from reading UI file 'control_window.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROL_WINDOW_H
#define UI_CONTROL_WINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_control_window
{
public:
    QAction *actionSerialHelper;
    QAction *actionguany;
    QAction *actionnew;
    QAction *actionedit;
    QWidget *centralwidget;
    QPushButton *Advanced_Button;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *control_window)
    {
        if (control_window->objectName().isEmpty())
            control_window->setObjectName("control_window");
        control_window->resize(961, 691);
        actionSerialHelper = new QAction(control_window);
        actionSerialHelper->setObjectName("actionSerialHelper");
        actionguany = new QAction(control_window);
        actionguany->setObjectName("actionguany");
        actionnew = new QAction(control_window);
        actionnew->setObjectName("actionnew");
        actionedit = new QAction(control_window);
        actionedit->setObjectName("actionedit");
        centralwidget = new QWidget(control_window);
        centralwidget->setObjectName("centralwidget");
        Advanced_Button = new QPushButton(centralwidget);
        Advanced_Button->setObjectName("Advanced_Button");
        Advanced_Button->setGeometry(QRect(830, 30, 81, 41));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(50, 79, 651, 521));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(gridLayoutWidget);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(32);
        label->setFont(font);
        label->setFrameShape(QFrame::Shape::Box);
        label->setLineWidth(2);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        control_window->setCentralWidget(centralwidget);
        menubar = new QMenuBar(control_window);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 961, 22));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName("menu_2");
        control_window->setMenuBar(menubar);
        statusbar = new QStatusBar(control_window);
        statusbar->setObjectName("statusbar");
        control_window->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menu->addAction(actionnew);
        menu->addSeparator();
        menu->addAction(actionedit);
        menu_2->addAction(actionSerialHelper);
        menu_2->addSeparator();
        menu_2->addAction(actionguany);

        retranslateUi(control_window);

        QMetaObject::connectSlotsByName(control_window);
    } // setupUi

    void retranslateUi(QMainWindow *control_window)
    {
        control_window->setWindowTitle(QCoreApplication::translate("control_window", "MainWindow", nullptr));
        actionSerialHelper->setText(QCoreApplication::translate("control_window", "\344\270\262\345\217\243\345\212\251\346\211\213", nullptr));
        actionguany->setText(QCoreApplication::translate("control_window", "\345\205\263\344\272\216", nullptr));
        actionnew->setText(QCoreApplication::translate("control_window", "\346\226\260\345\273\272", nullptr));
        actionedit->setText(QCoreApplication::translate("control_window", "\351\200\200\345\207\272", nullptr));
        Advanced_Button->setText(QCoreApplication::translate("control_window", "\350\256\276\347\275\256", nullptr));
        label->setText(QCoreApplication::translate("control_window", "\346\230\276\347\244\272", nullptr));
        menu->setTitle(QCoreApplication::translate("control_window", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QCoreApplication::translate("control_window", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class control_window: public Ui_control_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROL_WINDOW_H
