#include "mythread.h"
MyThread::MyThread(QObject *parent)
    : QThread{parent}
{
}

MyThread::~MyThread()
{
    // cameraPtr and imagePtr are owned by caller; do not delete them here
}

void MyThread::getCameraPtr(CMvCamera *camera)
{
    cameraPtr = camera;
}

void MyThread::getImagePtr(QImage *image)
{
    imagePtr = image;
}

void MyThread::run()
{
    if (cameraPtr == NULL) {
        return;
    }
    if (imagePtr == NULL) {
        return;
    }

    while (!isInterruptionRequested()) {
        // Read trigger configuration to decide behavior
        int triggerMode = 0;
        int triggerSource = -1;
        MVCC_ENUMVALUE enumVal;
        memset(&enumVal, 0, sizeof(enumVal));
        if (cameraPtr->GetEnumValue("TriggerMode", &enumVal) == MV_OK) {
            triggerMode = (int)enumVal.nCurValue;
        }
        memset(&enumVal, 0, sizeof(enumVal));
        if (cameraPtr->GetEnumValue("TriggerSource", &enumVal) == MV_OK) {
            triggerSource = (int)enumVal.nCurValue;
        }

        // Debug: report current trigger configuration
        qDebug() << "MyThread: TriggerMode=" << triggerMode << " TriggerSource=" << triggerSource;

        // Determine if software trigger is configured. In this project software trigger
        // was mapped to value 7; confirm with your SDK/CHM and adjust if different.
        bool useSoftwareTrigger = (triggerMode != 0 && triggerSource == 7);

        if (useSoftwareTrigger) {
            // Issue software trigger only when configured
            qDebug() << "SoftTrigger:" << cameraPtr->CommandExecute("TriggerSoftware");
        }

        // Read a frame from the camera. For hardware external trigger this will block
        // until a frame arrives; for software trigger it will read the frame produced
        // by the CommandExecute call above.
        int rc = cameraPtr->ReadBuffer(*imagePtr);
        if (rc == MV_OK) {
            emit signal_messImage(*imagePtr);
        } else {
            qDebug() << "ReadBuffer failed:" << rc << " TriggerMode=" << triggerMode << " TriggerSource=" << triggerSource;
            msleep(5);
        }

        // Sleep briefly: longer for software-trigger loops, shorter for hardware-driven
        if (useSoftwareTrigger)
            msleep(10);
        else
            msleep(2);
    }
}
