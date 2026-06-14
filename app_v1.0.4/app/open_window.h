#ifndef OPEN_WINDOW_H
#define OPEN_WINDOW_H

#include <QMainWindow>
#include "mainwindow.h"
// Forward declaration of UI class (generated header defines Ui::mainWindow)
namespace Ui { class mainWindow; }

class open_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit open_window(QWidget *parent = nullptr);
    ~open_window();

signals:
    // 声明自定义信号：通知主窗口填入FF
    void sendFFToMainWindow();
    // open_window.h


private slots:
    void on_advanced_setting_button_clicked();

    void on_send_button_clicked();

    void on_open_btnSerialCheck_clicked();

    void on_open_openBt_clicked();

    void on_open_serailCb_currentIndexChanged(const QString &arg1);

    void on_action_triggered();

private:
    Ui::mainWindow *ui;
    MainWindow *mainWin = nullptr; // 声明 MainWindow 指针
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // OPEN_WINDOW_H
