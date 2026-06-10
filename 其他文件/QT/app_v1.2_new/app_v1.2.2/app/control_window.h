#ifndef CONTROL_WINDOW_H
#define CONTROL_WINDOW_H

#include <QMainWindow>
#include <QImage>
#include "open_window.h"
#include "cmvcamera.h"
#include "mythread.h"

namespace Ui {
class control_window;
}

class control_window : public QMainWindow
{
    Q_OBJECT


public:
     void initWidget();

public:
    explicit control_window(QWidget *parent = nullptr);
    ~control_window();

private slots:
    void on_Advanced_Button_clicked();
    void on_actionSerialHelper_triggered(); // 菜单项点击事件

    void on_find_device_clicked();

    void on_open_device_clicked();

    void on_close_device_clicked();

    void on_single_acquisition_clicked();

    void on_continuous_acquisition_clicked();

    void on_stops_acquisition_clicked();

    void on_save_BMP_clicked();

    void on_save_PNG_clicked();

    // slots used by MyThread signals
    void slot_display();
    void slot_displayImage(QImage image);

private:
    Ui::control_window *ui;
    open_window *m_advancedWindow = nullptr; // 加这一行！
    MainWindow *m_serialWindow = nullptr;     // 串口助手

    bool m_bOpenDevice;
    MV_CC_DEVICE_INFO_LIST m_stDevList;
    CMvCamera *m_pcMyCamera = NULL;
    MyThread *myThread = NULL;
    QImage *myImage = NULL;

    // 保存图片的帮助函数
    void saveImage(const QString &format);
};

#endif // CONTROL_WINDOW_H
