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
    if(cameraPtr == NULL)
    {
        return;
    }
    if(imagePtr == NULL)
    {
        return;
    }

    while(!isInterruptionRequested())
    {
        qDebug()<<"SoftTrigger:"<<cameraPtr->CommandExecute("TriggerSoftware");
        // Read directly into QImage
        cameraPtr->ReadBuffer(*imagePtr);
        emit signal_messImage(*imagePtr);
        msleep(10);

        //耗时操作，需要放到线程中保存
        //QImage保存图像
        //QString savePath = QDir::currentPath() + "/myImage/";
        //QString curDate = QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss.zzz");
        //QString saveName = savePath + curDate + ".png";
        //qDebug()<<"saveName:"<<saveName;
        //myImage->save(saveName);
    }
}
