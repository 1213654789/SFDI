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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_control_window
{
public:
    QAction *actionSerialHelper;
    QAction *actionabout;
    QAction *actionopen;
    QAction *actionexit;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_15;
    QComboBox *choose_devices;
    QPushButton *find_device;
    QPushButton *open_device;
    QSpacerItem *horizontalSpacer;
    QComboBox *open_serailCb;
    QPushButton *open_btnSerialCheck;
    QPushButton *open_openBt;
    QComboBox *selectmode;
    QWidget *widget_15;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_show_;
    QWidget *widget_17;
    QVBoxLayout *verticalLayout_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *open_freq;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_2;
    QSpinBox *open_times;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_4;
    QSpinBox *weightphoto;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_3;
    QSpinBox *highphoto;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QComboBox *TriggerMode;
    QWidget *widget_10;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_11;
    QSpinBox *Shutter_time;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QComboBox *TriggerSource;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_7;
    QPushButton *single_acquisition;
    QWidget *widget_9;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_8;
    QPushButton *continuous_acquisition;
    QWidget *widget_11;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_10;
    QComboBox *save_formal;
    QWidget *widget_13;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_12;
    QPushButton *save_location;
    QWidget *widget_16;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_9;
    QPushButton *send_button;
    QWidget *widget_18;
    QHBoxLayout *horizontalLayout_13;
    QPushButton *take_photo;
    QPushButton *Exit_Button;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *control_window)
    {
        if (control_window->objectName().isEmpty())
            control_window->setObjectName("control_window");
        control_window->resize(960, 600);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(control_window->sizePolicy().hasHeightForWidth());
        control_window->setSizePolicy(sizePolicy);
        control_window->setMinimumSize(QSize(960, 600));
        actionSerialHelper = new QAction(control_window);
        actionSerialHelper->setObjectName("actionSerialHelper");
        actionabout = new QAction(control_window);
        actionabout->setObjectName("actionabout");
        actionopen = new QAction(control_window);
        actionopen->setObjectName("actionopen");
        actionexit = new QAction(control_window);
        actionexit->setObjectName("actionexit");
        centralwidget = new QWidget(control_window);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy1);
        widget->setMinimumSize(QSize(0, 40));
        widget->setMaximumSize(QSize(16777215, 40));
        horizontalLayout_15 = new QHBoxLayout(widget);
        horizontalLayout_15->setObjectName("horizontalLayout_15");
        horizontalLayout_15->setContentsMargins(-1, 0, -1, -1);
        choose_devices = new QComboBox(widget);
        choose_devices->setObjectName("choose_devices");
        choose_devices->setMinimumSize(QSize(200, 30));
        choose_devices->setMaximumSize(QSize(200, 30));
        QFont font;
        font.setPointSize(12);
        choose_devices->setFont(font);
        choose_devices->setFocusPolicy(Qt::FocusPolicy::NoFocus);

        horizontalLayout_15->addWidget(choose_devices);

        find_device = new QPushButton(widget);
        find_device->setObjectName("find_device");
        find_device->setMinimumSize(QSize(100, 30));
        find_device->setMaximumSize(QSize(100, 30));
        find_device->setFont(font);

        horizontalLayout_15->addWidget(find_device);

        open_device = new QPushButton(widget);
        open_device->setObjectName("open_device");
        open_device->setMinimumSize(QSize(100, 30));
        open_device->setMaximumSize(QSize(100, 30));
        open_device->setFont(font);

        horizontalLayout_15->addWidget(open_device);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer);

        open_serailCb = new QComboBox(widget);
        open_serailCb->setObjectName("open_serailCb");
        open_serailCb->setMinimumSize(QSize(130, 30));
        open_serailCb->setMaximumSize(QSize(120, 30));
        open_serailCb->setFont(font);
        open_serailCb->setFocusPolicy(Qt::FocusPolicy::NoFocus);

        horizontalLayout_15->addWidget(open_serailCb);

        open_btnSerialCheck = new QPushButton(widget);
        open_btnSerialCheck->setObjectName("open_btnSerialCheck");
        open_btnSerialCheck->setMinimumSize(QSize(100, 30));
        open_btnSerialCheck->setMaximumSize(QSize(100, 30));
        open_btnSerialCheck->setFont(font);

        horizontalLayout_15->addWidget(open_btnSerialCheck);

        open_openBt = new QPushButton(widget);
        open_openBt->setObjectName("open_openBt");
        open_openBt->setMinimumSize(QSize(100, 30));
        open_openBt->setMaximumSize(QSize(100, 30));
        open_openBt->setFont(font);

        horizontalLayout_15->addWidget(open_openBt);

        selectmode = new QComboBox(widget);
        selectmode->addItem(QString());
        selectmode->addItem(QString());
        selectmode->setObjectName("selectmode");
        selectmode->setMinimumSize(QSize(120, 30));
        selectmode->setMaximumSize(QSize(120, 30));
        selectmode->setFont(font);
        selectmode->setFocusPolicy(Qt::FocusPolicy::NoFocus);

        horizontalLayout_15->addWidget(selectmode);


        verticalLayout_2->addWidget(widget);

        widget_15 = new QWidget(centralwidget);
        widget_15->setObjectName("widget_15");
        horizontalLayout_11 = new QHBoxLayout(widget_15);
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        horizontalLayout_11->setContentsMargins(-1, 0, -1, 0);
        label_show_ = new QLabel(widget_15);
        label_show_->setObjectName("label_show_");
        label_show_->setMinimumSize(QSize(200, 200));
        QFont font1;
        font1.setPointSize(32);
        label_show_->setFont(font1);
        label_show_->setFrameShape(QFrame::Shape::Box);
        label_show_->setLineWidth(2);
        label_show_->setTextFormat(Qt::TextFormat::PlainText);
        label_show_->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_11->addWidget(label_show_);

        widget_17 = new QWidget(widget_15);
        widget_17->setObjectName("widget_17");
        widget_17->setMinimumSize(QSize(280, 0));
        widget_17->setMaximumSize(QSize(280, 16777215));
        widget_17->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        verticalLayout_3 = new QVBoxLayout(widget_17);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(widget_17);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setMinimumSize(QSize(280, 0));
        scrollArea->setMaximumSize(QSize(280, 16777215));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 261, 720));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName("verticalLayout");
        widget_2 = new QWidget(scrollAreaWidgetContents);
        widget_2->setObjectName("widget_2");
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(widget_2);
        label->setObjectName("label");
        label->setMinimumSize(QSize(80, 30));
        label->setMaximumSize(QSize(80, 30));
        label->setFont(font);

        horizontalLayout->addWidget(label);

        open_freq = new QSpinBox(widget_2);
        open_freq->setObjectName("open_freq");
        open_freq->setMinimumSize(QSize(105, 35));
        open_freq->setMaximumSize(QSize(105, 35));
        open_freq->setFont(font);
        open_freq->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        open_freq->setMaximum(1000);
        open_freq->setValue(50);

        horizontalLayout->addWidget(open_freq);


        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(scrollAreaWidgetContents);
        widget_3->setObjectName("widget_3");
        horizontalLayout_16 = new QHBoxLayout(widget_3);
        horizontalLayout_16->setObjectName("horizontalLayout_16");
        label_2 = new QLabel(widget_3);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(80, 30));
        label_2->setMaximumSize(QSize(80, 30));
        label_2->setFont(font);

        horizontalLayout_16->addWidget(label_2);

        open_times = new QSpinBox(widget_3);
        open_times->setObjectName("open_times");
        open_times->setMinimumSize(QSize(105, 35));
        open_times->setMaximumSize(QSize(105, 35));
        open_times->setFont(font);
        open_times->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        open_times->setMaximum(1000);
        open_times->setValue(10);

        horizontalLayout_16->addWidget(open_times);


        verticalLayout->addWidget(widget_3);

        widget_7 = new QWidget(scrollAreaWidgetContents);
        widget_7->setObjectName("widget_7");
        horizontalLayout_18 = new QHBoxLayout(widget_7);
        horizontalLayout_18->setObjectName("horizontalLayout_18");
        label_4 = new QLabel(widget_7);
        label_4->setObjectName("label_4");
        label_4->setMinimumSize(QSize(80, 30));
        label_4->setMaximumSize(QSize(80, 30));
        label_4->setFont(font);

        horizontalLayout_18->addWidget(label_4);

        weightphoto = new QSpinBox(widget_7);
        weightphoto->setObjectName("weightphoto");
        weightphoto->setMinimumSize(QSize(105, 35));
        weightphoto->setMaximumSize(QSize(105, 35));
        weightphoto->setFont(font);
        weightphoto->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
        weightphoto->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);
        weightphoto->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        weightphoto->setMaximum(5000);

        horizontalLayout_18->addWidget(weightphoto);


        verticalLayout->addWidget(widget_7);

        widget_4 = new QWidget(scrollAreaWidgetContents);
        widget_4->setObjectName("widget_4");
        horizontalLayout_17 = new QHBoxLayout(widget_4);
        horizontalLayout_17->setObjectName("horizontalLayout_17");
        label_3 = new QLabel(widget_4);
        label_3->setObjectName("label_3");
        label_3->setMinimumSize(QSize(80, 30));
        label_3->setMaximumSize(QSize(80, 30));
        label_3->setFont(font);

        horizontalLayout_17->addWidget(label_3);

        highphoto = new QSpinBox(widget_4);
        highphoto->setObjectName("highphoto");
        highphoto->setMinimumSize(QSize(105, 35));
        highphoto->setMaximumSize(QSize(105, 35));
        highphoto->setFont(font);
        highphoto->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
        highphoto->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        highphoto->setMaximum(5000);

        horizontalLayout_17->addWidget(highphoto);


        verticalLayout->addWidget(widget_4);

        widget_5 = new QWidget(scrollAreaWidgetContents);
        widget_5->setObjectName("widget_5");
        horizontalLayout_3 = new QHBoxLayout(widget_5);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_5 = new QLabel(widget_5);
        label_5->setObjectName("label_5");
        label_5->setMinimumSize(QSize(80, 30));
        label_5->setMaximumSize(QSize(80, 30));
        label_5->setFont(font);

        horizontalLayout_3->addWidget(label_5);

        TriggerMode = new QComboBox(widget_5);
        TriggerMode->addItem(QString());
        TriggerMode->addItem(QString());
        TriggerMode->addItem(QString());
        TriggerMode->addItem(QString());
        TriggerMode->setObjectName("TriggerMode");
        TriggerMode->setMinimumSize(QSize(105, 35));
        TriggerMode->setMaximumSize(QSize(105, 35));
        TriggerMode->setFont(font);
        TriggerMode->setFocusPolicy(Qt::FocusPolicy::NoFocus);

        horizontalLayout_3->addWidget(TriggerMode);


        verticalLayout->addWidget(widget_5);

        widget_10 = new QWidget(scrollAreaWidgetContents);
        widget_10->setObjectName("widget_10");
        horizontalLayout_6 = new QHBoxLayout(widget_10);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_11 = new QLabel(widget_10);
        label_11->setObjectName("label_11");
        label_11->setMinimumSize(QSize(80, 30));
        label_11->setMaximumSize(QSize(80, 30));
        label_11->setFont(font);

        horizontalLayout_6->addWidget(label_11);

        Shutter_time = new QSpinBox(widget_10);
        Shutter_time->setObjectName("Shutter_time");
        Shutter_time->setMinimumSize(QSize(105, 35));
        Shutter_time->setMaximumSize(QSize(105, 35));
        Shutter_time->setFont(font);
        Shutter_time->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
        Shutter_time->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        Shutter_time->setMaximum(5000000);

        horizontalLayout_6->addWidget(Shutter_time);


        verticalLayout->addWidget(widget_10);

        widget_6 = new QWidget(scrollAreaWidgetContents);
        widget_6->setObjectName("widget_6");
        horizontalLayout_4 = new QHBoxLayout(widget_6);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_6 = new QLabel(widget_6);
        label_6->setObjectName("label_6");
        label_6->setMinimumSize(QSize(80, 30));
        label_6->setMaximumSize(QSize(80, 30));
        label_6->setFont(font);

        horizontalLayout_4->addWidget(label_6);

        TriggerSource = new QComboBox(widget_6);
        TriggerSource->addItem(QString());
        TriggerSource->addItem(QString());
        TriggerSource->addItem(QString());
        TriggerSource->addItem(QString());
        TriggerSource->addItem(QString());
        TriggerSource->setObjectName("TriggerSource");
        TriggerSource->setMinimumSize(QSize(105, 35));
        TriggerSource->setMaximumSize(QSize(105, 35));
        TriggerSource->setFont(font);
        TriggerSource->setFocusPolicy(Qt::FocusPolicy::NoFocus);

        horizontalLayout_4->addWidget(TriggerSource);


        verticalLayout->addWidget(widget_6);

        widget_8 = new QWidget(scrollAreaWidgetContents);
        widget_8->setObjectName("widget_8");
        horizontalLayout_2 = new QHBoxLayout(widget_8);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_7 = new QLabel(widget_8);
        label_7->setObjectName("label_7");
        label_7->setMinimumSize(QSize(80, 30));
        label_7->setMaximumSize(QSize(80, 30));
        label_7->setFont(font);

        horizontalLayout_2->addWidget(label_7);

        single_acquisition = new QPushButton(widget_8);
        single_acquisition->setObjectName("single_acquisition");
        single_acquisition->setMinimumSize(QSize(105, 35));
        single_acquisition->setMaximumSize(QSize(105, 35));
        single_acquisition->setFont(font);

        horizontalLayout_2->addWidget(single_acquisition);


        verticalLayout->addWidget(widget_8);

        widget_9 = new QWidget(scrollAreaWidgetContents);
        widget_9->setObjectName("widget_9");
        horizontalLayout_5 = new QHBoxLayout(widget_9);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_8 = new QLabel(widget_9);
        label_8->setObjectName("label_8");
        label_8->setMinimumSize(QSize(80, 30));
        label_8->setMaximumSize(QSize(80, 30));
        label_8->setFont(font);

        horizontalLayout_5->addWidget(label_8);

        continuous_acquisition = new QPushButton(widget_9);
        continuous_acquisition->setObjectName("continuous_acquisition");
        continuous_acquisition->setMinimumSize(QSize(105, 35));
        continuous_acquisition->setMaximumSize(QSize(105, 35));
        continuous_acquisition->setFont(font);

        horizontalLayout_5->addWidget(continuous_acquisition);


        verticalLayout->addWidget(widget_9);

        widget_11 = new QWidget(scrollAreaWidgetContents);
        widget_11->setObjectName("widget_11");
        horizontalLayout_7 = new QHBoxLayout(widget_11);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_10 = new QLabel(widget_11);
        label_10->setObjectName("label_10");
        label_10->setMinimumSize(QSize(80, 30));
        label_10->setMaximumSize(QSize(80, 30));
        label_10->setFont(font);

        horizontalLayout_7->addWidget(label_10);

        save_formal = new QComboBox(widget_11);
        save_formal->addItem(QString());
        save_formal->addItem(QString());
        save_formal->addItem(QString());
        save_formal->setObjectName("save_formal");
        save_formal->setMinimumSize(QSize(105, 35));
        save_formal->setMaximumSize(QSize(105, 35));
        save_formal->setFont(font);
        save_formal->setFocusPolicy(Qt::FocusPolicy::NoFocus);

        horizontalLayout_7->addWidget(save_formal);


        verticalLayout->addWidget(widget_11);

        widget_13 = new QWidget(scrollAreaWidgetContents);
        widget_13->setObjectName("widget_13");
        horizontalLayout_9 = new QHBoxLayout(widget_13);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        label_12 = new QLabel(widget_13);
        label_12->setObjectName("label_12");
        label_12->setMinimumSize(QSize(80, 30));
        label_12->setMaximumSize(QSize(80, 30));
        label_12->setFont(font);

        horizontalLayout_9->addWidget(label_12);

        save_location = new QPushButton(widget_13);
        save_location->setObjectName("save_location");
        save_location->setMinimumSize(QSize(105, 35));
        save_location->setMaximumSize(QSize(105, 35));
        save_location->setFont(font);

        horizontalLayout_9->addWidget(save_location);


        verticalLayout->addWidget(widget_13);

        widget_16 = new QWidget(scrollAreaWidgetContents);
        widget_16->setObjectName("widget_16");
        horizontalLayout_12 = new QHBoxLayout(widget_16);
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        label_9 = new QLabel(widget_16);
        label_9->setObjectName("label_9");
        label_9->setMinimumSize(QSize(80, 30));
        label_9->setMaximumSize(QSize(80, 30));
        QFont font2;
        font2.setPointSize(13);
        label_9->setFont(font2);
        label_9->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_12->addWidget(label_9);

        send_button = new QPushButton(widget_16);
        send_button->setObjectName("send_button");
        send_button->setMinimumSize(QSize(105, 35));
        send_button->setMaximumSize(QSize(105, 35));
        send_button->setFont(font);

        horizontalLayout_12->addWidget(send_button);


        verticalLayout->addWidget(widget_16);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_3->addWidget(scrollArea);

        widget_18 = new QWidget(widget_17);
        widget_18->setObjectName("widget_18");
        widget_18->setMinimumSize(QSize(280, 45));
        widget_18->setMaximumSize(QSize(280, 45));
        horizontalLayout_13 = new QHBoxLayout(widget_18);
        horizontalLayout_13->setSpacing(0);
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        horizontalLayout_13->setContentsMargins(0, 10, 0, 0);
        take_photo = new QPushButton(widget_18);
        take_photo->setObjectName("take_photo");
        take_photo->setMinimumSize(QSize(105, 35));
        take_photo->setMaximumSize(QSize(105, 35));
        take_photo->setFont(font);

        horizontalLayout_13->addWidget(take_photo);

        Exit_Button = new QPushButton(widget_18);
        Exit_Button->setObjectName("Exit_Button");
        Exit_Button->setMinimumSize(QSize(105, 35));
        Exit_Button->setMaximumSize(QSize(105, 35));
        Exit_Button->setFont(font);

        horizontalLayout_13->addWidget(Exit_Button);


        verticalLayout_3->addWidget(widget_18);


        horizontalLayout_11->addWidget(widget_17);


        verticalLayout_2->addWidget(widget_15);

        control_window->setCentralWidget(centralwidget);
        menubar = new QMenuBar(control_window);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 960, 22));
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
        menu->addAction(actionopen);
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
        actionopen->setText(QCoreApplication::translate("control_window", "\346\211\223\345\274\200", nullptr));
        actionexit->setText(QCoreApplication::translate("control_window", "\351\200\200\345\207\272", nullptr));
        find_device->setText(QCoreApplication::translate("control_window", "\346\237\245\346\211\276\350\256\276\345\244\207", nullptr));
        open_device->setText(QCoreApplication::translate("control_window", "\346\211\223\345\274\200\350\256\276\345\244\207", nullptr));
        open_btnSerialCheck->setText(QCoreApplication::translate("control_window", "\345\210\267\346\226\260", nullptr));
        open_openBt->setText(QCoreApplication::translate("control_window", "\350\277\236\346\216\245", nullptr));
        selectmode->setItemText(0, QCoreApplication::translate("control_window", "\347\241\254\344\273\266\346\213\215\347\205\247", nullptr));
        selectmode->setItemText(1, QCoreApplication::translate("control_window", "\350\275\257\344\273\266\346\213\215\347\205\247", nullptr));

        label_show_->setText(QCoreApplication::translate("control_window", "\346\230\276\347\244\272", nullptr));
        label->setText(QCoreApplication::translate("control_window", "\350\247\246\345\217\221\351\242\221\347\216\207", nullptr));
        label_2->setText(QCoreApplication::translate("control_window", "\350\247\246\345\217\221\344\270\252\346\225\260", nullptr));
        label_4->setText(QCoreApplication::translate("control_window", "\345\233\276\345\203\217\351\253\230\345\272\246", nullptr));
        label_3->setText(QCoreApplication::translate("control_window", "\345\233\276\345\203\217\345\256\275\345\272\246", nullptr));
        label_5->setText(QCoreApplication::translate("control_window", "\350\247\246\345\217\221\346\250\241\345\274\217", nullptr));
        TriggerMode->setItemText(0, QCoreApplication::translate("control_window", "\344\270\212\345\215\207\346\262\277", nullptr));
        TriggerMode->setItemText(1, QCoreApplication::translate("control_window", "\344\270\213\351\231\215\346\262\277", nullptr));
        TriggerMode->setItemText(2, QCoreApplication::translate("control_window", "\351\253\230\347\224\265\345\271\263", nullptr));
        TriggerMode->setItemText(3, QCoreApplication::translate("control_window", "\344\275\216\347\224\265\345\271\263", nullptr));

        label_11->setText(QCoreApplication::translate("control_window", "\345\277\253\351\227\250\351\200\237\345\272\246", nullptr));
        label_6->setText(QCoreApplication::translate("control_window", "\350\247\246\345\217\221\350\265\204\346\272\220", nullptr));
        TriggerSource->setItemText(0, QCoreApplication::translate("control_window", "line0", nullptr));
        TriggerSource->setItemText(1, QCoreApplication::translate("control_window", "line2", nullptr));
        TriggerSource->setItemText(2, QCoreApplication::translate("control_window", "\350\256\241\346\225\260\345\231\250\350\247\246\345\217\221", nullptr));
        TriggerSource->setItemText(3, QCoreApplication::translate("control_window", "\350\275\257\344\273\266\350\247\246\345\217\221", nullptr));
        TriggerSource->setItemText(4, QCoreApplication::translate("control_window", "\351\242\221\347\216\207\350\275\254\346\215\242\345\231\250\350\247\246\345\217\221", nullptr));

        label_7->setText(QCoreApplication::translate("control_window", "\351\207\207\351\233\206\346\250\241\345\274\217", nullptr));
        single_acquisition->setText(QCoreApplication::translate("control_window", "\345\215\225\346\254\241\351\207\207\351\233\206", nullptr));
        label_8->setText(QCoreApplication::translate("control_window", "\351\207\207\351\233\206", nullptr));
        continuous_acquisition->setText(QCoreApplication::translate("control_window", "\345\274\200\345\247\213\351\207\207\351\233\206", nullptr));
        label_10->setText(QCoreApplication::translate("control_window", "\344\277\235\345\255\230\346\240\274\345\274\217", nullptr));
        save_formal->setItemText(0, QCoreApplication::translate("control_window", "PNG", nullptr));
        save_formal->setItemText(1, QCoreApplication::translate("control_window", "BMP", nullptr));
        save_formal->setItemText(2, QCoreApplication::translate("control_window", "JPG", nullptr));

        label_12->setText(QCoreApplication::translate("control_window", "\344\277\235\345\255\230\350\256\276\347\275\256", nullptr));
        save_location->setText(QCoreApplication::translate("control_window", "\351\200\211\346\213\251", nullptr));
        label_9->setText(QCoreApplication::translate("control_window", "\350\247\246\345\217\221\345\217\221\351\200\201", nullptr));
        send_button->setText(QCoreApplication::translate("control_window", "\345\217\221\351\200\201", nullptr));
        take_photo->setText(QCoreApplication::translate("control_window", "\346\213\215\347\205\247", nullptr));
        Exit_Button->setText(QCoreApplication::translate("control_window", "\351\200\200\345\207\272", nullptr));
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
