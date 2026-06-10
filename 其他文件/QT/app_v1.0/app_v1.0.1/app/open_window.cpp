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

    // 在 open_window 构造函数中手动连接
    //connect(ui->send_button, &QPushButton::clicked, this, &open_window::on_send_button_clicked);
    qDebug() << a++;
}
