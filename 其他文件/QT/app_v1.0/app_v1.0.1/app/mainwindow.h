#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QString>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QTimer>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QSerialPort *serialPort;//定义串口指针

    /////////////
public:
        void setSendEditText(const QString &text);

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
