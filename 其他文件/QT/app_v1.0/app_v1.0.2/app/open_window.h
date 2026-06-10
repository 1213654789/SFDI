#ifndef OPEN_WINDOW_H
#define OPEN_WINDOW_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class open_window;
}

class open_window : public QWidget
{
    Q_OBJECT

public:
    explicit open_window(QWidget *parent = nullptr);
    ~open_window();

signals:
    // 声明自定义信号：通知主窗口填入FF
    void sendFFToMainWindow();

private slots:
    void on_advanced_setting_button_clicked();

    void on_send_button_clicked();

    void on_open_btnSerialCheck_clicked();

    void on_open_openBt_clicked();

    void on_open_serailCb_currentIndexChanged(const QString &arg1);

private:
    Ui::open_window *ui;
    MainWindow *mainWin = nullptr; // 声明 MainWindow 指针
};

#endif // OPEN_WINDOW_H
