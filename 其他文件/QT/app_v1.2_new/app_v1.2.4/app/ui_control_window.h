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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
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
    QPushButton *send_button;
    QSpinBox *open_freq;
    QSpinBox *open_times;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QComboBox *choose_devices;
    QPushButton *find_device;
    QPushButton *open_device;
    QSpacerItem *horizontalSpacer;
    QComboBox *open_serailCb;
    QPushButton *open_btnSerialCheck;
    QPushButton *open_openBt;
    QComboBox *comboBox;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *control_window)
    {
        if (control_window->objectName().isEmpty())
            control_window->setObjectName("control_window");
        control_window->resize(961, 691);
        control_window->setMinimumSize(QSize(961, 691));
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
        Advanced_Button->setGeometry(QRect(750, 600, 91, 30));
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

        single_acquisition = new QPushButton(centralwidget);
        single_acquisition->setObjectName("single_acquisition");
        single_acquisition->setGeometry(QRect(750, 450, 100, 30));
        single_acquisition->setFont(font);
        continuous_acquisition = new QPushButton(centralwidget);
        continuous_acquisition->setObjectName("continuous_acquisition");
        continuous_acquisition->setGeometry(QRect(860, 450, 100, 30));
        continuous_acquisition->setFont(font);
        stops_acquisition = new QPushButton(centralwidget);
        stops_acquisition->setObjectName("stops_acquisition");
        stops_acquisition->setGeometry(QRect(750, 490, 100, 30));
        stops_acquisition->setFont(font);
        save_BMP = new QPushButton(centralwidget);
        save_BMP->setObjectName("save_BMP");
        save_BMP->setGeometry(QRect(750, 530, 100, 30));
        save_BMP->setFont(font);
        save_PNG = new QPushButton(centralwidget);
        save_PNG->setObjectName("save_PNG");
        save_PNG->setGeometry(QRect(860, 490, 100, 30));
        save_PNG->setFont(font);
        weightphoto = new QSpinBox(centralwidget);
        weightphoto->setObjectName("weightphoto");
        weightphoto->setGeometry(QRect(750, 360, 91, 40));
        weightphoto->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        weightphoto->setMaximum(5000);
        highphoto = new QSpinBox(centralwidget);
        highphoto->setObjectName("highphoto");
        highphoto->setGeometry(QRect(850, 360, 91, 40));
        highphoto->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        highphoto->setMaximum(5000);
        Exit_Button = new QPushButton(centralwidget);
        Exit_Button->setObjectName("Exit_Button");
        Exit_Button->setGeometry(QRect(860, 600, 91, 30));
        Exit_Button->setFont(font);
        TriggerSource = new QComboBox(centralwidget);
        TriggerSource->addItem(QString());
        TriggerSource->addItem(QString());
        TriggerSource->addItem(QString());
        TriggerSource->addItem(QString());
        TriggerSource->addItem(QString());
        TriggerSource->setObjectName("TriggerSource");
        TriggerSource->setGeometry(QRect(860, 410, 81, 30));
        QFont font2;
        font2.setPointSize(15);
        TriggerSource->setFont(font2);
        TriggerMode = new QComboBox(centralwidget);
        TriggerMode->addItem(QString());
        TriggerMode->addItem(QString());
        TriggerMode->addItem(QString());
        TriggerMode->addItem(QString());
        TriggerMode->setObjectName("TriggerMode");
        TriggerMode->setGeometry(QRect(750, 410, 91, 30));
        QFont font3;
        font3.setPointSize(14);
        TriggerMode->setFont(font3);
        save_location = new QPushButton(centralwidget);
        save_location->setObjectName("save_location");
        save_location->setGeometry(QRect(860, 530, 100, 30));
        save_location->setFont(font);
        send_button = new QPushButton(centralwidget);
        send_button->setObjectName("send_button");
        send_button->setGeometry(QRect(740, 90, 100, 30));
        send_button->setFont(font);
        open_freq = new QSpinBox(centralwidget);
        open_freq->setObjectName("open_freq");
        open_freq->setGeometry(QRect(760, 130, 171, 51));
        QFont font4;
        font4.setPointSize(20);
        open_freq->setFont(font4);
        open_freq->setMaximum(1000);
        open_freq->setValue(500);
        open_times = new QSpinBox(centralwidget);
        open_times->setObjectName("open_times");
        open_times->setGeometry(QRect(760, 190, 171, 51));
        open_times->setFont(font4);
        open_times->setMaximum(1000);
        open_times->setValue(10);
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(0, 10, 941, 71));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        choose_devices = new QComboBox(horizontalLayoutWidget);
        choose_devices->setObjectName("choose_devices");
        choose_devices->setMinimumSize(QSize(200, 40));
        choose_devices->setMaximumSize(QSize(20, 16777215));

        horizontalLayout->addWidget(choose_devices);

        find_device = new QPushButton(horizontalLayoutWidget);
        find_device->setObjectName("find_device");
        find_device->setFont(font);

        horizontalLayout->addWidget(find_device);

        open_device = new QPushButton(horizontalLayoutWidget);
        open_device->setObjectName("open_device");
        open_device->setFont(font);

        horizontalLayout->addWidget(open_device);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        open_serailCb = new QComboBox(horizontalLayoutWidget);
        open_serailCb->setObjectName("open_serailCb");
        open_serailCb->setMinimumSize(QSize(100, 0));
        open_serailCb->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(open_serailCb);

        open_btnSerialCheck = new QPushButton(horizontalLayoutWidget);
        open_btnSerialCheck->setObjectName("open_btnSerialCheck");
        open_btnSerialCheck->setFont(font);

        horizontalLayout->addWidget(open_btnSerialCheck);

        open_openBt = new QPushButton(horizontalLayoutWidget);
        open_openBt->setObjectName("open_openBt");
        open_openBt->setFont(font);

        horizontalLayout->addWidget(open_openBt);

        comboBox = new QComboBox(horizontalLayoutWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setFont(font);

        horizontalLayout->addWidget(comboBox);

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
        toolBar = new QToolBar(control_window);
        toolBar->setObjectName("toolBar");
        control_window->addToolBar(Qt::ToolBarArea::BottomToolBarArea, toolBar);

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
        send_button->setText(QCoreApplication::translate("control_window", "\345\217\221\351\200\201", nullptr));
        find_device->setText(QCoreApplication::translate("control_window", "\346\237\245\346\211\276\350\256\276\345\244\207", nullptr));
        open_device->setText(QCoreApplication::translate("control_window", "\346\211\223\345\274\200\350\256\276\345\244\207", nullptr));
        open_btnSerialCheck->setText(QCoreApplication::translate("control_window", "\345\210\267\346\226\260", nullptr));
        open_openBt->setText(QCoreApplication::translate("control_window", "\350\277\236\346\216\245", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("control_window", "\347\241\254\344\273\266\346\213\215\347\205\247", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("control_window", "\350\275\257\344\273\266\346\213\215\347\205\247", nullptr));

        menu->setTitle(QCoreApplication::translate("control_window", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QCoreApplication::translate("control_window", "\345\270\256\345\212\251", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("control_window", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class control_window: public Ui_control_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROL_WINDOW_H
