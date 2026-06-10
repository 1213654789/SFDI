#include "open_window.h"
#include "mainwindow.h"
#include "ui_open_window.h"

#include "qdebug.h"
    int a = 0;
open_window::open_window(QWidget *parent) :
    QWidget(parent),
//    ui(new Ui::open_window)
//{
//    ui->setupUi(this);

//}
    ui(new Ui::open_window),
    mainWin(nullptr)          // 添加初始化
    {
        ui->setupUi(this);
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
    for (int i = 0; i < 10; ++i) {
    mainWin->setSendEditText("FF");
    mainWin->setSendEditText("AF");
    }

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

   qDebug() << "打开串口按钮被点击";
}

void open_window::on_open_serailCb_currentIndexChanged(const QString &arg1)
{
    // 当用户在主窗口选择新串口时，同步到子窗口（如果已创建）
       if (mainWin) {
           mainWin->setCurrentSerialPort(arg1);
       }
}
