#include "mainwindow.h"
#include "open_window.h"
#include "control_window.h"
#include <QApplication>
#include <QObject>
#include "qdebug.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    open_window w;
    control_window w;
    w.show();




    return a.exec();
}
