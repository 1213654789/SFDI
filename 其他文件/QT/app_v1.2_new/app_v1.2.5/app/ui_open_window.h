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
    QPushButton *open_btnSerialCheck;
    QPushButton *open_openBt;
    QSpinBox *open_freq;
    QSpinBox *open_times;

    void setupUi(QWidget *open_window)
    {
        if (open_window->objectName().isEmpty())
            open_window->setObjectName("open_window");
        open_window->resize(569, 535);
        advanced_setting_button = new QPushButton(open_window);
        advanced_setting_button->setObjectName("advanced_setting_button");
        advanced_setting_button->setEnabled(true);
        advanced_setting_button->setGeometry(QRect(280, 170, 161, 81));
        QFont font;
        font.setPointSize(20);
        advanced_setting_button->setFont(font);
        send_button = new QPushButton(open_window);
        send_button->setObjectName("send_button");
        send_button->setGeometry(QRect(350, 340, 171, 121));
        send_button->setFont(font);
        open_serailCb = new QComboBox(open_window);
        open_serailCb->setObjectName("open_serailCb");
        open_serailCb->setGeometry(QRect(30, 70, 181, 61));
        open_serailCb->setFont(font);
        open_btnSerialCheck = new QPushButton(open_window);
        open_btnSerialCheck->setObjectName("open_btnSerialCheck");
        open_btnSerialCheck->setGeometry(QRect(290, 70, 141, 71));
        open_btnSerialCheck->setFont(font);
        open_openBt = new QPushButton(open_window);
        open_openBt->setObjectName("open_openBt");
        open_openBt->setGeometry(QRect(20, 180, 171, 51));
        open_openBt->setFont(font);
        open_freq = new QSpinBox(open_window);
        open_freq->setObjectName("open_freq");
        open_freq->setGeometry(QRect(40, 290, 291, 91));
        open_freq->setFont(font);
        open_freq->setMaximum(1000);
        open_freq->setValue(500);
        open_times = new QSpinBox(open_window);
        open_times->setObjectName("open_times");
        open_times->setGeometry(QRect(40, 400, 291, 91));
        open_times->setFont(font);
        open_times->setMaximum(10000);
        open_times->setValue(8);

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
    } // retranslateUi

};

namespace Ui {
    class open_window: public Ui_open_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPEN_WINDOW_H
