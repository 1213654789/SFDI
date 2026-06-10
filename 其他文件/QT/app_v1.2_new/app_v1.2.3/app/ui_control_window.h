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
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_control_window
{
public:
    QAction *actionSerialHelper;
    QAction *actionabout;
    QAction *actionnew;
    QAction *actionexit;
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
    QSpinBox *weightphoto;
    QSpinBox *highphoto;
    QPushButton *Exit_Button;
    QComboBox *TriggerSource;
    QComboBox *TriggerMode;
    QPushButton *save_location;
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
        actionabout = new QAction(control_window);
        actionabout->setObjectName("actionabout");
        actionnew = new QAction(control_window);
        actionnew->setObjectName("actionnew");
        actionexit = new QAction(control_window);
        actionexit->setObjectName("actionexit");
        centralwidget = new QWidget(control_window);
        centralwidget->setObjectName("centralwidget");
        Advanced_Button = new QPushButton(centralwidget);
        Advanced_Button->setObjectName("Advanced_Button");
        Advanced_Button->setGeometry(QRect(750, 600, 91, 51));
        QFont font;
        font.setPointSize(13);
        Advanced_Button->setFont(font);
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(20, 90, 711, 531));
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
        find_device->setGeometry(QRect(520, 20, 100, 50));
        find_device->setFont(font);
        open_device = new QPushButton(centralwidget);
        open_device->setObjectName("open_device");
        open_device->setGeometry(QRect(630, 20, 100, 50));
        open_device->setFont(font);
        close_device = new QPushButton(centralwidget);
        close_device->setObjectName("close_device");
        close_device->setGeometry(QRect(740, 20, 100, 50));
        close_device->setFont(font);
        single_acquisition = new QPushButton(centralwidget);
        single_acquisition->setObjectName("single_acquisition");
        single_acquisition->setGeometry(QRect(740, 430, 100, 50));
        single_acquisition->setFont(font);
        continuous_acquisition = new QPushButton(centralwidget);
        continuous_acquisition->setObjectName("continuous_acquisition");
        continuous_acquisition->setGeometry(QRect(850, 430, 100, 50));
        continuous_acquisition->setFont(font);
        stops_acquisition = new QPushButton(centralwidget);
        stops_acquisition->setObjectName("stops_acquisition");
        stops_acquisition->setGeometry(QRect(740, 480, 100, 50));
        stops_acquisition->setFont(font);
        save_BMP = new QPushButton(centralwidget);
        save_BMP->setObjectName("save_BMP");
        save_BMP->setGeometry(QRect(740, 540, 100, 50));
        save_BMP->setFont(font);
        save_PNG = new QPushButton(centralwidget);
        save_PNG->setObjectName("save_PNG");
        save_PNG->setGeometry(QRect(850, 490, 100, 50));
        save_PNG->setFont(font);
        weightphoto = new QSpinBox(centralwidget);
        weightphoto->setObjectName("weightphoto");
        weightphoto->setGeometry(QRect(740, 120, 91, 61));
        weightphoto->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        weightphoto->setMaximum(5000);
        highphoto = new QSpinBox(centralwidget);
        highphoto->setObjectName("highphoto");
        highphoto->setGeometry(QRect(840, 120, 91, 61));
        highphoto->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        highphoto->setMaximum(5000);
        Exit_Button = new QPushButton(centralwidget);
        Exit_Button->setObjectName("Exit_Button");
        Exit_Button->setGeometry(QRect(860, 600, 91, 51));
        Exit_Button->setFont(font);
        TriggerSource = new QComboBox(centralwidget);
        TriggerSource->addItem(QString());
        TriggerSource->addItem(QString());
        TriggerSource->addItem(QString());
        TriggerSource->addItem(QString());
        TriggerSource->addItem(QString());
        TriggerSource->setObjectName("TriggerSource");
        TriggerSource->setGeometry(QRect(750, 360, 141, 51));
        QFont font2;
        font2.setPointSize(15);
        TriggerSource->setFont(font2);
        TriggerMode = new QComboBox(centralwidget);
        TriggerMode->addItem(QString());
        TriggerMode->addItem(QString());
        TriggerMode->addItem(QString());
        TriggerMode->addItem(QString());
        TriggerMode->setObjectName("TriggerMode");
        TriggerMode->setGeometry(QRect(750, 290, 121, 51));
        QFont font3;
        font3.setPointSize(14);
        TriggerMode->setFont(font3);
        save_location = new QPushButton(centralwidget);
        save_location->setObjectName("save_location");
        save_location->setGeometry(QRect(860, 540, 100, 50));
        save_location->setFont(font);
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
        menu->addAction(actionexit);
        menu_2->addAction(actionSerialHelper);
        menu_2->addSeparator();
        menu_2->addAction(actionabout);

        retranslateUi(control_window);

        QMetaObject::connectSlotsByName(control_window);
    } // setupUi

    void retranslateUi(QMainWindow *control_window)
    {
        control_window->setWindowTitle(QCoreApplication::translate("control_window", "MainWindow", nullptr));
        actionSerialHelper->setText(QCoreApplication::translate("control_window", "\344\270\262\345\217\243\345\212\251\346\211\213", nullptr));
        actionabout->setText(QCoreApplication::translate("control_window", "\345\205\263\344\272\216", nullptr));
        actionnew->setText(QCoreApplication::translate("control_window", "\346\226\260\345\273\272", nullptr));
        actionexit->setText(QCoreApplication::translate("control_window", "\351\200\200\345\207\272", nullptr));
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
        Exit_Button->setText(QCoreApplication::translate("control_window", "\351\200\200\345\207\272", nullptr));
        TriggerSource->setItemText(0, QCoreApplication::translate("control_window", "line0", nullptr));
        TriggerSource->setItemText(1, QCoreApplication::translate("control_window", "line2", nullptr));
        TriggerSource->setItemText(2, QCoreApplication::translate("control_window", "\350\256\241\346\225\260\345\231\250\350\247\246\345\217\221", nullptr));
        TriggerSource->setItemText(3, QCoreApplication::translate("control_window", "\350\275\257\344\273\266\350\247\246\345\217\221", nullptr));
        TriggerSource->setItemText(4, QCoreApplication::translate("control_window", "\351\242\221\347\216\207\350\275\254\346\215\242\345\231\250\350\247\246\345\217\221", nullptr));

        TriggerMode->setItemText(0, QCoreApplication::translate("control_window", "\344\270\212\345\215\207\346\262\277", nullptr));
        TriggerMode->setItemText(1, QCoreApplication::translate("control_window", "\344\270\213\351\231\215\346\262\277", nullptr));
        TriggerMode->setItemText(2, QCoreApplication::translate("control_window", "\351\253\230\347\224\265\345\271\263", nullptr));
        TriggerMode->setItemText(3, QCoreApplication::translate("control_window", "\344\275\216\347\224\265\345\271\263", nullptr));

        save_location->setText(QCoreApplication::translate("control_window", "\344\277\235\345\255\230\344\275\215\347\275\256", nullptr));
        menu->setTitle(QCoreApplication::translate("control_window", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QCoreApplication::translate("control_window", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class control_window: public Ui_control_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROL_WINDOW_H
