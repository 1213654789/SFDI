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
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_open_window
{
public:
    QPushButton *advanced_setting_button;
    QPushButton *send_button;
    QComboBox *open_serailCb;
    QSpinBox *open_freq;
    QSpinBox *open_times;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *open_btnSerialCheck;
    QPushButton *open_openBt;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *open_window)
    {
        if (open_window->objectName().isEmpty())
            open_window->setObjectName("open_window");
        open_window->resize(569, 381);
        advanced_setting_button = new QPushButton(open_window);
        advanced_setting_button->setObjectName("advanced_setting_button");
        advanced_setting_button->setEnabled(true);
        advanced_setting_button->setGeometry(QRect(280, 280, 250, 71));
        advanced_setting_button->setMinimumSize(QSize(0, 0));
        advanced_setting_button->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setPointSize(20);
        advanced_setting_button->setFont(font);
        send_button = new QPushButton(open_window);
        send_button->setObjectName("send_button");
        send_button->setGeometry(QRect(290, 160, 250, 70));
        send_button->setFont(font);
        open_serailCb = new QComboBox(open_window);
        open_serailCb->setObjectName("open_serailCb");
        open_serailCb->setGeometry(QRect(10, 40, 250, 70));
        open_serailCb->setMinimumSize(QSize(0, 0));
        open_serailCb->setMaximumSize(QSize(16777215, 16777215));
        open_serailCb->setFont(font);
        open_freq = new QSpinBox(open_window);
        open_freq->setObjectName("open_freq");
        open_freq->setGeometry(QRect(10, 160, 250, 70));
        open_freq->setMinimumSize(QSize(250, 70));
        open_freq->setMaximumSize(QSize(250, 70));
        open_freq->setFont(font);
        open_freq->setMaximum(1000);
        open_freq->setValue(500);
        open_times = new QSpinBox(open_window);
        open_times->setObjectName("open_times");
        open_times->setGeometry(QRect(10, 280, 250, 70));
        open_times->setMinimumSize(QSize(250, 70));
        open_times->setMaximumSize(QSize(250, 70));
        open_times->setFont(font);
        open_times->setMaximum(20);
        open_times->setValue(8);
        widget = new QWidget(open_window);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(290, 30, 271, 91));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        open_btnSerialCheck = new QPushButton(widget);
        open_btnSerialCheck->setObjectName("open_btnSerialCheck");
        open_btnSerialCheck->setMinimumSize(QSize(110, 70));
        open_btnSerialCheck->setMaximumSize(QSize(16777215, 16777215));
        open_btnSerialCheck->setFont(font);

        horizontalLayout->addWidget(open_btnSerialCheck);

        open_openBt = new QPushButton(widget);
        open_openBt->setObjectName("open_openBt");
        open_openBt->setMinimumSize(QSize(110, 70));
        open_openBt->setMaximumSize(QSize(16777215, 16777215));
        open_openBt->setFont(font);

        horizontalLayout->addWidget(open_openBt);

        label = new QLabel(open_window);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 120, 141, 31));
        label->setFont(font);
        label_2 = new QLabel(open_window);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 240, 141, 31));
        label_2->setFont(font);

        retranslateUi(open_window);

        QMetaObject::connectSlotsByName(open_window);
    } // setupUi

    void retranslateUi(QWidget *open_window)
    {
        open_window->setWindowTitle(QCoreApplication::translate("open_window", "Form", nullptr));
        advanced_setting_button->setText(QCoreApplication::translate("open_window", "\351\253\230\347\272\247\350\256\276\347\275\256", nullptr));
        send_button->setText(QCoreApplication::translate("open_window", "\345\217\221\351\200\201", nullptr));
        open_btnSerialCheck->setText(QCoreApplication::translate("open_window", "\345\210\267\346\226\260", nullptr));
        open_openBt->setText(QCoreApplication::translate("open_window", "\350\277\236\346\216\245", nullptr));
        label->setText(QCoreApplication::translate("open_window", "\351\242\221\347\216\207", nullptr));
        label_2->setText(QCoreApplication::translate("open_window", "\344\270\252\346\225\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class open_window: public Ui_open_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPEN_WINDOW_H
