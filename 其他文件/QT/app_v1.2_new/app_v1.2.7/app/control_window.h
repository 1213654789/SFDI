#ifndef CONTROL_WINDOW_H
#define CONTROL_WINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QString>
#include <QLabel>
#include <QWidget>

class MainWindow; // forward declaration to avoid including mainwindow.h in this header
#include "cmvcamera.h"
#include "mythread.h"
#include <QComboBox>
#include <QTimer>

class SaveWorker;
#include <QMetaObject>

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
    // Advanced button removed from UI
    void on_actionSerialHelper_triggered(); // 菜单项点击事件
    void on_actionabout_triggered();
    void on_actionexit_triggered();
    void on_actionopen_triggered();

    void on_find_device_clicked();

    void on_open_device_clicked();

    void on_close_device_clicked();

    void on_single_acquisition_clicked();

    void on_continuous_acquisition_clicked();


    // 保存格式由下拉框 `save_formal` 控制（替代原来的两个按钮）
    void on_save_formal_currentIndexChanged(int index);
    void on_save_location_clicked();

    // slots used by MyThread signals
    void slot_display();
    void slot_displayImage(QImage image);
    // spinbox value change handlers to apply image size
    void on_weightphoto_valueChanged(int val);
    void on_highphoto_valueChanged(int val);

    // 新增：快门/曝光时间 spinbox 改变处理
    void on_Shutter_time_valueChanged(int val);

    // UI handlers for trigger controls (if present in UI)
    void on_triggerMode_currentIndexChanged(int index);
    void on_triggerSource_currentIndexChanged(int index);

    // map combobox text to SDK numeric values
    int mapTriggerModeValue(const QString &text);
    int mapTriggerSourceValue(const QString &text);
    int mapTriggerActivationValue(const QString &text);

    void on_Exit_Button_clicked();

    void on_take_photo_clicked();

    void on_open_btnSerialCheck_clicked();

    void on_send_button_clicked();

    void on_open_openBt_clicked();

    void on_open_serailCb_currentIndexChanged(const QString &arg1);

    void on_selectmode_activated(int index);

private:
    Ui::control_window *ui;
    QWidget *m_advancedWindow = nullptr; // 简化为 QWidget，避免对 open_window 的链接依赖
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
    // debounce timestamp for continuous button (ms since epoch) -- kept for compatibility
    qint64 m_lastContinuousToggle = 0;

    // SaveWorker for async disk writes
    SaveWorker *m_saveWorker = nullptr;
    QMetaObject::Connection m_saveConn;

    // whether take_photo should also trigger send_button (hardware mode)
    bool m_takePhotoHardwareMode = false;



    // 保存图片的帮助函数
    void saveImage(const QString &format);

    // helper to close camera (used by unified open/close control)
    void closeCamera();
};

#endif // CONTROL_WINDOW_H
