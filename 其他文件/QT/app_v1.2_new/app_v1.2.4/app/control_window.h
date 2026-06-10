#ifndef CONTROL_WINDOW_H
#define CONTROL_WINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QString>
#include <QLabel>
#include "open_window.h"
#include "cmvcamera.h"
#include "mythread.h"
#include <QComboBox>
#include <QTimer>

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
    void on_actionabout_triggered();
    void on_actionexit_triggered();

    void on_find_device_clicked();

    void on_open_device_clicked();

    void on_close_device_clicked();

    void on_single_acquisition_clicked();

    void on_continuous_acquisition_clicked();

    void on_stops_acquisition_clicked();

    void on_save_BMP_clicked();

    void on_save_PNG_clicked();
    void on_save_location_clicked();

    // slots used by MyThread signals
    void slot_display();
    void slot_displayImage(QImage image);
    // spinbox value change handlers to apply image size
    void on_weightphoto_valueChanged(int val);
    void on_highphoto_valueChanged(int val);

    // UI handlers for trigger controls (if present in UI)
    void on_triggerMode_currentIndexChanged(int index);
    void on_triggerSource_currentIndexChanged(int index);

    // map combobox text to SDK numeric values
    int mapTriggerModeValue(const QString &text);
    int mapTriggerSourceValue(const QString &text);
    int mapTriggerActivationValue(const QString &text);

    void on_Exit_Button_clicked();

    void on_open_btnSerialCheck_clicked();

    void on_send_button_clicked();

    void on_open_openBt_clicked();

    void on_open_serailCb_currentIndexChanged(const QString &arg1);

private:
    Ui::control_window *ui;
    open_window *m_advancedWindow = nullptr; // 加这一行！
    MainWindow *m_serialWindow = nullptr;     // 串口助手

    QTimer *m_serialPollTimer = nullptr;
    QStringList m_lastSerialPorts;

    bool m_bOpenDevice;
    MV_CC_DEVICE_INFO_LIST m_stDevList;
    CMvCamera *m_pcMyCamera = NULL;
    MyThread *myThread = NULL;
    QImage *myImage = NULL;
    QString m_savePath;
    QLabel *m_statusLabel = nullptr;

    // 保存图片的帮助函数
    void saveImage(const QString &format);

    // helper to close camera (used by unified open/close control)
    void closeCamera();
};

#endif // CONTROL_WINDOW_H
