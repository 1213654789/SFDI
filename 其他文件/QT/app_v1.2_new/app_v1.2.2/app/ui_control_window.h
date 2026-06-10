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
#include <QtWidgets/QComboBox>
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
    QLabel *label_show_;
    QComboBox *choose_devices;
    QPushButton *find_device;
    QPushButton *open_device;
    QPushButton *close_device;
    QPushButton *single_acquisition;
    QPushButton *continuous_acquisition;
    QPushButton *stops_acquisition;
    QPushButton *save_BMP;
    QPushButton *save_PNG;
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
        Advanced_Button->setGeometry(QRect(810, 550, 91, 51));
        QFont font;
        font.setPointSize(13);
        Advanced_Button->setFont(font);
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(50, 79, 711, 531));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_show_ = new QLabel(gridLayoutWidget);
        label_show_->setObjectName("label_show_");
        QFont font1;
        font1.setPointSize(32);
        label_show_->setFont(font1);
        label_show_->setFrameShape(QFrame::Shape::Box);
        label_show_->setLineWidth(2);
        label_show_->setTextFormat(Qt::TextFormat::PlainText);
        label_show_->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_show_, 0, 0, 1, 1);

        choose_devices = new QComboBox(centralwidget);
        choose_devices->setObjectName("choose_devices");
        choose_devices->setGeometry(QRect(40, 20, 451, 41));
        find_device = new QPushButton(centralwidget);
        find_device->setObjectName("find_device");
        find_device->setGeometry(QRect(810, 10, 100, 50));
        find_device->setFont(font);
        open_device = new QPushButton(centralwidget);
        open_device->setObjectName("open_device");
        open_device->setGeometry(QRect(810, 60, 100, 50));
        open_device->setFont(font);
        close_device = new QPushButton(centralwidget);
        close_device->setObjectName("close_device");
        close_device->setGeometry(QRect(810, 110, 100, 50));
        close_device->setFont(font);
        single_acquisition = new QPushButton(centralwidget);
        single_acquisition->setObjectName("single_acquisition");
        single_acquisition->setGeometry(QRect(810, 170, 100, 50));
        single_acquisition->setFont(font);
        continuous_acquisition = new QPushButton(centralwidget);
        continuous_acquisition->setObjectName("continuous_acquisition");
        continuous_acquisition->setGeometry(QRect(810, 230, 100, 50));
        continuous_acquisition->setFont(font);
        stops_acquisition = new QPushButton(centralwidget);
        stops_acquisition->setObjectName("stops_acquisition");
        stops_acquisition->setGeometry(QRect(810, 290, 100, 50));
        stops_acquisition->setFont(font);
        save_BMP = new QPushButton(centralwidget);
        save_BMP->setObjectName("save_BMP");
        save_BMP->setGeometry(QRect(810, 350, 100, 50));
        save_BMP->setFont(font);
        save_PNG = new QPushButton(centralwidget);
        save_PNG->setObjectName("save_PNG");
        save_PNG->setGeometry(QRect(810, 410, 100, 50));
        save_PNG->setFont(font);
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
        label_show_->setText(QCoreApplication::translate("control_window", "\346\230\276\347\244\272", nullptr));
        find_device->setText(QCoreApplication::translate("control_window", "\346\237\245\346\211\276\350\256\276\345\244\207", nullptr));
        open_device->setText(QCoreApplication::translate("control_window", "\346\211\223\345\274\200\350\256\276\345\244\207", nullptr));
        close_device->setText(QCoreApplication::translate("control_window", "\345\205\263\351\227\255\350\256\276\345\244\207", nullptr));
        single_acquisition->setText(QCoreApplication::translate("control_window", "\345\215\225\346\254\241\351\207\207\351\233\206", nullptr));
        continuous_acquisition->setText(QCoreApplication::translate("control_window", "\350\277\236\347\273\255\351\207\207\351\233\206", nullptr));
        stops_acquisition->setText(QCoreApplication::translate("control_window", "\345\201\234\346\255\242\351\207\207\351\233\206", nullptr));
        save_BMP->setText(QCoreApplication::translate("control_window", "\344\277\235\345\255\230BMP", nullptr));
        save_PNG->setText(QCoreApplication::translate("control_window", "\344\277\235\345\255\230PNG", nullptr));
        menu->setTitle(QCoreApplication::translate("control_window", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QCoreApplication::translate("control_window", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class control_window: public Ui_control_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROL_WINDOW_H
