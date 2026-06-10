#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QString>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QTimer>
#include <QPainter>
#include <mutex>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Thread-safe direct write from worker thread. Returns number of bytes written or -1 on error.
    qint64 sendBytesDirect(const QByteArray &data);



    QSerialPort *serialPort;//定义串口指针
    std::mutex serialWriteMutex;

    /////////////
public:
    void setSendEditText(const QString &text);
    // mainwindow.h
public:
    bool openSerialPort();   // 公共方法，用于外部调用打开串口，返回是否打开成功

public:
    void refreshSerialPorts();               // 刷新串口列表
    void setCurrentSerialPort(const QString &portName); // 设置当前选中串口
    QString getCurrentSerialPort() const;    // 获取当前选中串口（可选）

        /////////////////

private slots:

    /*手动连接槽函数*/
    void manual_serialPortReadyRead();

    void on_openBt_clicked();

    void on_sendBt_clicked();

    void on_btnClearSend_clicked();

    void on_btnSerialCheck_clicked();



    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    long sendNum, recvNum;
    QLabel *lblSendNum;
    QLabel *lblRecvNum;
    QLabel *lblPortState;
    void setNumOnLabel(QLabel *lbl, QString strS, long num);


};
#endif // MAINWINDOW_H
