#include "control_window.h"
#include "mainwindow.h"
#include "ui_control_window.h"
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMutex>
#include <QPixmap>
#include <QCoreApplication>
#include <QImage>
#include <QDateTime>
#include <QVBoxLayout>
#include <QFont>
#include <QLabel>
#include <QFileDialog>
#include <QSettings>
#include <QSerialPortInfo>
#include "saveworker.h"
#include <QThread>

static QMutex s_logMutex;
static QFile *s_logFile = nullptr;
static QtMessageHandler previousMsgHandler = nullptr;

static void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context);
    QMutexLocker locker(&s_logMutex);
    if (!s_logFile) {
        QString path = QCoreApplication::applicationDirPath() + "/app_log.txt";
        s_logFile = new QFile(path);
        s_logFile->open(QIODevice::Append | QIODevice::Text);
    }
    QTextStream ts(s_logFile);
    QString now = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    QString level;
    switch (type) {
    case QtDebugMsg: level = "DEBUG"; break;
    case QtInfoMsg: level = "INFO"; break;
    case QtWarningMsg: level = "WARN"; break;
    case QtCriticalMsg: level = "CRIT"; break;
    case QtFatalMsg: level = "FATAL"; break;
    }
    ts << now << " [" << level << "] " << msg << "\n";
    ts.flush();
    // call previous handler if exists
    if (previousMsgHandler) previousMsgHandler(type, context, msg);
}

// previousMsgHandler is defined in this translation unit
// (static above) so nothing to define here.

control_window::control_window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::control_window)
{
    ui->setupUi(this);
    // Install global Qt message handler to capture qDebug/qWarning/etc into a log file
    // The handler is defined below in this translation unit.
    previousMsgHandler = qInstallMessageHandler(myMessageOutput);
    // Ensure widgets and resources (myThread, myImage, etc.) are initialized
    this->setWindowIcon(QIcon(":/img/photo.ioc"));
    initWidget();
}


control_window::~control_window()
{
    if (m_serialPollTimer) {
        m_serialPollTimer->stop();
        delete m_serialPollTimer;
        m_serialPollTimer = nullptr;
    }

    // ensure save worker is stopped
    if (m_saveWorker) {
        m_saveWorker->stop();
        delete m_saveWorker; m_saveWorker = nullptr;
    }

    // restore previous Qt message handler and close log file
    qInstallMessageHandler(previousMsgHandler);
    previousMsgHandler = nullptr;
    {
        QMutexLocker locker(&s_logMutex);
        if (s_logFile) {
            s_logFile->flush();
            s_logFile->close();
            delete s_logFile;
            s_logFile = nullptr;
        }
    }

    delete ui;
}


void control_window::on_Shutter_time_valueChanged(int val)
{
    // persist value
    QString cfgPath = QCoreApplication::applicationDirPath() + "/settings.ini";
    QSettings settings(cfgPath, QSettings::IniFormat);
    settings.setValue("ShutterTime", val);

    // apply to camera if open
    if (m_pcMyCamera) {
        qDebug() << "SetExposureTime (from UI):" << m_pcMyCamera->SetFloatValue("ExposureTime", (float)val);
    }
}


void control_window::on_take_photo_clicked()
{
    // Behavior depends on selectmode (trigger source). If hardware trigger is selected,
    // this button behaves like continuous_acquisition toggle and also triggers send_button once.
    // If software trigger is selected, it only toggles continuous_acquisition.

    // Determine trigger source combobox (named "selectmode" in UI). Fall back to TriggerSource if absent.
    QComboBox *select = this->findChild<QComboBox*>("selectmode");
    QString selText;
    if (select) selText = select->currentText();
    else {
        QComboBox *cb = this->findChild<QComboBox*>("triggerSource");
        if (cb) selText = cb->currentText();
    }

    bool isHardware = m_takePhotoHardwareMode;
    // fallback to text-check if flag not set
    if (!isHardware && !selText.isEmpty()) {
        QString t = selText.toLower();
        if (t.contains("hardware") || t.contains("hard") || t.contains("line0") || t.contains("line") || t.contains("硬件") || t.contains("硬")) isHardware = true;
    }

    // Behavior:
    // - Hardware trigger: do NOT toggle continuous acquisition. Instead ensure camera
    //   is in trigger/grabbing state and send a single trigger command to the external
    //   controller (via serial) so the camera captures once per external pulse.
    // - Software trigger: toggle continuous acquisition as before.
    if (isHardware) {
        if (!m_bOpenDevice) {
            QMessageBox::warning(this, "警告", "请先打开设备以使用硬件触发！");
            return;
        }

        // Ensure camera is set to trigger mode and using the configured trigger source
        if (m_pcMyCamera) {
            int modeVal = mapTriggerModeValue("On");
            // Many SDKs require changing TriggerSource while TriggerMode is OFF. Sequence:
            // StopGrabbing -> TriggerMode=Off -> set TriggerSource/Activation -> TriggerMode=On -> StartGrabbing
            m_pcMyCamera->StopGrabbing();

            int retOff = m_pcMyCamera->SetEnumValue("TriggerMode", mapTriggerModeValue("Off"));
            qDebug() << "Hardware trigger: Set TriggerMode(Off) returned" << retOff;

            // set trigger source
            QComboBox *cbSource = this->findChild<QComboBox*>("triggerSource");
            int srcVal = 0;
            if (cbSource) srcVal = mapTriggerSourceValue(cbSource->currentText());
            int retSrc = m_pcMyCamera->SetEnumValue("TriggerSource", srcVal);
            qDebug() << "Hardware trigger: Set TriggerSource(" << srcVal << ") returned" << retSrc;

            // set activation (rising/falling/level)
            QComboBox *cbAct = this->findChild<QComboBox*>("triggerActivation");
            int retAct = MV_OK;
            if (cbAct) {
                int actVal = mapTriggerActivationValue(cbAct->currentText());
                retAct = m_pcMyCamera->SetEnumValue("TriggerActivation", actVal);
                qDebug() << "Hardware trigger: Set TriggerActivation(" << actVal << ") returned" << retAct;
            }

            // finally enable trigger mode
            int retOn = m_pcMyCamera->SetEnumValue("TriggerMode", mapTriggerModeValue("On"));
            qDebug() << "Hardware trigger: Set TriggerMode(On) returned" << retOn;

            // Start grabbing if all sets succeeded
            if (retSrc == MV_OK && retOn == MV_OK) {
                int grabRet = m_pcMyCamera->StartGrabbing();
                qDebug() << "Hardware trigger: StartGrabbing returned" << grabRet;
            } else {
                qDebug() << "Hardware trigger: not starting grabbing because TriggerSource/Mode failed";
            }

            // Ensure the frame-reading thread is running so external triggers are consumed
            if (myThread && !myThread->isRunning()) {
                qDebug() << "Hardware trigger: starting frame reader thread";
                myThread->start();
            } else if (myThread) {
                qDebug() << "Hardware trigger: frame reader thread already running";
            }
        }

        // Send one serial trigger (this doesn't start continuous acquisition)
        // Create serial window if needed (same behavior as on_send_button_clicked)
        if (!m_serialWindow) {
            m_serialWindow = new MainWindow(this);
            connect(m_serialWindow, &QWidget::destroyed, this, [this]() { m_serialWindow = nullptr; });
            m_serialWindow->setAttribute(Qt::WA_DeleteOnClose);
        }

        // If serial port is not open, try to open it using current selection in control window
        if (m_serialWindow && m_serialWindow->serialPort && !m_serialWindow->serialPort->isOpen()) {
            if (ui && ui->open_serailCb) {
                m_serialWindow->setCurrentSerialPort(ui->open_serailCb->currentText());
            }
            m_serialWindow->openSerialPort();
            qDebug() << "Hardware trigger: tried to open serial port -> isOpen=" << (m_serialWindow->serialPort ? m_serialWindow->serialPort->isOpen() : false);
        }
        int freq = 0;
        int times = 0;
        if (ui->open_freq) freq = ui->open_freq->value();
        if (ui->open_times) times = ui->open_times->value();
        QString message = QString("A%1B%2C").arg(freq).arg(times);
        m_serialWindow->setSendEditText(message);
        qDebug() << "Hardware trigger: sent trigger message ->" << message << " serialOpen=" << (m_serialWindow->serialPort ? m_serialWindow->serialPort->isOpen() : false);
        return;
    }

    // Software trigger: toggle continuous acquisition as before
    on_continuous_acquisition_clicked();
}


void control_window::on_actionopen_triggered()
{
    // Only allow common image formats
    QString filter = "Images (*.png *.jpg *.jpeg *.bmp)";
    QString fileName = QFileDialog::getOpenFileName(this, tr("打开图像"), m_savePath.isEmpty() ? QDir::currentPath() : m_savePath, filter);
    if (fileName.isEmpty()) return;

    QImage img;
    if (!img.load(fileName)) {
        QMessageBox::warning(this, tr("打开失败"), tr("无法加载所选图像：%1").arg(fileName));
        return;
    }

    // display and update buffer
    slot_displayImage(img);
    if (myImage) {
        delete myImage;
        myImage = new QImage(img);
    }
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
    // Allow window to be resized by user; enforce a sensible minimum instead of a fixed size
    this->setMinimumSize(this->size());

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

    // 串口热插拔检测：定时轮询可用串口并在变化时刷新下拉框
    m_serialPollTimer = new QTimer(this);
    connect(m_serialPollTimer, &QTimer::timeout, this, [this]() {
        QStringList ports;
        foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
            ports << info.portName();
        }
        // 如果端口列表发生变化，刷新 UI 并通知 MainWindow（如果存在）
        if (ports != m_lastSerialPorts) {
            m_lastSerialPorts = ports;
            if (ui && ui->open_serailCb) {
                ui->open_serailCb->clear();
                ui->open_serailCb->addItems(ports);
            }
            if (m_serialWindow) {
                m_serialWindow->refreshSerialPorts();
            }
        }
    });
    m_serialPollTimer->start(1500); // 1.5s 轮询一次

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
        // Ensure label has a reasonable minimum so it doesn't collapse to a thin strip
            // Do not change label widget size here; its geometry is controlled by the UI layout
            // Keep scaledContents disabled and allow layout to manage sizing
            // Do NOT enable setScaledContents: we manage pixmap scaling manually to preserve desired ratio
            ui->label_show_->setScaledContents(false);
            // Prefer the label to expand in layouts so images get allocated space
            ui->label_show_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        }

        // Restore save format combobox (save_formal) selection and connect its signal
        if (ui->save_formal) {
            int savedFmt = settings.value("SaveFormalIndex", ui->save_formal->currentIndex()).toInt();
            ui->save_formal->setCurrentIndex(savedFmt);
            connect(ui->save_formal, SIGNAL(currentIndexChanged(int)), this, SLOT(on_save_formal_currentIndexChanged(int)));
        }

    // Connect new Shutter_time spinbox (if present) to handler and restore value
    if (ui) {
        if (this->findChild<QSpinBox*>("Shutter_time")) {
            QSpinBox *sb = this->findChild<QSpinBox*>("Shutter_time");
            int savedShutter = settings.value("ShutterTime", sb->value()).toInt();
            sb->setValue(savedShutter);
            connect(sb, SIGNAL(valueChanged(int)), this, SLOT(on_Shutter_time_valueChanged(int)));
        }
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
    // Unified open/close button handler: if device already open -> close it
    if (m_bOpenDevice) {
        closeCamera();
        // update UI
        if (ui && ui->open_device) {
            ui->open_device->setText("打开设备");
            ui->open_device->setStyleSheet("color: black;");
        }
        return;
    }

    // Otherwise open selected device
    QString deviceModel = ui->choose_devices->currentText();
    if (deviceModel.isEmpty()) {
        QMessageBox::warning(this, "警告", "请选择设备！");
        return;
    }
    m_pcMyCamera = new CMvCamera;
    if (m_pcMyCamera == NULL) {
        QMessageBox::warning(this, "警告", "无法创建相机对象！");
        return;
    }
    int nIndex = ui->choose_devices->currentIndex();
    int nRet = m_pcMyCamera->Open(m_stDevList.pDeviceInfo[nIndex]);
    qDebug() << "Connect:" << nRet;
    if (MV_OK != nRet) {
        delete m_pcMyCamera;
        m_pcMyCamera = NULL;
        QMessageBox::warning(this, "警告", "打开设备失败！");
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
    // 设置曝光时间：如果 UI 有 Shutter_time SpinBox，则使用其值（单位同 SDK），否则使用默认50000
    QSpinBox *shutterSb = this->findChild<QSpinBox*>("Shutter_time");
    int shutterVal = 50000;
    if (shutterSb) shutterVal = shutterSb->value();
    qDebug()<<"SetExposureTime:"<<m_pcMyCamera->SetFloatValue("ExposureTime", (float)shutterVal);

    // --- 使用 SDK 在相机端设置 AOI（Width/Height）使 highphoto / weightphoto 生效 ---
    int desiredW = ui->weightphoto->value();
    int desiredH = ui->highphoto->value();

    // 查询并对齐宽度（从相机读取硬件限制并反写到 UI）
    MVCC_INTVALUE_EX widthInfo;
    memset(&widthInfo, 0, sizeof(widthInfo));
    int nRetVal = m_pcMyCamera->GetIntValue("Width", &widthInfo);
    if (nRetVal == MV_OK)
    {
        // 把相机支持的范围/步进反映到 spinbox，防止用户选到不可用值
        if (ui->weightphoto) {
            ui->weightphoto->setMinimum((int)widthInfo.nMin);
            ui->weightphoto->setMaximum((int)widthInfo.nMax);
            if (widthInfo.nInc > 0) ui->weightphoto->setSingleStep((int)widthInfo.nInc);
        }

        // clamp 到相机允许范围并按步进对齐
        if (desiredW < (int)widthInfo.nMin) desiredW = (int)widthInfo.nMin;
        if (desiredW > (int)widthInfo.nMax) desiredW = (int)widthInfo.nMax;
        if (widthInfo.nInc > 0)
        {
            int64_t diff = (desiredW - (int)widthInfo.nMin) % widthInfo.nInc;
            desiredW -= (int)diff;
        }

        nRetVal = m_pcMyCamera->SetIntValue("Width", desiredW);
        qDebug() << "Set Width:" << nRetVal << "->" << desiredW;


		//验证相机的分辨率是否设置成功（通过回读 Width 来确认）
        MVCC_INTVALUE_EX widthCheck;
        memset(&widthCheck, 0, sizeof(widthCheck));
        if (m_pcMyCamera->GetIntValue("Width", &widthCheck) == MV_OK) {
            qDebug() << "Width after set - current:" << widthCheck.nCurValue;
            if ((int)widthCheck.nCurValue == desiredW) {
                qDebug() << "Width 设置成功，与期望值一致";
            }
            else {
                qDebug() << "Width 设置后不一致! 期望:" << desiredW << "实际:" << widthCheck.nCurValue;
            }
        }
        else {
            qDebug() << "回读 Width 失败";
        }







     

        // 把最终生效值写回到 UI，保持一致
        if (ui->weightphoto) ui->weightphoto->setValue(desiredW);
    } else {
        qDebug() << "GetIntValue Width failed:" << nRetVal;
    }

    // 查询并对齐高度（同上）
    MVCC_INTVALUE_EX heightInfo;
    memset(&heightInfo, 0, sizeof(heightInfo));
    nRetVal = m_pcMyCamera->GetIntValue("Height", &heightInfo);
    if (nRetVal == MV_OK)
    {
        if (ui->highphoto) {
            ui->highphoto->setMinimum((int)heightInfo.nMin);
            ui->highphoto->setMaximum((int)heightInfo.nMax);
            if (heightInfo.nInc > 0) ui->highphoto->setSingleStep((int)heightInfo.nInc);
        }

        if (desiredH < (int)heightInfo.nMin) desiredH = (int)heightInfo.nMin;
        if (desiredH > (int)heightInfo.nMax) desiredH = (int)heightInfo.nMax;
        if (heightInfo.nInc > 0)
        {
            int64_t diff = (desiredH - (int)heightInfo.nMin) % heightInfo.nInc;
            desiredH -= (int)diff;
        }

        nRetVal = m_pcMyCamera->SetIntValue("Height", desiredH);
        qDebug() << "Set Height:" << nRetVal << "->" << desiredH;

        if (ui->highphoto) ui->highphoto->setValue(desiredH);
    } else {
        qDebug() << "GetIntValue Height failed:" << nRetVal;
    }




    //验证相机的分辨率是否设置成功（通过回读 Hight 来确认）
    MVCC_INTVALUE_EX hightCheck;
    memset(&hightCheck, 0, sizeof(hightCheck));
    if (m_pcMyCamera->GetIntValue("Height", &hightCheck) == MV_OK) {
        qDebug() << "Height after set - current:" << hightCheck.nCurValue;
        if ((int)hightCheck.nCurValue == desiredH) {
            qDebug() << "Height 设置成功，与期望值一致";
        }
        else {
            qDebug() << "Height 设置后不一致! 期望:" << desiredH << "实际:" << hightCheck.nCurValue;
        }
    }
    else {
        qDebug() << "回读 Height 失败";
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
    if (ui && ui->open_device) {
        ui->open_device->setText("关闭设备");
        ui->open_device->setStyleSheet("color: red;");
        // Ensure AOI and trigger controls remain enabled when device is opened
        if (ui->weightphoto) ui->weightphoto->setEnabled(true);
        if (ui->highphoto) ui->highphoto->setEnabled(true);
        if (ui->TriggerMode) ui->TriggerMode->setEnabled(true);
        if (ui->TriggerSource) ui->TriggerSource->setEnabled(true);
    }

}


void control_window::on_close_device_clicked()
{
    // Backwards compatible: calling close explicitly
    closeCamera();
    if (ui && ui->open_device) {
        ui->open_device->setText("打开设备");
        ui->open_device->setStyleSheet("color: black;");
        // ensure controls restored
        if (ui->weightphoto) ui->weightphoto->setEnabled(true);
        if (ui->highphoto) ui->highphoto->setEnabled(true);
        if (ui->TriggerMode) ui->TriggerMode->setEnabled(true);
        if (ui->TriggerSource) ui->TriggerSource->setEnabled(true);
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

    // NOTE: per user request, do not debounce this button here; each click toggles immediately

    // Toggle start/stop behavior on the single button
    if(!myThread->isRunning())
    {
        // create and start save worker thread if not already
        if (!m_saveWorker) {
            m_saveWorker = new SaveWorker(m_savePath, "bmp");
            QComboBox *cb = this->findChild<QComboBox*>("save_formal");
            if (cb) m_saveWorker->setFormat(cb->currentText());
        }

        // connect myThread frame signal to save worker using functor wrapper
        m_saveConn = QObject::connect(myThread, &MyThread::signal_messImage, this, [this](QImage img){
            if (m_saveWorker) m_saveWorker->enqueueImage(img);
        });

        myThread->start();

        // update UI text to indicate it is running
        if (ui && ui->continuous_acquisition) {
            ui->continuous_acquisition->setText("停止采集");
            ui->continuous_acquisition->setStyleSheet("color: red;");
        }
    }
    else
    {
        // Stop the thread safely
        myThread->requestInterruption();
        myThread->wait();

        // Stop hardware grabbing as well
        if (m_pcMyCamera) {
            m_pcMyCamera->StopGrabbing();
        }

        // When stopping, save the last acquired image buffer to disk using
        // the selected save format from combobox `save_formal` (if available)
        QString fmt = "bmp"; // default
        QComboBox *cb = this->findChild<QComboBox*>("save_formal");
        if (cb) fmt = cb->currentText().toLower();
        // call helper to save; saveImage checks buffer existence
        saveImage(fmt);

        // disconnect and stop save worker safely
        if (m_saveWorker) {
            if (m_saveConn) QObject::disconnect(m_saveConn);
            m_saveWorker->stop();
            delete m_saveWorker; m_saveWorker = nullptr;
        }

        // update UI text back to start
        if (ui && ui->continuous_acquisition) {
            ui->continuous_acquisition->setText("连续采集");
            ui->continuous_acquisition->setStyleSheet("color: black;");
        }
    }
}


void control_window::slot_display()
{
    // 占位——目前无text-only display
}


void control_window::slot_displayImage(QImage image)
{
    if (image.isNull()) return;

    // Respect user-set logical aspect (weightphoto/highphoto) but DO NOT change
    // the label widget size. Always render inside the existing label bounds.
    int desiredW = ui->weightphoto->value();
    int desiredH = ui->highphoto->value();

    QSize avail = ui->label_show_->size();
    if (avail.width() <= 0 || avail.height() <= 0) {
        // not yet laid out
        return;
    }

    QImage toShow = image;
    if (desiredW > 0 && desiredH > 0 && image.width() > 0 && image.height() > 0) {
        qreal desiredAspect = (qreal)desiredW / (qreal)desiredH;
        qreal srcAspect = (qreal)image.width() / (qreal)image.height();
        QRect cropRect;
        if (srcAspect > desiredAspect) {
            int newW = int(image.height() * desiredAspect);
            int x = (image.width() - newW) / 2;
            cropRect = QRect(x, 0, newW, image.height());
        } else {
            int newH = int(image.width() / desiredAspect);
            int y = (image.height() - newH) / 2;
            cropRect = QRect(0, y, image.width(), newH);
        }
        toShow = image.copy(cropRect);
    }

    QPixmap pix = QPixmap::fromImage(toShow).scaled(avail, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_show_->setScaledContents(false);
    ui->label_show_->setAlignment(Qt::AlignCenter);
    ui->label_show_->setPixmap(pix);

    // Keep the label widget geometry untouched; update buffer
    if (myImage) *myImage = image;
}


void control_window::on_weightphoto_valueChanged(int val)
{
    if (val > 0 && ui->highphoto->value() > 0) {
        // Do not force the label to resize beyond UI; cap desired logical size
        const int MAX_DESIRED = 2000;
        int cappedW = qMin(val, MAX_DESIRED);
        int cappedH = qMin(ui->highphoto->value(), MAX_DESIRED);
        // persist value to local ini
        QString cfgPath = QCoreApplication::applicationDirPath() + "/settings.ini";
        QSettings settings(cfgPath, QSettings::IniFormat);
        settings.setValue("WeightPhoto", val);
        // if there's a current image buffer, re-render it to apply new ratio immediately
        if (myImage && !myImage->isNull()) {
            // re-render but ensure we pass the capped desired size via UI values
            ui->weightphoto->blockSignals(true);
            ui->highphoto->blockSignals(true);
            ui->weightphoto->setValue(cappedW);
            ui->highphoto->setValue(cappedH);
            slot_displayImage(*myImage);
            ui->weightphoto->blockSignals(false);
            ui->highphoto->blockSignals(false);
        }
    }
}


void control_window::on_highphoto_valueChanged(int val)
{
    if (val > 0 && ui->weightphoto->value() > 0) {
        const int MAX_DESIRED = 2000;
        int cappedW = qMin(ui->weightphoto->value(), MAX_DESIRED);
        int cappedH = qMin(val, MAX_DESIRED);
        // persist value to local ini
        QString cfgPath = QCoreApplication::applicationDirPath() + "/settings.ini";
        QSettings settings(cfgPath, QSettings::IniFormat);
        settings.setValue("HighPhoto", val);
        // if there's a current image buffer, re-render it to apply new ratio immediately
        if (myImage && !myImage->isNull()) {
            ui->weightphoto->blockSignals(true);
            ui->highphoto->blockSignals(true);
            ui->weightphoto->setValue(cappedW);
            ui->highphoto->setValue(cappedH);
            slot_displayImage(*myImage);
            ui->weightphoto->blockSignals(false);
            ui->highphoto->blockSignals(false);
        }
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


void control_window::on_save_formal_currentIndexChanged(int index)
{
    // The combobox should only change the desired save format — do not auto-save on startup
    if (!ui) return;
    QComboBox *cb = this->findChild<QComboBox*>("save_formal");
    if (!cb) return;
    QString txt = cb->currentText();

    // persist the selection to settings only
    QString cfgPath = QCoreApplication::applicationDirPath() + "/settings.ini";
    QSettings settings(cfgPath, QSettings::IniFormat);
    settings.setValue("SaveFormalIndex", index);
    settings.setValue("SaveFormalValue", txt);

    // update statusbar to indicate selected format (no saving performed)
    //if (this->statusBar()) this->statusBar()->showMessage(tr("保存格式: %1").arg(txt));


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


void control_window::on_open_btnSerialCheck_clicked()
{

    // 刷新串口下拉框（与原 open_window 的行为一致）
    if (!ui) return;
    ui->open_serailCb->clear();
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->open_serailCb->addItem(info.portName());
    }

    // 如果串口主窗口已创建，亦同步刷新其列表
    if (m_serialWindow) {
        m_serialWindow->refreshSerialPorts();
    }
}


void control_window::on_send_button_clicked()
{

    // 如果串口主窗口未创建，先创建但不一定显示（与 open_window 的行为一致）
    if (!m_serialWindow) {
        m_serialWindow = new MainWindow(this);
        connect(m_serialWindow, &QWidget::destroyed, this, [this]() { m_serialWindow = nullptr; });
        m_serialWindow->setAttribute(Qt::WA_DeleteOnClose);
    }

    // 从 UI 中读取频率/次数并组合格式化字符串发送给串口主窗口
    int freq = 0;
    int times = 0;
    if (ui->open_freq) freq = ui->open_freq->value();
    if (ui->open_times) times = ui->open_times->value();

    QString message = QString("A%1B%2C").arg(freq).arg(times);
    m_serialWindow->setSendEditText(message);
}


void control_window::on_open_openBt_clicked()
{

    // 如果串口主窗口尚未创建，则创建（但初始不显示）
    if (!m_serialWindow) {
        m_serialWindow = new MainWindow(this);
        connect(m_serialWindow, &QWidget::destroyed, this, [this]() { m_serialWindow = nullptr; });
        m_serialWindow->setAttribute(Qt::WA_DeleteOnClose);
        // 将当前下拉框选择同步给串口主窗口
        if (ui->open_serailCb) m_serialWindow->setCurrentSerialPort(ui->open_serailCb->currentText());
    }

    // 调用主窗口的打开串口方法
    m_serialWindow->openSerialPort();

    // 切换按钮显示状态（与 open_window 中的行为一致）
    if (!ui) return;
    if (ui->open_openBt->text() == "连接") {
        ui->open_openBt->setText("关闭");
        ui->open_openBt->setStyleSheet("color: red;");
        ui->open_serailCb->setEnabled(false);
        ui->open_btnSerialCheck->setEnabled(false);
        // keep frequency/time inputs enabled in the main control window
        ui->open_freq->setEnabled(false);
        ui->open_times->setEnabled(false);
    } else {
        ui->open_openBt->setText("连接");
        ui->open_openBt->setStyleSheet("color: black;");
        ui->open_serailCb->setEnabled(true);
        ui->open_btnSerialCheck->setEnabled(true);
        // restore frequency/time inputs
        ui->open_freq->setEnabled(true);
        ui->open_times->setEnabled(true);
    }
}


void control_window::on_open_serailCb_currentIndexChanged(const QString &arg1)
{
    if (m_serialWindow) {
        m_serialWindow->setCurrentSerialPort(arg1);
    }
}


void control_window::closeCamera()
{
    if (myThread && myThread->isRunning()) {
        myThread->requestInterruption();
        myThread->wait();
    }
    if (m_pcMyCamera) {
        m_pcMyCamera->StopGrabbing();
        m_pcMyCamera->Close();
        delete m_pcMyCamera;
        m_pcMyCamera = nullptr;
    }
    if (myImage) {
        delete myImage;
        myImage = nullptr;
    }
    m_bOpenDevice = false;
}


void control_window::on_selectmode_activated(int index)
{
    // Update internal flag: index 0 == 硬件拍照, index 1 == 软件拍照 (based on UI ordering)
    QComboBox *cb = this->findChild<QComboBox*>("selectmode");
    if (!cb) return;
    QString txt = cb->itemText(index).toLower();
    // treat anything containing "硬件" or starting with line as hardware
    if (txt.contains("硬件") || txt.contains("line") || txt.contains("硬")) {
        m_takePhotoHardwareMode = true;
    } else {
        m_takePhotoHardwareMode = false;
    }
}
