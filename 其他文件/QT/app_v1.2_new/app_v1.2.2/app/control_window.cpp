#include "control_window.h"
#include "open_window.h"
#include "mainwindow.h"
#include "ui_control_window.h"
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include <QPixmap>
#include <QImage>
#include <QDateTime>

control_window::control_window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::control_window)
{
    ui->setupUi(this);
    // Ensure widgets and resources (myThread, myImage, etc.) are initialized
    initWidget();
}

control_window::~control_window()
{
    delete ui;
}




void control_window::initWidget()
{
    //设置窗口属性
    this->setWindowTitle("相机测试");
    this->setWindowFlags(Qt::WindowCloseButtonHint | Qt::Dialog);
    this->setWindowModality(Qt::ApplicationModal);
    this->setFixedSize(this->width(),this->height());

    //初始化变量
    m_bOpenDevice = false;

    //生成保存图片的文件夹
    QString imagePath = QDir::currentPath() + "/myImage/";
    QDir dstDir(imagePath);
    if(!dstDir.exists())
    {
        if(!dstDir.mkdir(imagePath))
        {
            qDebug()<<"创建Image文件夹失败！";
            //return;
        }
    }

    //图像指针对象（使用QImage，cmvcamera 已用 QImage）
    myImage = new QImage();

    //线程对象实例化
    myThread = new MyThread();
    connect(myThread,SIGNAL(signal_message()),this,SLOT(slot_display()));
    connect(myThread,SIGNAL(signal_messImage(QImage)),this,SLOT(slot_displayImage(QImage)));
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


void control_window::on_find_device_clicked()
{
    ui->choose_devices->clear();
    memset(&m_stDevList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));

    //枚举子网内所有设备
    int nRet = CMvCamera::EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE,&m_stDevList);
    if (MV_OK != nRet)
    {
        return;
    }
    for(unsigned int i = 0; i < m_stDevList.nDeviceNum; i++)
    {
        MV_CC_DEVICE_INFO* pDeviceInfo = m_stDevList.pDeviceInfo[i];
        QString strModelName = "";
        if(pDeviceInfo->nTLayerType == MV_USB_DEVICE)
        {
            strModelName = (char*)pDeviceInfo->SpecialInfo.stUsb3VInfo.chModelName;
        }
        else if(pDeviceInfo->nTLayerType == MV_GIGE_DEVICE)
        {
            strModelName = (char*)pDeviceInfo->SpecialInfo.stGigEInfo.chModelName;
        }
        else
        {
            QMessageBox::warning(this,"警告","未知设备枚举！");
            return;
        }
        qDebug()<<"strModelName:"<<strModelName;
        ui->choose_devices->addItem(strModelName);
    }
}


void control_window::on_open_device_clicked()
{
    if(m_bOpenDevice)
    {
        return;
    }
    QString deviceModel = ui->choose_devices->currentText();
    if(deviceModel == "")
    {
        QMessageBox::warning(this,"警告","请选择设备！");
        return;
    }
    m_pcMyCamera = new CMvCamera;
    if(NULL == m_pcMyCamera)
    {
        return;
    }
    int nIndex = ui->choose_devices->currentIndex();
    //打开设备
    int nRet = m_pcMyCamera->Open(m_stDevList.pDeviceInfo[nIndex]);
    qDebug()<<"Connect:"<<nRet;
    if(MV_OK != nRet)
    {
        delete m_pcMyCamera;
        m_pcMyCamera = NULL;
        QMessageBox::warning(this,"警告","打开设备失败！");
        return;
    }
    //设置为触发模式
    qDebug()<<"TriggerMode:"<<m_pcMyCamera->SetEnumValue("TriggerMode",1);
    //设置触发源为软触发
    qDebug()<<"TriggerSource:"<<m_pcMyCamera->SetEnumValue("TriggerSource",7);
    //设置曝光时间
    qDebug()<<"SetExposureTime:"<<m_pcMyCamera->SetFloatValue("ExposureTime",5000);
    //开启相机采集
    qDebug()<<"StartCamera:"<<m_pcMyCamera->StartGrabbing();

    myThread->getCameraPtr(m_pcMyCamera);
    myThread->getImagePtr(myImage);

    m_bOpenDevice = true;

}


void control_window::on_close_device_clicked()
{
    if(m_pcMyCamera)
    {
        m_pcMyCamera->Close();
        delete m_pcMyCamera;
        m_pcMyCamera = NULL;
        m_bOpenDevice = false;
    }
}


void control_window::on_single_acquisition_clicked()
{
    if(!m_bOpenDevice)
    {
        QMessageBox::warning(this,"警告","采集失败,请打开设备！");
        return;
    }

    //发送软触发
    qDebug()<<"single SoftTrigger:"<<m_pcMyCamera->CommandExecute("TriggerSoftware");
    //读取QImage格式的图像
    QImage image;
    qDebug()<<"single ReadBuffer:"<<m_pcMyCamera->ReadBuffer(image);
    // 显示并保存到当前缓冲，以便后续保存操作使用
    slot_displayImage(image);
    if(myImage)
        *myImage = image;
}


void control_window::on_continuous_acquisition_clicked()
{
    if(!m_bOpenDevice)
    {
        QMessageBox::warning(this,"警告","采集失败,请打开设备！");
        return;
    }

    if(!myThread->isRunning())
    {
        myThread->start();
    }
}


void control_window::on_stops_acquisition_clicked()
{
    if(myThread->isRunning())
    {
        myThread->requestInterruption();
        myThread->wait();
    }
}


void control_window::on_save_BMP_clicked()
{
    saveImage("bmp");   //文件较大
}


void control_window::on_save_PNG_clicked()
{
    saveImage("png");   //文件较小
}


void control_window::slot_display()
{
    // 占位——目前无text-only display
}

void control_window::slot_displayImage(QImage image)
{
    if(image.isNull()) return;
    QPixmap pix = QPixmap::fromImage(image).scaled(ui->label_show_->size(), Qt::KeepAspectRatio);
    ui->label_show_->setPixmap(pix);
    // 更新当前缓冲图像，供保存使用
    if(myImage)
        *myImage = image;
}

void control_window::saveImage(const QString &format)
{
    if(!myImage || myImage->isNull()){
        QMessageBox::warning(this, "警告", "没有可保存的图像！");
        return;
    }
    QString savePath = QDir::currentPath() + "/myImage/";
    QString curDate = QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss.zzz");
    QString saveName = savePath + curDate + "." + format;
    myImage->save(saveName, format.toUpper().toUtf8().constData());
}

