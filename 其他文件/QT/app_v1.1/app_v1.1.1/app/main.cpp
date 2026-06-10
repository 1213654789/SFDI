#include "mainwindow.h"
#include "open_window.h"
#include <QApplication>
#include <QObject>
#include "qdebug.h"
#include "timerthread.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //    MainWindow w;
    open_window w;
    w.show();

    // Start a high-resolution 0.1 ms timer in a worker thread
    TimerThread *t = new TimerThread(100, [](){ qDebug() << "timer tick"; }); // 100 microseconds
    t->start();

    // Ensure the timer thread stops when the application quits
    QObject::connect(&a, &QApplication::aboutToQuit, [t]() {
        t->stop();
        delete t;
    });

    return a.exec();
}
