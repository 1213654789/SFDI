#ifndef CONTROL_WINDOW_H
#define CONTROL_WINDOW_H

#include <QMainWindow>
#include "open_window.h"

namespace Ui {
class control_window;
}

class control_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit control_window(QWidget *parent = nullptr);
    ~control_window();

private slots:
    void on_Advanced_Button_clicked();
    void on_actionSerialHelper_triggered(); // 菜单项点击事件

private:
    Ui::control_window *ui;
    open_window *m_advancedWindow = nullptr; // 加这一行！
    MainWindow *m_serialWindow = nullptr;     // 串口助手
};

#endif // CONTROL_WINDOW_H
