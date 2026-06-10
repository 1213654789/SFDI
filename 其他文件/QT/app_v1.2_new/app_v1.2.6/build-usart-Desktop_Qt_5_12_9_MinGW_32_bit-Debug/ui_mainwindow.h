/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPlainTextEdit *recvEdit;
    QWidget *widget_6;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *serailCb;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QComboBox *baundrateCb;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QComboBox *databitCb;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QComboBox *stopbitCb;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QComboBox *checkbitCb;
    QTextEdit *sendEdit;
    QWidget *widget_8;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QWidget *widget_7;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *chk_rev_hex;
    QCheckBox *chk_rev_line;
    QPushButton *openBt;
    QPushButton *btnSerialCheck;
    QWidget *widget_9;
    QGridLayout *gridLayout_2;
    QPushButton *sendBt;
    QCheckBox *chk_send_hex;
    QCheckBox *chk_send_line;
    QPushButton *btnClearSend;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1800, 1300);
        MainWindow->setMinimumSize(QSize(1800, 1300));
        MainWindow->setMaximumSize(QSize(1800, 1300));
        QFont font;
        font.setPointSize(11);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        recvEdit = new QPlainTextEdit(centralwidget);
        recvEdit->setObjectName(QString::fromUtf8("recvEdit"));
        recvEdit->setGeometry(QRect(60, 60, 1200, 871));
        QFont font1;
        font1.setPointSize(15);
        recvEdit->setFont(font1);
        recvEdit->setReadOnly(true);
        widget_6 = new QWidget(centralwidget);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        widget_6->setGeometry(QRect(1320, 60, 436, 434));
        verticalLayout = new QVBoxLayout(widget_6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(widget_6);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(400, 70));
        widget->setMaximumSize(QSize(400, 70));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setEnabled(true);
        label->setMinimumSize(QSize(150, 45));
        label->setMaximumSize(QSize(150, 45));
        QFont font2;
        font2.setPointSize(16);
        label->setFont(font2);

        horizontalLayout->addWidget(label);

        serailCb = new QComboBox(widget);
        serailCb->setObjectName(QString::fromUtf8("serailCb"));
        serailCb->setMinimumSize(QSize(200, 54));
        serailCb->setMaximumSize(QSize(200, 54));
        serailCb->setFont(font2);

        horizontalLayout->addWidget(serailCb);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(widget_6);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMinimumSize(QSize(400, 70));
        widget_2->setMaximumSize(QSize(400, 70));
        horizontalLayout_3 = new QHBoxLayout(widget_2);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setEnabled(true);
        label_2->setMinimumSize(QSize(150, 45));
        label_2->setMaximumSize(QSize(150, 45));
        label_2->setFont(font2);

        horizontalLayout_3->addWidget(label_2);

        baundrateCb = new QComboBox(widget_2);
        baundrateCb->addItem(QString());
        baundrateCb->addItem(QString());
        baundrateCb->addItem(QString());
        baundrateCb->addItem(QString());
        baundrateCb->addItem(QString());
        baundrateCb->addItem(QString());
        baundrateCb->addItem(QString());
        baundrateCb->addItem(QString());
        baundrateCb->setObjectName(QString::fromUtf8("baundrateCb"));
        baundrateCb->setMinimumSize(QSize(200, 54));
        baundrateCb->setMaximumSize(QSize(200, 54));
        baundrateCb->setFont(font2);

        horizontalLayout_3->addWidget(baundrateCb);


        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(widget_6);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setMinimumSize(QSize(400, 70));
        widget_3->setMaximumSize(QSize(400, 70));
        widget_3->setFont(font2);
        horizontalLayout_2 = new QHBoxLayout(widget_3);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setEnabled(true);
        label_3->setMinimumSize(QSize(150, 45));
        label_3->setMaximumSize(QSize(150, 45));
        label_3->setFont(font2);

        horizontalLayout_2->addWidget(label_3);

        databitCb = new QComboBox(widget_3);
        databitCb->addItem(QString());
        databitCb->addItem(QString());
        databitCb->addItem(QString());
        databitCb->addItem(QString());
        databitCb->setObjectName(QString::fromUtf8("databitCb"));
        databitCb->setMinimumSize(QSize(200, 54));
        databitCb->setMaximumSize(QSize(200, 54));
        databitCb->setFont(font2);

        horizontalLayout_2->addWidget(databitCb);


        verticalLayout->addWidget(widget_3);

        widget_4 = new QWidget(widget_6);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setMinimumSize(QSize(400, 70));
        widget_4->setMaximumSize(QSize(400, 70));
        horizontalLayout_4 = new QHBoxLayout(widget_4);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(widget_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setEnabled(true);
        label_4->setMinimumSize(QSize(150, 45));
        label_4->setMaximumSize(QSize(150, 45));
        label_4->setFont(font2);

        horizontalLayout_4->addWidget(label_4);

        stopbitCb = new QComboBox(widget_4);
        stopbitCb->addItem(QString());
        stopbitCb->addItem(QString());
        stopbitCb->addItem(QString());
        stopbitCb->setObjectName(QString::fromUtf8("stopbitCb"));
        stopbitCb->setMinimumSize(QSize(200, 54));
        stopbitCb->setMaximumSize(QSize(200, 54));
        stopbitCb->setFont(font2);

        horizontalLayout_4->addWidget(stopbitCb);


        verticalLayout->addWidget(widget_4);

        widget_5 = new QWidget(widget_6);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setMinimumSize(QSize(400, 70));
        widget_5->setMaximumSize(QSize(400, 70));
        horizontalLayout_5 = new QHBoxLayout(widget_5);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(widget_5);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setEnabled(true);
        label_5->setMinimumSize(QSize(150, 45));
        label_5->setMaximumSize(QSize(150, 45));
        label_5->setFont(font2);

        horizontalLayout_5->addWidget(label_5);

        checkbitCb = new QComboBox(widget_5);
        checkbitCb->addItem(QString());
        checkbitCb->addItem(QString());
        checkbitCb->addItem(QString());
        checkbitCb->setObjectName(QString::fromUtf8("checkbitCb"));
        checkbitCb->setMinimumSize(QSize(200, 54));
        checkbitCb->setMaximumSize(QSize(200, 54));
        checkbitCb->setFont(font2);

        horizontalLayout_5->addWidget(checkbitCb);


        verticalLayout->addWidget(widget_5);

        sendEdit = new QTextEdit(centralwidget);
        sendEdit->setObjectName(QString::fromUtf8("sendEdit"));
        sendEdit->setGeometry(QRect(60, 970, 1200, 231));
        sendEdit->setFont(font1);
        widget_8 = new QWidget(centralwidget);
        widget_8->setObjectName(QString::fromUtf8("widget_8"));
        widget_8->setGeometry(QRect(1320, 520, 440, 241));
        gridLayout = new QGridLayout(widget_8);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton = new QPushButton(widget_8);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(200, 80));
        pushButton->setFont(font2);

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        widget_7 = new QWidget(widget_8);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        verticalLayout_2 = new QVBoxLayout(widget_7);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        chk_rev_hex = new QCheckBox(widget_7);
        chk_rev_hex->setObjectName(QString::fromUtf8("chk_rev_hex"));

        verticalLayout_2->addWidget(chk_rev_hex);

        chk_rev_line = new QCheckBox(widget_7);
        chk_rev_line->setObjectName(QString::fromUtf8("chk_rev_line"));

        verticalLayout_2->addWidget(chk_rev_line);


        gridLayout->addWidget(widget_7, 0, 1, 1, 1);

        openBt = new QPushButton(widget_8);
        openBt->setObjectName(QString::fromUtf8("openBt"));
        openBt->setMinimumSize(QSize(200, 80));
        openBt->setFont(font2);

        gridLayout->addWidget(openBt, 1, 0, 1, 1);

        btnSerialCheck = new QPushButton(widget_8);
        btnSerialCheck->setObjectName(QString::fromUtf8("btnSerialCheck"));
        btnSerialCheck->setMinimumSize(QSize(200, 80));
        btnSerialCheck->setFont(font2);

        gridLayout->addWidget(btnSerialCheck, 1, 1, 1, 1);

        widget_9 = new QWidget(centralwidget);
        widget_9->setObjectName(QString::fromUtf8("widget_9"));
        widget_9->setGeometry(QRect(1320, 1000, 440, 154));
        gridLayout_2 = new QGridLayout(widget_9);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(12);
        sendBt = new QPushButton(widget_9);
        sendBt->setObjectName(QString::fromUtf8("sendBt"));
        sendBt->setMinimumSize(QSize(200, 80));
        QFont font3;
        font3.setPointSize(22);
        sendBt->setFont(font3);

        gridLayout_2->addWidget(sendBt, 1, 0, 2, 1);

        chk_send_hex = new QCheckBox(widget_9);
        chk_send_hex->setObjectName(QString::fromUtf8("chk_send_hex"));

        gridLayout_2->addWidget(chk_send_hex, 0, 0, 1, 1);

        chk_send_line = new QCheckBox(widget_9);
        chk_send_line->setObjectName(QString::fromUtf8("chk_send_line"));

        gridLayout_2->addWidget(chk_send_line, 0, 1, 1, 1);

        btnClearSend = new QPushButton(widget_9);
        btnClearSend->setObjectName(QString::fromUtf8("btnClearSend"));
        btnClearSend->setMinimumSize(QSize(200, 80));
        btnClearSend->setFont(font3);

        gridLayout_2->addWidget(btnClearSend, 1, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1800, 37));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Serial Port Assistant", nullptr));
        label->setText(QApplication::translate("MainWindow", "\344\270\262  \345\217\243", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207", nullptr));
        baundrateCb->setItemText(0, QApplication::translate("MainWindow", "1200", nullptr));
        baundrateCb->setItemText(1, QApplication::translate("MainWindow", "2400", nullptr));
        baundrateCb->setItemText(2, QApplication::translate("MainWindow", "4800", nullptr));
        baundrateCb->setItemText(3, QApplication::translate("MainWindow", "9600", nullptr));
        baundrateCb->setItemText(4, QApplication::translate("MainWindow", "19200", nullptr));
        baundrateCb->setItemText(5, QApplication::translate("MainWindow", "38400", nullptr));
        baundrateCb->setItemText(6, QApplication::translate("MainWindow", "57600", nullptr));
        baundrateCb->setItemText(7, QApplication::translate("MainWindow", "115200", nullptr));

        baundrateCb->setCurrentText(QApplication::translate("MainWindow", "9600", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\344\275\215", nullptr));
        databitCb->setItemText(0, QApplication::translate("MainWindow", "5", nullptr));
        databitCb->setItemText(1, QApplication::translate("MainWindow", "6", nullptr));
        databitCb->setItemText(2, QApplication::translate("MainWindow", "7", nullptr));
        databitCb->setItemText(3, QApplication::translate("MainWindow", "8", nullptr));

        databitCb->setCurrentText(QApplication::translate("MainWindow", "8", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242\344\275\215", nullptr));
        stopbitCb->setItemText(0, QApplication::translate("MainWindow", "1", nullptr));
        stopbitCb->setItemText(1, QApplication::translate("MainWindow", "1.5", nullptr));
        stopbitCb->setItemText(2, QApplication::translate("MainWindow", "2", nullptr));

        label_5->setText(QApplication::translate("MainWindow", "\346\240\241\351\252\214\344\275\215", nullptr));
        checkbitCb->setItemText(0, QApplication::translate("MainWindow", "none", nullptr));
        checkbitCb->setItemText(1, QApplication::translate("MainWindow", "\345\245\207\346\240\241\351\252\214", nullptr));
        checkbitCb->setItemText(2, QApplication::translate("MainWindow", "\345\201\266\346\240\241\351\252\214", nullptr));

        pushButton->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272\346\216\245\346\224\266", nullptr));
        chk_rev_hex->setText(QApplication::translate("MainWindow", "HEX\346\216\245\346\224\266", nullptr));
        chk_rev_line->setText(QApplication::translate("MainWindow", "\350\207\252\345\212\250\346\215\242\350\241\214", nullptr));
        openBt->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        btnSerialCheck->setText(QApplication::translate("MainWindow", "\346\243\200\346\265\213\344\270\262\345\217\243", nullptr));
        sendBt->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        chk_send_hex->setText(QApplication::translate("MainWindow", "HEX\345\217\221\351\200\201", nullptr));
        chk_send_line->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201\346\215\242\350\241\214", nullptr));
        btnClearSend->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
