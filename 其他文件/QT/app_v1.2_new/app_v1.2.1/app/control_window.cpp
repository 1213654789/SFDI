#include "control_window.h"
#include "open_window.h"
#include "mainwindow.h"
#include "ui_control_window.h"

control_window::control_window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::control_window)
{
    ui->setupUi(this);
}

control_window::~control_window()
{
    delete ui;
}

// 菜单“串口助手”点击事件
void control_window::on_actionSerialHelper_triggered()
{
    if (m_serialWindow) {
        m_serialWindow->show();
        m_serialWindow->raise();
        m_serialWindow->activateWindow();
        return;
    }

    m_serialWindow =  new MainWindow(this);
    connect(m_serialWindow, &QWidget::destroyed, this, [this]() {
        m_serialWindow = nullptr;
    });

    m_serialWindow->setAttribute(Qt::WA_DeleteOnClose);
    m_serialWindow->show();
}




void control_window::on_Advanced_Button_clicked()
{
        // 如果窗口已经存在 → 直接显示并置顶
    if (m_advancedWindow) {
        m_advancedWindow->show();
        m_advancedWindow->raise();
        m_advancedWindow->activateWindow();
        return;
    }

    // 不存在 → 创建新窗口
    m_advancedWindow = new open_window(this);
    // 关闭时自动清空指针，防止野指针
    connect(m_advancedWindow, &QWidget::destroyed, this, [=]() {
        m_advancedWindow = nullptr;
    });

    m_advancedWindow->setAttribute(Qt::WA_DeleteOnClose);
    m_advancedWindow->show();

}

