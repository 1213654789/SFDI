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
#include <QVBoxLayout>
#include <QFont>
#include <QLabel>
#include <QFileDialog>
#include <QSettings>

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







int control_window::mapTriggerModeValue(const QString &text)
{
    // Map human-readable combobox text to SDK integer values for TriggerMode
    // Common mapping (please adjust to your SDK's exact meanings):
    // "Off" -> 0, "On" -> 1
    if (text.compare("Off", Qt::CaseInsensitive) == 0) return 0;
    if (text.compare("On", Qt::CaseInsensitive) == 0) return 1;
    // fallback: try to parse as number
    bool ok = false;
    int v = text.toInt(&ok);
    return ok ? v : 1; // default to 1
}

int control_window::mapTriggerSourceValue(const QString &text)
{
    // Map combobox display text to SDK values for TriggerSource
    // Device supports 0 (Line0/Hardware) and 2 (Software)
    if (text.contains("Software", Qt::CaseInsensitive) || text.compare("Soft", Qt::CaseInsensitive) == 0) return 7; // software trigger -> 7
    if (text.contains("Hardware", Qt::CaseInsensitive) || text.compare("Hard", Qt::CaseInsensitive) == 0) return 0; // line0 -> 0
    if (text.contains("Line2", Qt::CaseInsensitive) || text.contains("line2", Qt::CaseInsensitive)) return 2; // line2 -> 2
    if (text.contains("Counter", Qt::CaseInsensitive) || text.contains("计数器", Qt::CaseInsensitive)) return 4; // counter trigger -> 4
    if (text.contains("FreqConverter", Qt::CaseInsensitive) || text.contains("频率转换器", Qt::CaseInsensitive)) return 8; // frequency converter -> 8
    // numeric fallback
    bool ok = false;
    int v = text.toInt(&ok);
    return ok ? v : 2; // default to software
}

int control_window::mapTriggerActivationValue(const QString &text)
{
    // Map activation type strings to SDK integers
    if (text.contains("Rising", Qt::CaseInsensitive) || text.contains("上升", Qt::CaseInsensitive)) return 0;
    if (text.contains("Falling", Qt::CaseInsensitive) || text.contains("下降", Qt::CaseInsensitive)) return 1;
    if (text.contains("High", Qt::CaseInsensitive) || text.contains("高电平", Qt::CaseInsensitive)) return 2;
    if (text.contains("Low", Qt::CaseInsensitive) || text.contains("低电平", Qt::CaseInsensitive)) return 3;
    bool ok = false;
    int v = text.toInt(&ok);
    return ok ? v : 0;
}





void control_window::on_actionexit_triggered()
{
    // Gracefully stop thread if running
    if (myThread && myThread->isRunning()) {
        myThread->requestInterruption();
        myThread->wait();
    }

    // Close camera if open
    if (m_pcMyCamera) {
        m_pcMyCamera->StopGrabbing();
        m_pcMyCamera->Close();
        delete m_pcMyCamera;
        m_pcMyCamera = nullptr;
    }

    // delete image buffer
    if (myImage) {
        delete myImage;
        myImage = nullptr;
    }

    qApp->quit();
}

// Note: About dialog is handled by `on_actionabout_triggered` which is
// connected to the UI action `actionabout` generated in the .ui file.

void control_window::on_actionabout_triggered()
{
    // Show a custom About dialog so size and font can be controlled
    QDialog dlg(this);
    dlg.setWindowTitle("关于");
    dlg.setFixedSize(300, 180); // adjust size as needed
    QVBoxLayout *layout = new QVBoxLayout(&dlg);
    layout->setContentsMargins(12, 12, 12, 12);
    QLabel *label = new QLabel("XXX\n导师：\n学长：\n2026.6.1", &dlg);
    QFont font = label->font();
    font.setPointSize(14); // restore desired font size
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
    dlg.setLayout(layout);
    dlg.exec();
}



void control_window::initWidget()
{
    //设置窗口属性
    this->setWindowTitle("相机测试");
    // keep default window flags but ensure close button is available
    this->setWindowFlags(this->windowFlags() | Qt::WindowCloseButtonHint);
    this->setFixedSize(this->width(),this->height());

    //初始化变量
    m_bOpenDevice = false;

    // Load last save path from local ini file in application folder (do not use registry)
    QString cfgPath = QCoreApplication::applicationDirPath() + "/settings.ini";
    QSettings settings(cfgPath, QSettings::IniFormat);
    m_savePath = settings.value("savePath", QDir::currentPath() + "/myImage/").toString();
    // ensure directory exists
    QDir dir(m_savePath);
    if (!dir.exists()) {
        // try to create as-is; if fails, try appending a "Photo" subfolder
        if (!dir.mkpath(m_savePath)) {
            QString photoSub = QDir(m_savePath).filePath("Photo");
            QDir d2(photoSub);
            if (!d2.exists()) d2.mkpath(photoSub);
            m_savePath = photoSub;
        }
    }
    // show current save path in status bar
    if (this->statusBar()) {
        this->statusBar()->showMessage(tr("%1").arg(m_savePath));
    }

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
    myThread = new MyThread(this);
    connect(myThread,SIGNAL(signal_message()),this,SLOT(slot_display()));
    connect(myThread,SIGNAL(signal_messImage(QImage)),this,SLOT(slot_displayImage(QImage)));

    // Restore saved UI control values (if any)
    if (ui) {
        // Trigger mode/source indices (defaults to 0)
        if (ui->TriggerMode) {
            int savedMode = settings.value("TriggerModeIndex", ui->TriggerMode->currentIndex()).toInt();
            ui->TriggerMode->setCurrentIndex(savedMode);
        }
        if (ui->TriggerSource) {
            int savedSource = settings.value("TriggerSourceIndex", ui->TriggerSource->currentIndex()).toInt();
            ui->TriggerSource->setCurrentIndex(savedSource);
        }

        // Weight / High spinbox values (defaults to current label size)
        int savedW = settings.value("WeightPhoto", ui->label_show_ ? ui->label_show_->width() : 640).toInt();
        int savedH = settings.value("HighPhoto", ui->label_show_ ? ui->label_show_->height() : 480).toInt();
        ui->weightphoto->setValue(savedW);
        ui->highphoto->setValue(savedH);
        if (ui->label_show_) {
            ui->label_show_->setFixedSize(savedW, savedH);
        }
    }

    // If trigger mode/source comboboxes exist in UI, initialize them and connect
    if (ui->centralwidget) {
        if (this->findChild<QComboBox*>("triggerMode")) {
            QComboBox *cb = this->findChild<QComboBox*>("triggerMode");
            connect(cb, SIGNAL(currentIndexChanged(int)), this, SLOT(on_triggerMode_currentIndexChanged(int)));
        }
        if (this->findChild<QComboBox*>("triggerSource")) {
            QComboBox *cb2 = this->findChild<QComboBox*>("triggerSource");
            connect(cb2, SIGNAL(currentIndexChanged(int)), this, SLOT(on_triggerSource_currentIndexChanged(int)));
        }
    }
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
    // 根据 UI combobox（如果存在）设置 TriggerMode/TriggerSource/TriggerActivation，否则使用默认值
    int setModeVal = 1; // default On
    QComboBox *cbMode = this->findChild<QComboBox*>("triggerMode");
    if (cbMode) {
        setModeVal = mapTriggerModeValue(cbMode->currentText());
    }
    qDebug() << "TriggerMode:" << m_pcMyCamera->SetEnumValue("TriggerMode", setModeVal);

    int setSourceVal = 7; // default software trigger per SDK mapping
    QComboBox *cbSource = this->findChild<QComboBox*>("triggerSource");
    if (cbSource) {
        setSourceVal = mapTriggerSourceValue(cbSource->currentText());
    }
    qDebug() << "TriggerSource:" << m_pcMyCamera->SetEnumValue("TriggerSource", setSourceVal);

    // If there's a trigger activation combobox, set TriggerActivation accordingly
    QComboBox *cbActivation = this->findChild<QComboBox*>("triggerActivation");
    if (cbActivation) {
        int actVal = mapTriggerActivationValue(cbActivation->currentText());
        qDebug() << "TriggerActivation:" << m_pcMyCamera->SetEnumValue("TriggerActivation", actVal);
    }
    //设置曝光时间
    qDebug()<<"SetExposureTime:"<<m_pcMyCamera->SetFloatValue("ExposureTime",5000);

    // --- 使用 SDK 在相机端设置 AOI（Width/Height）使 highphoto / weightphoto 生效 ---
    int desiredW = ui->weightphoto->value();
    int desiredH = ui->highphoto->value();

    // 查询并对齐宽度
    MVCC_INTVALUE_EX widthInfo;
    memset(&widthInfo, 0, sizeof(widthInfo));
    int nRetVal = m_pcMyCamera->GetIntValue("Width", &widthInfo);
    if (nRetVal == MV_OK)
    {
        // clamp
        if (desiredW < (int)widthInfo.nMin) desiredW = (int)widthInfo.nMin;
        if (desiredW > (int)widthInfo.nMax) desiredW = (int)widthInfo.nMax;
        // align to step
        if (widthInfo.nInc > 0)
        {
            int64_t diff = (desiredW - (int)widthInfo.nMin) % widthInfo.nInc;
            desiredW -= (int)diff;
        }
        nRetVal = m_pcMyCamera->SetIntValue("Width", desiredW);
        qDebug()<<"Set Width:"<<nRetVal<<"->"<<desiredW;
    }

    // 查询并对齐高度
    MVCC_INTVALUE_EX heightInfo;
    memset(&heightInfo, 0, sizeof(heightInfo));
    nRetVal = m_pcMyCamera->GetIntValue("Height", &heightInfo);
    if (nRetVal == MV_OK)
    {
        if (desiredH < (int)heightInfo.nMin) desiredH = (int)heightInfo.nMin;
        if (desiredH > (int)heightInfo.nMax) desiredH = (int)heightInfo.nMax;
        if (heightInfo.nInc > 0)
        {
            int64_t diff = (desiredH - (int)heightInfo.nMin) % heightInfo.nInc;
            desiredH -= (int)diff;
        }
        nRetVal = m_pcMyCamera->SetIntValue("Height", desiredH);
        qDebug()<<"Set Height:"<<nRetVal<<"->"<<desiredH;
    }

    // 将偏移设为 0（可根据需要调整）
    m_pcMyCamera->SetIntValue("OffsetX", 0);
    m_pcMyCamera->SetIntValue("OffsetY", 0);

    // 在完成相机参数配置后启动抓取
    qDebug()<<"StartCamera:"<<m_pcMyCamera->StartGrabbing();

    // 根据相机像素格式分配 myImage（ReadBuffer 会覆盖 QImage 内容，但预分配可以保证尺寸）
    MVCC_ENUMVALUE enumVal;
    memset(&enumVal, 0, sizeof(enumVal));
    QImage::Format qfmt = QImage::Format_RGB888;
    if (m_pcMyCamera->GetEnumValue("PixelFormat", &enumVal) == MV_OK)
    {
        // 常见 mono -> Format_Grayscale8，否则使用 RGB888（SDK ReadBuffer 会做必要转换）
        if (enumVal.nCurValue == PixelType_Gvsp_Mono8)
            qfmt = QImage::Format_Grayscale8;
        else
            qfmt = QImage::Format_RGB888;
    }

    // 重新分配 myImage 为相机实际尺寸
    if (myImage)
    {
        delete myImage;
        myImage = nullptr;
    }
    myImage = new QImage(desiredW, desiredH, qfmt);

    // 传入线程
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
    // Use user-specified size from spinboxes when scaling
    QSize targetSize = ui->label_show_->size();
    if (ui->weightphoto->value() > 0 && ui->highphoto->value() > 0) {
        targetSize.setWidth(ui->weightphoto->value());
        targetSize.setHeight(ui->highphoto->value());
        // also update label fixed size to reflect chosen dimensions
        ui->label_show_->setFixedSize(targetSize);
    }
    QPixmap pix = QPixmap::fromImage(image).scaled(targetSize, Qt::KeepAspectRatio);
    ui->label_show_->setPixmap(pix);
    // 更新当前缓冲图像，供保存使用
    if(myImage)
        *myImage = image;
}

void control_window::on_weightphoto_valueChanged(int val)
{
    if (val > 0 && ui->highphoto->value() > 0) {
        ui->label_show_->setFixedSize(val, ui->highphoto->value());
        // persist value to local ini
        QString cfgPath = QCoreApplication::applicationDirPath() + "/settings.ini";
        QSettings settings(cfgPath, QSettings::IniFormat);
        settings.setValue("WeightPhoto", val);
    }
}

void control_window::on_highphoto_valueChanged(int val)
{
    if (val > 0 && ui->weightphoto->value() > 0) {
        ui->label_show_->setFixedSize(ui->weightphoto->value(), val);
        // persist value to local ini
        QString cfgPath = QCoreApplication::applicationDirPath() + "/settings.ini";
        QSettings settings(cfgPath, QSettings::IniFormat);
        settings.setValue("HighPhoto", val);
    }
}

void control_window::on_triggerMode_currentIndexChanged(int index)
{
    // Map combobox text to SDK value and always print the mapped value
    int sdkVal = index;
    QComboBox *cb = this->findChild<QComboBox*>("triggerMode");
    if (cb) {
        sdkVal = mapTriggerModeValue(cb->currentText());
    }
    qDebug() << "Selected TriggerMode value:" << sdkVal;

    // If camera isn't open yet, just print the mapping and return
    if (!m_pcMyCamera) return;

    // Conservative: stop grabbing, set, restart if necessary
    bool wasRunning = myThread && myThread->isRunning();
    if (wasRunning) {
        myThread->requestInterruption();
        myThread->wait();
    }

    int ret = m_pcMyCamera->SetEnumValue("TriggerMode", sdkVal);
    qDebug() << "UI set TriggerMode" << ret << "->" << sdkVal;
    if (wasRunning && myThread) myThread->start();

    // persist UI selection to local ini
    {
        QString cfgPath = QCoreApplication::applicationDirPath() + "/settings.ini";
        QSettings settings(cfgPath, QSettings::IniFormat);
        settings.setValue("TriggerModeIndex", index);
        // also persist the mapped SDK integer value
        settings.setValue("TriggerModeValue", sdkVal);
    }
}

void control_window::on_triggerSource_currentIndexChanged(int index)
{
    // Map combobox text to SDK value and always print the mapped value
    int sdkVal = index;
    QComboBox *cb2 = this->findChild<QComboBox*>("triggerSource");
    if (cb2) {
        sdkVal = mapTriggerSourceValue(cb2->currentText());
    }
    qDebug() << "Selected TriggerSource value:" << sdkVal;

    // If camera isn't open yet, just print the mapping and return
    if (!m_pcMyCamera) return;

    bool wasRunning = myThread && myThread->isRunning();
    if (wasRunning) {
        myThread->requestInterruption();
        myThread->wait();
    }

    int ret = m_pcMyCamera->SetEnumValue("TriggerSource", sdkVal);
    qDebug() << "UI set TriggerSource" << ret << "->" << sdkVal;
    if (wasRunning && myThread) myThread->start();

    // persist UI selection to local ini
    {
        QString cfgPath = QCoreApplication::applicationDirPath() + "/settings.ini";
        QSettings settings(cfgPath, QSettings::IniFormat);
        settings.setValue("TriggerSourceIndex", index);
        // also persist the mapped SDK integer value
        settings.setValue("TriggerSourceValue", sdkVal);
    }
}

void control_window::saveImage(const QString &format)
{
    if(!myImage || myImage->isNull()){
        QMessageBox::warning(this, "警告", "没有可保存的图像！");
        return;
    }
    QString savePath;
    if (!m_savePath.isEmpty()) {
        QDir d(m_savePath);
        savePath = d.absolutePath() + QDir::separator();
        if (!d.exists()) d.mkpath(d.absolutePath());
    } else {
        savePath = QDir::currentPath() + "/myImage/";
        QDir d(savePath);
        if (!d.exists()) d.mkpath(savePath);
    }
    QString curDate = QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss.zzz");
    QString saveName = savePath + curDate + "." + format;
    myImage->save(saveName, format.toUpper().toUtf8().constData());
}


void control_window::on_Exit_Button_clicked()
{
    // Gracefully stop thread if running
    if (myThread && myThread->isRunning()) {
        myThread->requestInterruption();
        myThread->wait();
    }

    // Close camera if open
    if (m_pcMyCamera) {
        m_pcMyCamera->StopGrabbing();
        m_pcMyCamera->Close();
        delete m_pcMyCamera;
        m_pcMyCamera = nullptr;
    }

    // delete image buffer
    if (myImage) {
        delete myImage;
        myImage = nullptr;
    }

    qApp->quit();
}


void control_window::on_save_location_clicked()
{

    // Open a directory selection dialog and set the save path
    QString dir = QFileDialog::getExistingDirectory(this, tr("选择保存目录"), m_savePath.isEmpty() ? QDir::currentPath() : m_savePath,
                                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (dir.isEmpty()) return;
    // create a "Photo" folder inside selected directory and use it
    QString photoFolder = QDir(dir).filePath("Photo");
    QDir pd(photoFolder);
    if (!pd.exists()) pd.mkpath(photoFolder);
    m_savePath = photoFolder;
    // persist the selection to local ini (in app folder)
    QString cfgPath = QCoreApplication::applicationDirPath() + "/settings.ini";
    QSettings settings(cfgPath, QSettings::IniFormat);
    settings.setValue("savePath", m_savePath);
    //QMessageBox::information(this, tr("保存路径设置"), tr("保存路径已设置为:\n%1").arg(m_savePath));
    if (this->statusBar()) this->statusBar()->showMessage(tr("%1").arg(m_savePath));
}

