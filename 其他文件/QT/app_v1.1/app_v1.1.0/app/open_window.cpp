#include "open_window.h"
#include "mainwindow.h"
#include "ui_open_window.h"

#include <QTimer>
#include <QSerialPortInfo>
#include <memory>
#include <algorithm>
#include "timerthread.h"

#include "qdebug.h"
    int a = 0;




open_window::open_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::open_window),
    mainWin(nullptr)          // 添加初始化
    {
        ui->setupUi(this);
        on_open_btnSerialCheck_clicked();
    }



open_window::~open_window()
{
    delete ui;
}








void open_window::on_advanced_setting_button_clicked()
{
    if (mainWin == nullptr) {
           mainWin = new MainWindow(this);
       }
    mainWin->show(); // 显示 MainWindow 窗口
}

void open_window::on_send_button_clicked()
{
    // 如果子窗口尚未创建，则创建它（但不显示）
    if (!mainWin) {
       mainWin = new MainWindow(this);
       // 注意：这里不调用 show()，窗口保持隐藏
    }
    // 调用子窗口的公共方法，向 sendEdit 写入 "FF"
    int freq = ui->open_freq->value();
    int times = ui->open_times->value();

    // 使用获取的值，例如打印或计算
    qDebug() << "Frequency:" << freq << "Times:" << times;

//    mainWin->setSendEditText("A");
//    mainWin->setSendEditText(QString::number(freq));
//    mainWin->setSendEditText("B");
//    mainWin->setSendEditText(QString::number(times));
//    mainWin->setSendEditText("C");


    //QString message = QString("A%1B%2C").arg(freq).arg(times);

    // 根据需求使用高精度定时器（TimerThread），支持子毫秒精度。
    // 发送次数由 times 决定（每个周期发送两个消息），freq 视为 Hz，周期 = 1/freq 秒。
    if (times <= 0) {
        qDebug() << "Times <= 0, nothing to send";
    } else {
        // 计算半周期（微秒）
        unsigned int half_us = 500; // 默认 500us
        if (freq > 0) {
            double period_us = 1000000.0 / static_cast<double>(freq);
            double half = period_us / 2.0;
            half_us = static_cast<unsigned int>(std::max(1.0, std::round(half)));
        }

        // 计数和消息
        auto counter = std::make_shared<int>(0);
        const int maxCount = times * 2;
        const QString msg1 = QString("message");
        const QString msg2 = QString("mege");

        // 立即发送 msg1
        if (this->mainWin) {
            this->mainWin->setSendEditText(msg1);
            (*counter)++;
        }

        if (*counter >= maxCount) {
            qDebug() << "Send complete immediately";
        } else {
            // 创建高精度定时器线程，回调在 Qt 主线程执行
            // 使用 shared_ptr 管理 TimerThread 的生命周期，回调捕获 shared_ptr 的副本以保证安全
            auto ht = std::shared_ptr<TimerThread>(new TimerThread(half_us));

            // 定义回调，捕获 shared_ptr ht 的副本
            std::function<void()> cb = [this, counter, maxCount, msg1, msg2, ht]() mutable {
                if (!this->mainWin) return;

                if (((*counter) % 2) == 1) {
                    this->mainWin->setSendEditText(msg2);
                } else {
                    this->mainWin->setSendEditText(msg1);
                }

                (*counter)++;
                if (*counter >= maxCount) {
                    ht->stop();
                    const_cast<std::shared_ptr<TimerThread>&>(ht).reset();
                }
            };

            ht->setCallback(cb);
            ht->start();
        }
    }

    // 在已有文本后追加带换行的内容


    //mainWin->setSendEditText("start");

    qDebug() << a++;
}

void open_window::on_open_btnSerialCheck_clicked()
{
    // 刷新自己的下拉框
    ui->open_serailCb->clear();
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->open_serailCb->addItem(info.portName());
    }

    // 如果子窗口已创建，同步刷新其列表
    if (mainWin) {
        mainWin->refreshSerialPorts();
    }

}



void open_window::on_open_openBt_clicked()
{
    // 如果子窗口尚未创建，则创建（但隐藏）
   if (!mainWin) {
       mainWin = new MainWindow(this);
       // 创建后同步当前串口选择（使子窗口使用主窗口选中的串口）
       mainWin->setCurrentSerialPort(ui->open_serailCb->currentText());
   }

   // 调用子窗口的打开串口方法
   mainWin->openSerialPort();

   if(ui->open_openBt->text() == "连接")
   {
          ui->open_openBt->setText("关闭");
          ui->open_openBt->setStyleSheet("color: red;");
          // 让端口号下拉框不可选，避免误操作（选择功能不可用，控件背景为灰色）
          ui->open_serailCb->setEnabled(false);
          ui->open_btnSerialCheck->setEnabled(false);
   }
   else
   {

       //serialPort->close();
       ui->open_openBt->setText("连接");
       ui->open_openBt->setStyleSheet("color: black;");
       // 端口号下拉框恢复可选，避免误操作
       ui->open_serailCb->setEnabled(true);
       ui->open_btnSerialCheck->setEnabled(true);
   }

}



void open_window::on_open_serailCb_currentIndexChanged(const QString &arg1)
{
    // 当用户在主窗口选择新串口时，同步到子窗口（如果已创建）
       if (mainWin) {
           mainWin->setCurrentSerialPort(arg1);
       }
}
